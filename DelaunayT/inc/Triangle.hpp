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

        // Barycentric Coordinates
        baryVec0.fromVertexes(v0, v2);
        baryVec1.fromVertexes(v0, v1);
        baryDenom = 1 /
                    (baryVec0.dotProd(baryVec0) * baryVec1.dotProd(baryVec1) -
                     baryVec0.dotProd(baryVec1) * baryVec0.dotProd(baryVec1));

        std::cout << "Triangle Construction: baryVec0:";
        baryVec0.print();
        std::cout << ". baryVec1: ";
        baryVec1.print(); std::cout << ". baryDenom: " <<baryDenom << "\n";
    }

    bool PointInside(Vertex<numType> v) {

        // Barycentric Coordinates Method
        Vector<numType> vector1v;
        vector1v.fromVertexes(vertexList[0], &v);

        std::cout << "Point vec construction:";
        baryVec0.print(); std::cout << "\n";
        baryVec1.print(); std::cout << "\n";
        vector1v.print(); std::cout << "\n";

        numType a = baryDenom *
                    (baryVec1.dotProd(baryVec1) * baryVec0.dotProd(vector1v)) -
                    (baryVec0.dotProd(baryVec1) * baryVec0.dotProd(vector1v));
        numType b = baryDenom *
                    (baryVec0.dotProd(baryVec0) * baryVec1.dotProd(vector1v)) -
                    (baryVec0.dotProd(baryVec1) * baryVec0.dotProd(baryVec1));

        //v.print();
        //std::cout << a << b << "\n";

        return (a >= 0) && (b >= 0) && (a + b <= 1);
    }

    int PointOnEdge(Vertex<numType> v) {

        Vector<numType> vector1v;
        vector1v.fromVertexes(vertexList[0], &v);

        numType a = baryDenom *
                    (baryVec1.dotProd(baryVec1) * baryVec0.dotProd(vector1v)) -
                    (baryVec0.dotProd(baryVec1) * baryVec0.dotProd(vector1v));
        numType b = baryDenom *
                    (baryVec0.dotProd(baryVec0) * baryVec1.dotProd(vector1v)) -
                    (baryVec0.dotProd(baryVec1) * baryVec0.dotProd(baryVec1));

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
