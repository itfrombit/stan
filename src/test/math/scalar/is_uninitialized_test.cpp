#include <gtest/gtest.h>
#include <stan/math/scalar/is_uninitialized.hpp>

TEST(MathScalar, is_uninitialized) {
  using stan::math::is_uninitialized;
  EXPECT_FALSE(is_uninitialized(1.0));
  double x = 1.0;
  EXPECT_FALSE(is_uninitialized(x));
  
  EXPECT_FALSE(is_uninitialized(3));
  int y = 3;
  EXPECT_FALSE(is_uninitialized(y));
}

