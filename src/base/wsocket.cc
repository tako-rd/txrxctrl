/*!
 * cryptography library
 *
 * Copyright (c) 2023 tako
 *
 * This software is released under the MIT license.
 * see https://opensource.org/licenses/MIT
 */
#include "base/wsocket.h"

namespace txrxctrl {

wsocket::wsocket(const wsocket& other) noexcept {
#if defined(_MSC_VER)
  wsa_data_ = other.wsa_data_;
#endif
  dst_socket_ = other.dst_socket_;
  src_socket_ = other.src_socket_;
  accept_socket_ = other.accept_socket_;
  src_addr_ = other.src_addr_;
  dst_addr_ = other.dst_addr_;
  socket_type_ = other.socket_type_;
  connection_type_ = other.connection_type_;
}

wsocket::wsocket(const wsocket&& other) noexcept {
#if defined(_MSC_VER)
  wsa_data_ = other.wsa_data_;
#endif
  dst_socket_ = other.dst_socket_;
  src_socket_ = other.src_socket_;
  accept_socket_ = other.accept_socket_;
  src_addr_ = other.src_addr_;
  dst_addr_ = other.dst_addr_;
  socket_type_ = other.socket_type_;
  connection_type_ = other.connection_type_;
}

wsocket::~wsocket() {

}

int32_t wsocket::initialize(int8_t* const dst_addr, const uint16_t dst_port, 
                            int8_t* const src_addr, const uint16_t src_port,
                            socket_type_t type) {
  int32_t status = 0;
  int32_t r_cd = SOCKET_SUCCESS;
  int32_t is_bind_src = 0;

  /* Initialize member variables. */
  dst_socket_ = INVALID_SOCKET;
  src_socket_ = INVALID_SOCKET;
  accept_socket_ = INVALID_SOCKET;
  connection_type_ = SOCK_STREAM;

  if (NULL != dst_addr) {
    /* Setting the destination address. */
    inet_pton(AF_INET, (PCSTR)dst_addr, &dst_addr_.sin_addr.s_addr);
    dst_addr_.sin_port = htons(dst_port);
    dst_addr_.sin_family = AF_INET;
  } else {
    /* Destination address is required. */
    r_cd = SOCKET_PARAMETERS_ERROR;
  }

  if (NULL != src_addr && SOCKET_SUCCESS == r_cd) {
    /* Setting the receiving address. */
    inet_pton(AF_INET, (PCSTR)src_addr, &src_addr_.sin_addr.s_addr);
    src_addr_.sin_port = htons(src_port);
    src_addr_.sin_family = AF_INET;
    is_bind_src = (CLIENT == type) ? 1 : 0;
  }
#if defined(_MSC_VER)
  if (SOCKET_SUCCESS == r_cd) {
    /* Loading the library, Ws2_32.dll. */
    status = WSAStartup(MAKEWORD(LIB_MAJOR_VER, LIB_MINOR_VER), &wsa_data_);
    if (0 != status) {
      r_cd = SOCKET_INITIALIZATION_ERROR;
    }
  }
#endif
  switch (type) {
    case CLIENT:
      /* Initialize for connection requests. */
      if (SOCKET_SUCCESS == r_cd) {
        r_cd = client_initialze(is_bind_src);
      }
      break;
    case SERVER:
      /* Initialize for waiting for connection. */
      if (SOCKET_SUCCESS == r_cd) {
        r_cd = server_initialze();
      }
      break;
    default:
      /* Unexpected processing. */
      r_cd = SOCKET_UNEXPECTED_ERROR;
      break;
  }
  return r_cd;
}

int32_t wsocket::transmit(int8_t* const data, const int32_t data_length) {
  int32_t status = 0;
  int32_t r_cd = SOCKET_SUCCESS;
  int32_t pl_len = 0;

  switch (connection_type_) {
    case SOCK_STREAM:
      /* Establish a session with the server. */
      status = connect(dst_socket_, (const sockaddr*)&dst_addr_, sizeof(dst_addr_));
      if (SOCKET_ERROR == status) {
        r_cd = terminate(BOTH);
      } else {
        /* Get the received data. */
        pl_len = sendto(dst_socket_, (const char*)&data, data_length, 0, (const sockaddr*)&dst_addr_, sizeof(dst_addr_));
        if (pl_len < 0) {
          r_cd = terminate(BOTH);
        }
      }
      break;
    case SOCK_DGRAM:
      /* Get the received data. */
      pl_len = sendto(dst_socket_, (const char*)&data, data_length, 0, (const sockaddr*)&dst_addr_, sizeof(dst_addr_));
      if (pl_len < 0) {
        r_cd = terminate(BOTH);
      }
      break;
    case SOCK_RAW:
      break;
    case SOCK_RDM:
      break;
    case SOCK_SEQPACKET:
      break;
    default:
      break;
  }
  return r_cd;
}

int32_t wsocket::receive(int8_t *data, const int32_t data_length) {
  int32_t status = 0;
  int32_t r_cd = SOCKET_SUCCESS;
  int32_t d_addr_len = sizeof(dst_addr_);
  int32_t s_addr_len = sizeof(src_addr_);
  int32_t pl_len = 0;

  switch (connection_type_) {
    case SOCK_STREAM:
      /* Accept session. */
      accept_socket_ = accept(dst_socket_, (sockaddr*)&dst_addr_, &d_addr_len);
      if (INVALID_SOCKET == accept_socket_) {
        r_cd = terminate(BOTH);
      } else {
        /* Get the received data. */
        pl_len = recvfrom(dst_socket_, (char*)&data, data_length, 0, (struct sockaddr*)&src_addr_, &s_addr_len);
        if (pl_len < 0) {
          r_cd = terminate(BOTH);
        }
      }
      break;
    case SOCK_DGRAM:
      while (true) {
        /* Get the received data. */
        pl_len = recvfrom(dst_socket_, (char*)&data, data_length, 0, (struct sockaddr*)&src_addr_, &s_addr_len);
        if (pl_len < 0) {
          r_cd = terminate(BOTH);
        } else {
          /* Exit the loop if any data is received. */
          break;
        }
      }
    case SOCK_RAW:
      break;
    case SOCK_RDM:
      break;
    case SOCK_SEQPACKET:
      break;
    default:
      break;
  }
  return r_cd;
}

int32_t wsocket::finish() {
  int32_t r_cd = SOCKET_SUCCESS;

  if (INVALID_SOCKET == dst_socket_) {
    if (0 != closesocket(dst_socket_)) {
      r_cd = SOCKET_TERMINATION_ERROR;
    }
  }
  if (INVALID_SOCKET == src_socket_) {
    if (0 != closesocket(src_socket_)) {
      r_cd = SOCKET_TERMINATION_ERROR;
    }
  }
  if (INVALID_SOCKET == accept_socket_) {
    if (0 != closesocket(accept_socket_)) {
      r_cd = SOCKET_TERMINATION_ERROR;
    }
  }
#if defined(_MSC_VER)
  if (0 != WSACleanup()) {
    r_cd = SOCKET_TERMINATION_ERROR;
  }
#endif
  return r_cd;
}

int32_t wsocket::client_initialze(int32_t is_bind_src) {
  int32_t status = 0;
  int32_t r_cd = SOCKET_SUCCESS;

  /* Get the socket FD for the destination. */
  dst_socket_ = socket(dst_addr_.sin_family, connection_type_, 0);
  if (INVALID_SOCKET == dst_socket_) {
    r_cd = terminate(DLL_UNLOAD);
  } else {
    /* When binding the source address. */
    if (1 == is_bind_src) {
      /* Get the socket FD for the source. */
      src_socket_ = socket(src_addr_.sin_family, connection_type_, 0);
      if (INVALID_SOCKET == src_socket_) {
        r_cd = terminate(BOTH);
      } else {
        /* Bind the socket for source to the address. */
        status = bind(src_socket_, (const struct sockaddr*)&src_addr_, sizeof(src_addr_));
        if (0 != status) {
          r_cd = terminate(BOTH);
        }
      }
    }
  }
  return r_cd;
}

int32_t wsocket::server_initialze() {
  int32_t status = 0;
  int32_t r_cd = SOCKET_SUCCESS;

  /* Get the socket FD for the source. */
  dst_socket_ = socket(dst_addr_.sin_family, connection_type_, 0);
  if (INVALID_SOCKET == dst_socket_) {
    r_cd = terminate(BOTH);
  } else {
    /* Bind the socket to the address. */
    status = bind(dst_socket_, (const struct sockaddr*)&dst_addr_, sizeof(dst_addr_));
    if (0 != status) {
      r_cd = terminate(BOTH);
    } else {
      /* Start waiting for a session request. */
      status = listen(dst_socket_, SOMAXCONN);
      if (SOCKET_ERROR == status) {
        r_cd = terminate(BOTH);
      }
    }
  }
  return r_cd;
}

#if defined(_MSC_VER)
int32_t wsocket::terminate(termination_t type) {
#elif defined(__GNUC__)
int32_t wsocket::terminate(termination_t type) {
#endif
  int32_t r_cd = SOCKET_INITIALIZATION_ERROR;

  if (SOCKET_CLOSE == type || BOTH == type) {
    if (INVALID_SOCKET == dst_socket_) {
      if (0 != closesocket(dst_socket_)) {
        r_cd = SOCKET_TERMINATION_ERROR;
      }
    }
    if (INVALID_SOCKET == src_socket_) {
      if (0 != closesocket(src_socket_)) {
        r_cd = SOCKET_TERMINATION_ERROR;
      }
    }
    if (INVALID_SOCKET == accept_socket_) {
      if (0 != closesocket(accept_socket_)) {
        r_cd = SOCKET_TERMINATION_ERROR;
      }
    }
  }
#if defined(_MSC_VER)
  if (DLL_UNLOAD == type || BOTH == type) {
    if (0 != WSACleanup()) {
      r_cd = SOCKET_TERMINATION_ERROR;
    }
  }
#endif
  return r_cd;
}


}