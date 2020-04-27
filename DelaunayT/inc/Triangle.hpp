#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Vector.hpp"

template<class numType>
class Triangle {
public:
    Vertex<numType>* vertexList[3];
    Triangle<numType>* triangleList[3];

    Vector<numType> baryVec0;
    Vector<numType> baryVec1;
    numType baryDenom;

    Triangle() { }
    Triangle(Vertex<numType> *v0, Vertex<numType> *v1, Vertex<numType> *v2) {
        vertexList[0] = v0;
        vertexList[1] = v1;
        vertexList[2] = v2;

        triangleList[0] = nullptr;
        triangleList[1] = nullptr;
        triangleList[2] = nullptr;

        calcBarycentric();
    }

    void calcBarycentric() {
        // Barycentric Coordinates
        baryVec0.fromVertexes(vertexList[0], vertexList[2]);
        baryVec1.fromVertexes(vertexList[0], vertexList[1]);
        baryDenom = 1 /
                    (baryVec0.dotProd(baryVec0) * baryVec1.dotProd(baryVec1) -
                     baryVec0.dotProd(baryVec1) * baryVec0.dotProd(baryVec1));
    }

    bool PointInside(Vertex<numType>* ver) {

        // Barycentric Coordinates Method
        Vector<numType> baryVecV;
        baryVecV.fromVertexes(vertexList[0], ver);

        calcBarycentric();

        numType u = baryDenom *
                    (baryVec1.dotProd(baryVec1) * baryVec0.dotProd(baryVecV) -
                    baryVec0.dotProd(baryVec1) * baryVec1.dotProd(baryVecV));
        numType v = baryDenom *
                    (baryVec0.dotProd(baryVec0) * baryVec1.dotProd(baryVecV) -
                    baryVec0.dotProd(baryVec1) * baryVec0.dotProd(baryVecV));

        return (u >= 0) && (v >= 0) && (u + v <= 1);
    }

    int PointOnEdge(Vertex<numType>* ver) {

        Vector<numType> baryVecV;
        baryVecV.fromVertexes(vertexList[0], ver);

        numType u = baryDenom *
                    (baryVec1.dotProd(baryVec1) * baryVec0.dotProd(baryVecV) -
                     baryVec0.dotProd(baryVec1) * baryVec1.dotProd(baryVecV));
        numType v = baryDenom *
                    (baryVec0.dotProd(baryVec0) * baryVec1.dotProd(baryVecV) -
                     baryVec0.dotProd(baryVec1) * baryVec0.dotProd(baryVecV));

        if (u == 0) {
            return 2;
        } else if (v == 0) {
            return 1;
        } else if (u + v == 1) {
            return 0;
        } else {
            return -1;
        }
    }

    bool containsVertex(Vertex<numType> v ) {
        for (Vertex<numType>* u : vertexList){
            return *u == v;
        }
        return false;
    }

    bool operator==(Triangle t) {
        for (Vertex<numType>* v : vertexList) {
            return !t.containsVertex(v);
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
            std::cout << i;
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
        std::cout << "}" << "\n";
    }
};

#endif //TRIANGLE_HPP
