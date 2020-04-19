#include <gtest/gtest.h>

#include "Vertex.hpp"

class VertexTest : public::testing::Test {
protected:

    Vertex<float> testVertexF;
    Vertex<double> testVertexD;

    void SetUp() override {

    }

    void TearDown() override {

    }

};

TEST_F(VertexTest, FloatConstructor) {
    ASSERT_EQ(testVertexF.X, 0);
    ASSERT_EQ(testVertexF.Y, 0);
}

TEST_F(VertexTest, FloatConstructorParameters) {
    testVertexF = Vertex<float>(1.1f,2.2f);

    ASSERT_EQ(testVertexF.X, 1.1f);
    ASSERT_EQ(testVertexF.Y, 2.2f);
}

TEST_F(VertexTest, DoubleConstructor) {
    ASSERT_EQ(testVertexD.X, 0);
    ASSERT_EQ(testVertexD.Y, 0);
}

TEST_F(VertexTest, DoubleConstructorParameters) {
    testVertexD = Vertex<double>(1.1f,2.2f);

    ASSERT_EQ(testVertexD.X, 1.1f);
    ASSERT_EQ(testVertexD.Y, 2.2f);
}


TEST_F(VertexTest,EqualsOperator) {
    testVertexF = Vertex<float>(1.1f,2.2f);
    Vertex<float> equalVertex = Vertex<float>(1.1f,2.2f);
    ASSERT_TRUE(testVertexF == equalVertex);
}
