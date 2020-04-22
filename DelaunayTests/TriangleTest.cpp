#include <gtest/gtest.h>

#include "Triangle.hpp"

class TriangleTest : public::testing::Test {
protected:
    Vertex<float> v1;
    Vertex<float> v2;
    Vertex<float> v3;
    Triangle<float> testTriangle;

    void SetUp() override {
        v1 = Vertex<float>(0.0f, 0.0f);
        v2 = Vertex<float>(0.0f, 3.0f);
        v3 = Vertex<float>(-3.0f, 0.0f);

        testTriangle = Triangle<float>(&v1, &v2, &v3);
    }

    void TearDown() override { }
};

TEST_F(TriangleTest, VertexPointed) {
    ASSERT_EQ(testTriangle.vertexList[0], &v1);

    ASSERT_EQ(testTriangle.vertexList[1], &v2);

    ASSERT_EQ(testTriangle.vertexList[2], &v3);
}

TEST_F(TriangleTest, XValuesAccess) {
    ASSERT_EQ(testTriangle.vertexList[0]->X, v1.X);
    ASSERT_EQ(testTriangle.vertexList[1]->X, v2.X);
    ASSERT_EQ(testTriangle.vertexList[2]->X, v3.X);
}

TEST_F(TriangleTest, YValuesAccess) {
    ASSERT_EQ(testTriangle.vertexList[0]->Y, v1.Y);
    ASSERT_EQ(testTriangle.vertexList[1]->Y, v2.Y);
    ASSERT_EQ(testTriangle.vertexList[2]->Y, v3.Y);
}

TEST_F(TriangleTest, PointInside) {
    Vertex<float> insideVertex = Vertex<float>(-1.0f, 1.0f);

    ASSERT_TRUE(testTriangle.PointInside(insideVertex));
}


