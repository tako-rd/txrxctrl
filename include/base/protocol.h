/*!
 * cryptography library
 *
 * Copyright (c) 2023 tako
 *
 * This software is released under the MIT license.
 * see https://opensource.org/licenses/MIT
 */
#ifndef TXRXCTRL_PROTOCOL_H
#define TXRXCTRL_PROTOCOL_H

#include <stdint.h>

#include "common/result.h"

namespace txrxctrl {

typedef enum protocol_id {
  TCP = 0,
  UNKNOWN = 0x0000FFFF,
} protocol_id;

class protocol {
 public:
  protocol() noexcept : id_(UNKNOWN) {};

  ~protocol() {};

  protocol_id id() noexcept;

  int32_t form(int8_t *data, const int32_t size) {};

 protected:
  protocol_id id_;
};

}
#endif