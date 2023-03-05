/*!
 * cryptography library
 *
 * Copyright (c) 2023 tako
 *
 * This software is released under the MIT license.
 * see https://opensource.org/licenses/MIT
 */
#include "base/protocol.h"

namespace txrxctrl {

protocol_id protocol::id() noexcept {
  return id_;
};

}