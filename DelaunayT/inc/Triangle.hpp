#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <iostream>
#include "Vertex.hpp"
#include "Vector.hpp"

template<class numType>
class Triangle {
public:
    Vertex<numType>* vertexList[3];
    Triangle<numType>* triangleList[3];

    Triangle() { };
    Triangle(Vertex<numType> &v1, Vertex<numType> &v2, Vertex<numType> &v3) {
        vertexList[0] = &v1;

        Vector<float> vector1to2;
        vector1to2.fromVertexes(v1, v2);

        Vector<float> vector1to3;
        vector1to3.fromVertexes(v1, v3);

        numType det = vector1to2.CrossProd(vector1to3);

        if (det > 0) {
            vertexList[1] = &v2;
            vertexList[2] = &v3;
        }
        else if (det < 0) {
            vertexList[1] = &v3;
            vertexList[2] = &v2;
        }
    }
};

#include "../src/Triangle.cpp"

#endif //TRIANGLE_HPP
