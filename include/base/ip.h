/*!
 * cryptography library
 *
 * Copyright (c) 2023 tako
 *
 * This software is released under the MIT license.
 * see https://opensource.org/licenses/MIT
 */
#ifndef TXRXCTRL_IP_H
#define TXRXCTRL_IP_H

#include <stdint.h>
#if defined(_MSC_VER)
# include <winsock2.h>
# include <ws2tcpip.h>
#elif defined(__GNUC__)
# include <sys/socket.h>
# include <sys/types.h>
# include <arpa/inet.h>
#endif
#include <type_traits>

#include "common/result.h"
#include "base/protocol.h"
#include "base/wsocket.h"

namespace txrxctrl {

const static int32_t IP_UNEXPECTED_ERROR = int32_t(TXRXCTRL_IP & UNEXPECTED_ERROR);

template <typename Protocol, 
          bool IsBasedProtocal = std::is_base_of<protocol, Protocol>::value>
class protocol_verification {
  static_assert(IsBasedProtocal, "*** ERROR : The invalid type has been specified in template.");
};

template <typename Protocol>
class protocol_verification<Protocol, true> {};

template <typename Protocol>
class ipv4 {
 public:
  ipv4() noexcept {};

  ~ipv4() {};

  int32_t initialize() {};

  int32_t transmit() {};

  int32_t receive() {};

  int32_t finish() {};

 private:

};

template <typename Protocol>
class ipv6 {
 public:
  ipv6() noexcept {};

  ~ipv6() {};

  int32_t initialize() {};

  int32_t transmit() {};

  int32_t receive() {};

  int32_t finish() {};

 private:

};

template <typename Protocol>
class mac {
 public:
  mac() noexcept {};

  ~mac();

  int32_t initialize() {};

  int32_t transmit() {};

  int32_t receive() {};

  int32_t finish() {};

 private:

};

}

#endif