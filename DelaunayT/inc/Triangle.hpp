#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Vector.hpp"

template<class numType>
class Triangle {
public:
    Vertex<numType>* vList[3];
    Triangle<numType>* tList[3];
    int indexOppT[3];

    Vector<numType> baryVec0;
    Vector<numType> baryVec1;
    numType baryDenom;

    Triangle() { }
    Triangle(Vertex<numType> *v0, Vertex<numType> *v1, Vertex<numType> *v2) {
        vList[0] = v0;
        vList[1] = v1;
        vList[2] = v2;

        tList[0] = nullptr;
        tList[1] = nullptr;
        tList[2] = nullptr;

        //indexOppT[3];
        //indexOppT[3]
        //indexOppT[3]

        calcBarycentric();
    }

    void calcBarycentric() {
        // Barycentric Coordinates
        baryVec0.fromVertexes(vList[0], vList[2]);
        baryVec1.fromVertexes(vList[0], vList[1]);
        baryDenom = 1 /
                    (baryVec0.dotProd(baryVec0) * baryVec1.dotProd(baryVec1) -
                     baryVec0.dotProd(baryVec1) * baryVec0.dotProd(baryVec1));
    }

    bool PointInside(Vertex<numType>* ver) {

        // Barycentric Coordinates Method
        Vector<numType> baryVecV;
        baryVecV.fromVertexes(vList[0], ver);

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
        baryVecV.fromVertexes(vList[0], ver);

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
        for (Vertex<numType>* u : vList){
            return *u == v;
        }
        return false;
    }

    bool operator==(Triangle t) {
        for (Vertex<numType>* v : vList) {
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
        for (auto i : vList) {
            std::cout << i;
            i->print();
        }
    }

    void printNeigh() {
        std::cout << "Neigh:";
        std::cout << "{";
        for (int i = 0; i < 3; i++) {
            if (tList[i] != 0) {
                std::cout << indexOppT[i];
                tList[i]->printVer();
            }
            std::cout << ",";
        }
        std::cout << "}" << "\n";
    }
};

#endif //TRIANGLE_HPP
