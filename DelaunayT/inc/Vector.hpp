#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "Vertex.hpp"

template <class numType>
struct Vector {
    numType X;
    numType Y;

    Vector() : X(0), Y(0) { };
    Vector(numType x, numType y) : X(x), Y(y) { };

    void fromVertexes(Vertex<numType> v, Vertex<numType> u) {
        X = u.X - v.X;
        Y = u.Y - v.Y;
    }

    bool operator==(Vector v) { return (X == v.X) && (Y == v.Y); }
};


#endif //VECTOR_HPP
