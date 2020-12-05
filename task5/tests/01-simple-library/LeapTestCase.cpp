//
// Created by akhtyamovpavel on 5/1/20.
//

#include "LeapTestCase.h"
#include <stdexcept>
#include <Functions.h>

TEST(LeapTestCase, all) {
    ASSERT_THROW(IsLeap(-1), std::invalid_argument);
    ASSERT_TRUE(IsLeap(2008));
    ASSERT_TRUE(IsLeap(2000));
    ASSERT_FALSE(IsLeap(2001));
    ASSERT_FALSE(IsLeap(100));
}
