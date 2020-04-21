#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Vertex.hpp"
#include "Vector.hpp"

template<class numType>
class Triangle {
public:
    Vertex<numType>* vertexList[3];
    Triangle<numType>* triangleList[3];

    Vector<numType> beryVec1;
    Vector<numType> beryVec2;
    numType beryDenom;

    Triangle() { }
    Triangle(Vertex<numType> &v1, Vertex<numType> &v2, Vertex<numType> &v3) {
        vertexList[0] = &v1;
        vertexList[1] = &v2;
        vertexList[2] = &v3;
        
        // Berycentric Coordinates
        beryVec1.fromVertexes(v1, v3);
        beryVec2.fromVertexes(v1, v2);
        beryDenom = 1 /
                (beryVec1.dotProd(beryVec1) * beryVec2.dotProd(beryVec2) -
                beryVec1.dotProd(beryVec2) * beryVec1.dotProd(beryVec2));
    }

    bool PointInside(Vertex<numType> v) {

        // Berycentric Coordinates Method
        Vector<numType> vector1v;
        vector1v.fromVertexes(*vertexList[0], v);

        numType a = beryDenom *
                (beryVec2.dotProd(beryVec2) * beryVec1.dotProd(vector1v)) -
                (beryVec1.dotProd(beryVec2) * beryVec1.dotProd(vector1v));
        numType b = beryDenom *
                (beryVec1.dotProd(beryVec1) * beryVec2.dotProd(vector1v)) -
                (beryVec1.dotProd(beryVec2) * beryVec1.dotProd(beryVec2));

        return (a >= 0) && (b >= 0) && (a + b < 1);
    }

    bool containsVertex(Vertex<numType> v ) {
        for (int i = 0; i < 3; ++i){
            return triangleList[i] == v;
        }
    }
};

#endif //TRIANGLE_HPP
