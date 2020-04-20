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

    Triangle() { }
    Triangle(Vertex<numType> &v1, Vertex<numType> &v2, Vertex<numType> &v3) {
        vertexList[0] = &v1;
        vertexList[1] = &v2;
        vertexList[2] = &v3;
    }
};

#endif //TRIANGLE_HPP
