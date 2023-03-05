/*!
 * cryptography library
 *
 * Copyright (c) 2023 tako
 *
 * This software is released under the MIT license.
 * see https://opensource.org/licenses/MIT
 */
#ifndef TXRXCTRL_SOCKET_H
#define TXRXCTRL_SOCKET_H

#include <stdint.h>
#if defined(_MSC_VER)
# include <winsock2.h>
# include <ws2tcpip.h>
#elif defined(__GNUC__)
# include <sys/socket.h>
# include <sys/types.h>
# include <arpa/inet.h>
#endif
#include "common/result.h"

#if defined(_MSC_VER)
# define LIB_MAJOR_VER    2
# define LIB_MINOR_VER    2
#elif defined(__GNUC__)
#endif


namespace txrxctrl {

const static int32_t SOCKET_SUCCESS = int32_t(TXRXCTRL_SOCKET & SUCCESS);
const static int32_t SOCKET_INITIALIZATION_ERROR = int32_t(TXRXCTRL_SOCKET & INITIALIZATION_ERROR);
const static int32_t SOCKET_TERMINATION_ERROR = int32_t(TXRXCTRL_SOCKET & TERMINATION_ERROR);
const static int32_t SOCKET_UNEXPECTED_ERROR = int32_t(TXRXCTRL_SOCKET & UNEXPECTED_ERROR);
const static int32_t SOCKET_PARAMETERS_ERROR = int32_t(TXRXCTRL_SOCKET & PARAMETERS_ERROR);

typedef enum socket_type {
  NOT_SET = 0,
  CLIENT,
  SERVER,
} socket_type_t;

typedef enum termination_type {
  SOCKET_CLOSE = 0,
  DLL_UNLOAD,
  BOTH,
} termination_t;

class wsocket {
 public:
  wsocket() noexcept : src_addr_{0},
                       dst_addr_{0},
                       dst_socket_(-1),
                       src_socket_(-1),
                       socket_type_(NOT_SET),
                       connection_type_(SOCK_STREAM) {};

  wsocket(const wsocket& other) noexcept;

  wsocket(const wsocket&& other) noexcept;

  ~wsocket();

  int32_t initialize(int8_t* const dst_addr, const uint16_t dst_port, 
                     int8_t* const src_addr, const uint16_t src_port,
                     socket_type_t type);

  int32_t transmit(int8_t* const data, const int32_t data_length);

  int32_t receive(int8_t* data, const int32_t data_length);

  int32_t finish();

 private:
#if defined(_MSC_VER)
  int32_t terminate(termination_t type);
#elif defined(__GNUC__)
  int32_t terminate(termination_t type);
#endif
  int32_t client_initialze(int32_t is_bind);

  int32_t server_initialze();
#if defined(_MSC_VER)
  SOCKET dst_socket_;

  SOCKET src_socket_;

  SOCKET accept_socket_;

  WSADATA wsa_data_;
#elif defined(__GNUC__)
  int32_t dst_socket_;

  int32_t src_socket_;

  int32_t acpt_socket_;
#endif
  struct sockaddr_in src_addr_;

  struct sockaddr_in dst_addr_;

  socket_type_t socket_type_;

  int32_t connection_type_;
};

}

#endif