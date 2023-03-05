/*!
 * cryptography library
 *
 * Copyright (c) 2023 tako
 *
 * This software is released under the MIT license.
 * see https://opensource.org/licenses/MIT
 */
#include "gtest_wsocket.h"

#define DST_IPADDR    (int8_t *)"127.0.0.1"
#define DST_PORT      50000
#define SRC_IPADDR    (int8_t *)"127.0.0.1"
#define SRC_PORT      55000

TEST_F(GTestWSocket, NormalPattern_WSocket_001) {
  txrxctrl::wsocket ws;

  EXPECT_EQ(txrxctrl::SOCKET_SUCCESS, 
            ws.initialize(DST_IPADDR, DST_PORT, SRC_IPADDR, SRC_PORT, txrxctrl::CLIENT));
}