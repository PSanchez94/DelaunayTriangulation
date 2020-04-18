//
// Created by KasiSanchez on 17/04/2020.
//

#include "gtest/gtest.h"

TEST(FirstTest, Is1GreaterThan2) {
    EXPECT_GT(1, 2);
}

TEST(FirstTest, Is2GreaterThan1) {
    EXPECT_GT(2, 1);
}

TEST(FirstTest, Is2LessThan1) {
    EXPECT_LT(2, 1);
}

TEST(FirstTest, Is1LessThan2) {
    EXPECT_LT(1, 2);
}