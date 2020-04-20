#include <gtest/gtest.h>

#include "Vector.hpp"

class VectorTest : public::testing::Test {
protected:
    Vector<float> testVector;

    void SetUp() override {
        testVector = Vector<float>();
    }

    void TearDown() override { }
};

TEST_F(VectorTest, Constructor) {
    ASSERT_EQ(testVector.X, 0);
    ASSERT_EQ(testVector.Y, 0);
}

TEST_F(VectorTest, ParametersConstructor) {
    testVector = Vector<float>(1.1f,2.2f);
    ASSERT_EQ(testVector.X, 1.1f);
    ASSERT_EQ(testVector.Y, 2.2f);
}

TEST_F(VectorTest, FromVertex) {
    Vertex<float> vertexA = Vertex<float>(0.0f, 0.0f);
    Vertex<float> vertexB = Vertex<float>(1.0f, 1.0f);

    testVector.fromVertexes(vertexA, vertexB);
    ASSERT_EQ(testVector.X, 1.0f);
    ASSERT_EQ(testVector.Y, 1.0f);
}

TEST_F(VectorTest, dotProdShouldBe10) {
    Vector<float> vectorA = Vector<float>(2.0f, 2.0f);
    Vector<float> vectorB = Vector<float>(3.0f, 2.0f);

    ASSERT_EQ(vectorA.dotProd(vectorB), 10.0f);
}