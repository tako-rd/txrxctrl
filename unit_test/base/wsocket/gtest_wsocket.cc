/*!
 * cryptography library
 *
 * Copyright (c) 2023 tako
 *
 * This software is released under the MIT license.
 * see https://opensource.org/licenses/MIT
 */
#include "gtest_wsocket.h"

#define DST_IPADDR            (int8_t *)"192.168.10.2"
#define DST_PORT              50000
#define SRC_IPADDR            (int8_t *)"192.168.10.2"
#define SRC_PORT              55000
#define PAYLOAD_DATA          (int8_t *)"Test payload data."

 /***********************************/
 /* Client-side initialization test */
 /***********************************/
TEST_F(GTestWSocket, NormalPattern_WSocket_initialize_001) {
  txrxctrl::wsocket ws;

  EXPECT_EQ(txrxctrl::SOCKET_SUCCESS, 
            ws.initialize(DST_IPADDR, DST_PORT, SRC_IPADDR, SRC_PORT, txrxctrl::CLIENT, SOCK_STREAM));
}

TEST_F(GTestWSocket, NormalPattern_WSocket_initialize_002) {
  txrxctrl::wsocket ws;

  EXPECT_EQ(txrxctrl::SOCKET_SUCCESS,
            ws.initialize(DST_IPADDR, DST_PORT, SRC_IPADDR, SRC_PORT, txrxctrl::CLIENT, SOCK_DGRAM));
}

TEST_F(GTestWSocket, NormalPattern_WSocket_initialize_003) {
  txrxctrl::wsocket ws;

  EXPECT_EQ(txrxctrl::SOCKET_SUCCESS,
            ws.initialize(DST_IPADDR, DST_PORT, SRC_IPADDR, SRC_PORT, txrxctrl::CLIENT, SOCK_RAW));
}

TEST_F(GTestWSocket, NormalPattern_WSocket_initialize_004) {
  txrxctrl::wsocket ws;

  EXPECT_EQ(txrxctrl::SOCKET_SUCCESS,
            ws.initialize(DST_IPADDR, DST_PORT, SRC_IPADDR, SRC_PORT, txrxctrl::CLIENT, SOCK_RDM));
}

TEST_F(GTestWSocket, NormalPattern_WSocket_initialize_005) {
  txrxctrl::wsocket ws;

  EXPECT_EQ(txrxctrl::SOCKET_SUCCESS,
            ws.initialize(DST_IPADDR, DST_PORT, SRC_IPADDR, SRC_PORT, txrxctrl::CLIENT, SOCK_SEQPACKET));
}

/***********************************/
/* Server-side initialization test */
/***********************************/
TEST_F(GTestWSocket, NormalPattern_WSocket_initialize_006) {
  txrxctrl::wsocket ws;

  EXPECT_EQ(txrxctrl::SOCKET_SUCCESS,
            ws.initialize(DST_IPADDR, DST_PORT, SRC_IPADDR, SRC_PORT, txrxctrl::SERVER, SOCK_STREAM));
}

TEST_F(GTestWSocket, NormalPattern_WSocket_initialize_007) {
  txrxctrl::wsocket ws;

  EXPECT_EQ(txrxctrl::SOCKET_SUCCESS,
            ws.initialize(DST_IPADDR, DST_PORT, SRC_IPADDR, SRC_PORT, txrxctrl::SERVER, SOCK_DGRAM));
}

TEST_F(GTestWSocket, NormalPattern_WSocket_initialize_008) {
  txrxctrl::wsocket ws;

  EXPECT_EQ(txrxctrl::SOCKET_SUCCESS,
            ws.initialize(DST_IPADDR, DST_PORT, SRC_IPADDR, SRC_PORT, txrxctrl::SERVER, SOCK_RAW));
}

TEST_F(GTestWSocket, NormalPattern_WSocket_initialize_009) {
  txrxctrl::wsocket ws;

  EXPECT_EQ(txrxctrl::SOCKET_SUCCESS,
            ws.initialize(DST_IPADDR, DST_PORT, SRC_IPADDR, SRC_PORT, txrxctrl::SERVER, SOCK_RDM));
}

TEST_F(GTestWSocket, NormalPattern_WSocket_initialize_010) {
  txrxctrl::wsocket ws;

  EXPECT_EQ(txrxctrl::SOCKET_SUCCESS,
            ws.initialize(DST_IPADDR, DST_PORT, SRC_IPADDR, SRC_PORT, txrxctrl::SERVER, SOCK_SEQPACKET));
}

/*****************************/
/* Client-side transmit test */
/*****************************/
TEST_F(GTestWSocket, NormalPattern_WSocket_transmit_001) {
  txrxctrl::wsocket ws;

  EXPECT_EQ(txrxctrl::SOCKET_SUCCESS,
            ws.initialize(DST_IPADDR, DST_PORT, SRC_IPADDR, SRC_PORT, txrxctrl::CLIENT, SOCK_STREAM));

  EXPECT_EQ(txrxctrl::SOCKET_SUCCESS, ws.transmit(PAYLOAD_DATA, sizeof(PAYLOAD_DATA)));
}

TEST_F(GTestWSocket, NormalPattern_WSocket_transmit_002) {
  txrxctrl::wsocket ws;

  EXPECT_EQ(txrxctrl::SOCKET_SUCCESS,
            ws.initialize(DST_IPADDR, DST_PORT, SRC_IPADDR, SRC_PORT, txrxctrl::CLIENT, SOCK_DGRAM));

  EXPECT_EQ(txrxctrl::SOCKET_SUCCESS, ws.transmit(PAYLOAD_DATA, sizeof(PAYLOAD_DATA)));
}

TEST_F(GTestWSocket, NormalPattern_WSocket_transmit_003) {
  txrxctrl::wsocket ws;

  EXPECT_EQ(txrxctrl::SOCKET_SUCCESS,
            ws.initialize(DST_IPADDR, DST_PORT, SRC_IPADDR, SRC_PORT, txrxctrl::CLIENT, SOCK_RAW));

  EXPECT_EQ(txrxctrl::SOCKET_SUCCESS, ws.transmit(PAYLOAD_DATA, sizeof(PAYLOAD_DATA)));
}

TEST_F(GTestWSocket, NormalPattern_WSocket_transmit_004) {
  txrxctrl::wsocket ws;

  EXPECT_EQ(txrxctrl::SOCKET_SUCCESS,
            ws.initialize(DST_IPADDR, DST_PORT, SRC_IPADDR, SRC_PORT, txrxctrl::CLIENT, SOCK_RDM));

  EXPECT_EQ(txrxctrl::SOCKET_SUCCESS, ws.transmit(PAYLOAD_DATA, sizeof(PAYLOAD_DATA)));
}

TEST_F(GTestWSocket, NormalPattern_WSocket_transmit_005) {
  txrxctrl::wsocket ws;

  EXPECT_EQ(txrxctrl::SOCKET_SUCCESS,
            ws.initialize(DST_IPADDR, DST_PORT, SRC_IPADDR, SRC_PORT, txrxctrl::CLIENT, SOCK_SEQPACKET));

  EXPECT_EQ(txrxctrl::SOCKET_SUCCESS, ws.transmit(PAYLOAD_DATA, sizeof(PAYLOAD_DATA)));
}

/*****************************/
/* Server-side transmit test */
/*****************************/