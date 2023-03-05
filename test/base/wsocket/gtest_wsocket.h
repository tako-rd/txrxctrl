/*!
 * cryptography library
 *
 * Copyright (c) 2023 tako
 *
 * This software is released under the MIT license.
 * see https://opensource.org/licenses/MIT
 */
#ifndef TXRXCTRL_GTEST_WSOCKET_H
#define TXRXCTRL_GTEST_WSOCKET_H

#include "gtest/gtest.h"
#include "base/wsocket.h"

class GTestWSocket : public ::testing::Test {
 public:
  GTestWSocket() {};

  ~GTestWSocket() {};

  virtual void SetUp() {};

  virtual void TearDown() {};

 private:


};

#endif