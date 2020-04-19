#include <gtest/gtest.h>

#include "Vertex.hpp"

/* NOLINT */

class VertexTest : public::testing::Test {
protected:

    Vertex<float> testVertex;

    void SetUp() override {

    }

    void TearDown() override {

    }

};

TEST_F(VertexTest, Constructor) {
    ASSERT_EQ(testVertex.X, 0);
    ASSERT_EQ(testVertex.Y, 0);
}