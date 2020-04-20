#include <gtest/gtest.h>

#include "DelaunayT.hpp"

class DelaunayTTest : public::testing::Test {
protected:

    Vertex<float> swVertex;
    Vertex<float> seVertex;
    Vertex<float> neVertex;
    Vertex<float> nwVertex;

    DelaunayT<float> testTriangulation;

    void SetUp() override {
        swVertex = Vertex<float>(-1.0f, -1.0f);
        seVertex = Vertex<float>(1.0f, -1.0f);
        neVertex = Vertex<float>(1.0f, 1.0f);
        nwVertex = Vertex<float>(-1.0f, 1.0f);
    }

    void TearDown() override { }
};
