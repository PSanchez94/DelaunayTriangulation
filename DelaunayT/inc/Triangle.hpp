#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Vector.hpp"

template<class numType>
class Triangle {
public:
    Vertex<numType>* vertexList[3];
    Triangle<numType>* triangleList[3];

    Vector<numType> baryVec1;
    Vector<numType> baryVec2;
    numType baryDenom;

    Triangle() { }
    Triangle(Vertex<numType> &v0, Vertex<numType> &v1, Vertex<numType> &v2) {
        vertexList[0] = &v0;
        vertexList[1] = &v1;
        vertexList[2] = &v2;

        triangleList[0] = nullptr;
        triangleList[1] = nullptr;
        triangleList[2] = nullptr;

        // Barycentric Coordinates
        baryVec1.fromVertexes(v0, v2);
        baryVec2.fromVertexes(v0, v1);
        baryDenom = 1 /
                    (baryVec1.dotProd(baryVec1) * baryVec2.dotProd(baryVec2) -
                 baryVec1.dotProd(baryVec2) * baryVec1.dotProd(baryVec2));
    }

    bool PointInside(Vertex<numType> v) {

        // Barycentric Coordinates Method
        Vector<numType> vector1v;
        vector1v.fromVertexes(*vertexList[0], v);

        numType a = baryDenom *
                    (baryVec2.dotProd(baryVec2) * baryVec1.dotProd(vector1v)) -
                    (baryVec1.dotProd(baryVec2) * baryVec1.dotProd(vector1v));
        numType b = baryDenom *
                    (baryVec1.dotProd(baryVec1) * baryVec2.dotProd(vector1v)) -
                    (baryVec1.dotProd(baryVec2) * baryVec1.dotProd(baryVec2));

        return (a > 0) && (b > 0) && (a + b < 1);
    }

    int PointOnEdge(Vertex<numType> v) {

        Vector<numType> vector1v;
        vector1v.fromVertexes(*vertexList[0], v);

        numType a = baryDenom *
                    (baryVec2.dotProd(baryVec2) * baryVec1.dotProd(vector1v)) -
                    (baryVec1.dotProd(baryVec2) * baryVec1.dotProd(vector1v));
        numType b = baryDenom *
                    (baryVec1.dotProd(baryVec1) * baryVec2.dotProd(vector1v)) -
                    (baryVec1.dotProd(baryVec2) * baryVec1.dotProd(baryVec2));

        if (a == 0) {
            return 0;
        } else if (b == 0) {
            return 1;
        } else if (a + b == 1) {
            return 2;
        } else {
            return -1;
        }
    }

    bool containsVertex(Vertex<numType> v ) {
        for (auto u : vertexList){
            return *u == v;
        }
        return false;
    }

    bool operator==(Triangle t) {
        for (auto v : vertexList) {
            return !t.containsVertex(*v);
        }
        return false;
    }

    void print() {
        printVer();
        std::cout << "\n";
        printNeigh();
    }

    void printVer() {
        std::cout << "Ver:";
        for (auto i : vertexList) {
            i->print();
        }
    }

    void printNeigh() {
        std::cout << "Neigh:";
        std::cout << "{";
        for (auto i : triangleList) {
            if (i != nullptr) {
                i->printVer();
            }
            std::cout << ",";
        }
        std::cout << "}";
    }
};

#endif //TRIANGLE_HPP
