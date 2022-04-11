/* Copyright (c) 2020, 2021, Oracle and/or its affiliates.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License, version 2.0,
   as published by the Free Software Foundation.

   This program is also distributed with certain software (including
   but not limited to OpenSSL) that is licensed under separate terms,
   as designated in a particular file or component or in included license
   documentation.  The authors of MySQL hereby grant you an additional
   permission to link the program and your derivative works with the
   separately licensed software that they have included with MySQL.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License, version 2.0, for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA
*/

#include <array>
#include <chrono>
#include <vector>

#include "sql/memory/aligned_atomic.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace memory {
namespace unittests {

class Aligned_atomic_test : public ::testing::Test {
 protected:
  Aligned_atomic_test() = default;
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Aligned_atomic_test, Class_template_test) {
  std::string str{"012345678"};
  memory::Aligned_atomic<int> atm{1};
  EXPECT_EQ(atm->load(), 1);
  atm->store(2);
  EXPECT_EQ((*atm).load(), 2);
  EXPECT_EQ(atm.size(), sizeof(std::atomic<int>));
  EXPECT_EQ(atm.allocated_size(), memory::cache_line_size());

  memory::Aligned_atomic<int> atm2{std::move(atm)};
  EXPECT_EQ(atm2->load(), 2);
  EXPECT_EQ(atm == nullptr, true);
  memory::Aligned_atomic<int> atm3;
  atm3 = std::move(atm2);
  EXPECT_EQ(atm3->load(), 2);
}

}  // namespace unittests
}  // namespace memory
