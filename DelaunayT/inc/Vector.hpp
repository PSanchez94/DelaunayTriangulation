#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <math.h>

#include "Vertex.hpp"

template <class numType>
struct Vector {
    numType X;
    numType Y;

    Vector() : X(0), Y(0) { }
    Vector(numType x, numType y) : X(x), Y(y) { }

    void fromVertexes(Vertex<numType> *v, Vertex<numType> *u) {
        X = u->X - v->X;
        Y = u->Y - v->Y;

//        numType length = sqrt((X * X) + (Y * Y));
//        X = X / length;
//        Y = Y / length;
    }

    bool operator==(Vector v) { return (X == v.X) && (Y == v.Y); }

    numType dotProd(Vector v) {
        return (X * v.X) + (Y * v.Y);
    };

    numType normVal(Vector<numType> v) {
        return (X * v.Y) - (Y * v.X);
    }

    void print() {
        std::cout << "(" << X << ", " << Y << ")";
    }
};

#endif //VECTOR_HPP
