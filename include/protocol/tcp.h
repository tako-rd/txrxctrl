/*!
 * cryptography library
 *
 * Copyright (c) 2023 tako
 *
 * This software is released under the MIT license.
 * see https://opensource.org/licenses/MIT
 */
#ifndef TXRXCTRL_TCP_H
#define TXRXCTRL_TCP_H

#include "common/result.h"
#include "base/ip.h"

namespace txrxctrl {

class tcp : public protocol {
 public:
  tcp() noexcept;

  ~tcp();

  int32_t form(int8_t *data, const int32_t size);

 private:
  


};

}

#endif