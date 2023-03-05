/*!
 * cryptography library
 *
 * Copyright (c) 2023 tako
 *
 * This software is released under the MIT license.
 * see https://opensource.org/licenses/MIT
 */
#include "protocol/tcp.h"

namespace txrxctrl {

const static int32_t PROTOCOL_SUCCESS = TXRXCTRL_PROTOCOL + SUCCESS;

tcp::tcp() noexcept {
  id_ = TCP;
}

tcp::~tcp() {

}

int32_t tcp::form(int8_t *data, const int32_t size) {

  return PROTOCOL_SUCCESS;
}


}
