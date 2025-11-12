#include <gtest/gtest.h>
#include "four.h"

TEST(FourTests, FillingConstructor) {
    Four num(3, 2);
    EXPECT_EQ(num.toString(), "222");
}

TEST(FourTests, InitializerListConstructor) {
    Four num{1, 2, 0};
    EXPECT_EQ(num.toString(), "120");
}

TEST(FourTests, StringConstructor) {
    Four num("210");
    EXPECT_EQ(num.toString(), "210");
}

TEST(FourTests, CopyConstructor) {
    Four original("123");
    Four copy = original;
    EXPECT_EQ(original.toString(), copy.toString());
}

TEST(FourTests, Equals) {
    Four num1("123");
    Four num2("123");
    Four num3("321");
    
    EXPECT_TRUE(num1.equals(num2));
    EXPECT_FALSE(num1.equals(num3));
}

TEST(FourTests, GreaterThan) {
    Four num1("321");
    Four num2("123");
    
    EXPECT_TRUE(num1.greaterThan(num2));
    EXPECT_FALSE(num2.greaterThan(num1));
}

TEST(FourTests, LessThan) {
    Four num1("12");
    Four num2("21");
    
    EXPECT_TRUE(num1.lessThan(num2));
    EXPECT_FALSE(num2.lessThan(num1));
}

TEST(FourTests, Add) {
    Four num1("12");
    Four num2("21");
    Four result = num1.add(num2);
    EXPECT_EQ(result.toString(), "33");
}

TEST(FourTests, Add1) {
    Four num1("33");
    Four num2("1");
    Four result = num1.add(num2);
    EXPECT_EQ(result.toString(), "100");
}

TEST(FourTests, Subtract) {
    Four num1("32");
    Four num2("21");
    Four result = num1.subtract(num2);
    EXPECT_EQ(result.toString(), "11");
}

TEST(FourTests, SubtractNegativeResult) {
    Four num1("12");
    Four num2("21");
    EXPECT_THROW(num1.subtract(num2), std::invalid_argument);
}
