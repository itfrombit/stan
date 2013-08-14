#include <stan/math/scalar/if_else.hpp>
#include <gtest/gtest.h>

TEST(MathScalar, if_else) {
  using stan::math::if_else;
  unsigned int c = 5;
  double x = 1.0;
  double y = -1.0;
  EXPECT_FLOAT_EQ(x, if_else(c,x,y));
  c = 0;
  EXPECT_FLOAT_EQ(y, if_else(c,x,y));

  bool d = true;
  int u = 1;
  int v = -1;
  EXPECT_EQ(1.0, stan::math::if_else(d,u,v));
  d = false;
  EXPECT_FLOAT_EQ(-1.0, stan::math::if_else(d,u,v));

  EXPECT_FLOAT_EQ(1.2,if_else(true,1.2,12));
  EXPECT_FLOAT_EQ(12.0,if_else(false,1.2,12));

  EXPECT_FLOAT_EQ(1.0,if_else(true,1,12.3));
  EXPECT_FLOAT_EQ(12.3,if_else(false,1,12.3));
}

TEST(MathScalar, if_else_promote) {
  using stan::math::if_else;
  double x = 2.5;
  int y = -1;
  EXPECT_FLOAT_EQ(2.5, if_else(true,x,y));
  EXPECT_FLOAT_EQ(-1.0, if_else(false,x,y));
}
