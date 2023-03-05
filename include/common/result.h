/*!
 * cryptography library
 *
 * Copyright (c) 2023 tako
 *
 * This software is released under the MIT license.
 * see https://opensource.org/licenses/MIT
 */
#ifndef TXRXCTRL_RESULT_H
#define TXRXCTRL_RESULT_H

namespace txrxctrl {

typedef enum module_code {
  TXRXCTRL_IP = 0x00000000,
  TXRXCTRL_PROTOCOL = 0x00010000,
  TXRXCTRL_SOCKET = 0x00020000,
} mcd_t;

typedef enum return_code {
  SUCCESS = 0x00000000,
  INITIALIZATION_ERROR,
  TERMINATION_ERROR,
  UNEXPECTED_ERROR,
  PARAMETERS_ERROR,
  UNDER_DEVELOPMENT = 0x0000FFFF
} rcd_t;

}
#endif