//
// Created by KasiSanchez on 20/04/2020.
//
#ifndef DELAUNAYT_HPP
#define DELAUNAYT_HPP

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include "Triangle.hpp"

template<class numType>
class DelaunayT {
private:
    std::vector<Vertex<numType> *> vertexVec;
    std::vector<Vertex<numType> *> borderVertexVec;

    std::vector<Triangle<numType> *> triangleVec;
    std::vector<Triangle<numType> *> boundingTriangles;
    std::vector<Triangle<numType> *> allTriangles;

    Vertex<numType>* swVertex;
    Vertex<numType>* seVertex;
    Vertex<numType>* neVertex;
    Vertex<numType>* nwVertex;

public:
    DelaunayT() {
        vertexVec = std::vector<Vertex<numType> *>();
        borderVertexVec = std::vector<Vertex<numType> *>();

        triangleVec = std::vector<Triangle<numType> *>();
        boundingTriangles = std::vector<Triangle<numType> *>();
        allTriangles = std::vector<Triangle<numType> *>();

        swVertex = new Vertex<numType>();
        seVertex = new Vertex<numType>();
        neVertex = new Vertex<numType>();
        nwVertex = new Vertex<numType>();
    }
    explicit DelaunayT(std::vector<std::vector<numType> > input) {

        findBoundingTriangles(input);
        std::random_shuffle ( input.begin(), input.end() );

        for (auto it = input.begin(); it != input.end(); ++it) {
            Vertex<numType>* v = new Vertex<numType>((*it)[0], (*it)[1]);
            vertexVec.push_back(v);
            addPoint(v);
        }
    }

    void addPoint(Vertex<numType> *v) {
        for (auto t : allTriangles) {
            std::cout << "Triangle address: " << &t << ". ";
            t->print();
            std::cout << "Point to add";
            v->print();
            std::cout << "\n";

            if (t->PointInside(v)) {
                Triangle<numType>* ATriangle;
                Triangle<numType>* BTriangle;

                Vertex<numType>* auxVer[3] = {t->vertexList[0], t->vertexList[1], t->vertexList[2]};
                Triangle<numType>* auxTri[3] = {t->triangleList[0], t->triangleList[1], t->triangleList[2]};

                if (t->PointOnEdge(v) != -1) {
                    std::cout << "SHOULD THIS BE ON EDGE?";

                    int i = t->PointOnEdge(v);

                    ATriangle = new Triangle<numType>(auxVer[i], auxVer[(i + 1) % 3], v);
                    BTriangle = new Triangle<numType>(auxVer[i], v, auxVer[(i + 2) % 3]);
                    Triangle<numType>* CTriangle = new Triangle<numType>(auxVer[i], auxVer[(i + 1) % 3], v);
                    t->vertexList[0] = auxVer[i];
                    t->vertexList[1] = v;
                    t->vertexList[2] = auxVer[(i + 2) % 3];

                    ATriangle->triangleList[0] = t;
                    ATriangle->triangleList[1] = BTriangle;
                    ATriangle->triangleList[2] = auxTri[2];
                    auxTri[2] = ATriangle;

                    BTriangle->triangleList[0] = CTriangle;
                    BTriangle->triangleList[1] = auxTri[1];
                    BTriangle->triangleList[2] = ATriangle;
                    auxTri[1] = BTriangle;

                    CTriangle->triangleList[0] = BTriangle;
                    CTriangle->triangleList[1] = t;
                    CTriangle->triangleList[2] = auxTri[2];
                    auxTri[2] = CTriangle;

                    t->triangleList[0] = ATriangle;
                    t->triangleList[1] = auxTri[1];
                    t->triangleList[2] = CTriangle;
                    auxTri[1] = t;

                    allTriangles.push_back(CTriangle);
                    for (auto it2 : borderVertexVec) {
                        borderCheck(CTriangle, it2);
                    }
                } else {
                    std::cout << "Started Triangle Construction: ";

                    // Vertex definition
                    ATriangle = new Triangle<numType>(v, t->vertexList[0], t->vertexList[1]);
                    BTriangle = new Triangle<numType>(v, t->vertexList[1], t->vertexList[2]);
                    t->vertexList[0] = v;
                    t->vertexList[1] = auxVer[2];
                    t->vertexList[2] = auxVer[0];

                    // Neighbout definition
                    ATriangle->triangleList[0] = auxTri[2];
                    ATriangle->triangleList[1] = BTriangle;
                    ATriangle->triangleList[2] = t;
                    auxTri[2] = ATriangle;

                    BTriangle->triangleList[0] = auxTri[0];
                    BTriangle->triangleList[1] = t;
                    BTriangle->triangleList[2] = ATriangle;
                    auxTri[0] = BTriangle;

                    t->triangleList[0] = auxTri[1];
                    t->triangleList[1] = ATriangle;
                    t->triangleList[2] = BTriangle;
                    auxTri[1] = t;

                    std::cout << "Memory reeplacement; ";
                    ATriangle->print();
                    BTriangle->print();
                    t->print();
                    std::cout << "\n";
                    std::cout << "This doesn't look like an issue";
                }

                t->calcBarycentric();
                allTriangles.push_back(ATriangle);
                allTriangles.push_back(BTriangle);
                for (auto it2 : borderVertexVec) {
                    borderCheck(ATriangle, it2);
                    borderCheck(BTriangle, it2);
                    borderCheck(t, it2);
                }

                v->print();
                std::cout << " Vertex was added" << "\n";

                break;
            } else {
                v->print();
                std::cout << " Vertex not inside this triangle" << "\n";
            }
        }
    }

    void findBoundingTriangles(std::vector<std::vector<numType>> input) {
        swVertex = new Vertex<numType>(0, 0);
        seVertex = new Vertex<numType>(0, 0);
        neVertex = new Vertex<numType>(0, 0);
        nwVertex = new Vertex<numType>(0, 0);

        for (auto it = input.begin(); it != input.end(); ++it) {
            numType percentage = 0.01;

            if ((*it)[0] <= swVertex->X) {
                swVertex->X = (*it)[0] + ((*it)[0] *percentage);
                nwVertex->X = (*it)[0] + ((*it)[0] *percentage);
            }
            else if (((*it)[0]) >= seVertex->X) {
                seVertex->X = (*it)[0] + ((*it)[0] *percentage);
                neVertex->X = (*it)[0] + ((*it)[0] *percentage);
            }
            if (((*it)[1]) <= swVertex->Y) {
                swVertex->Y = (*it)[1] + ((*it)[1] *percentage);
                seVertex->Y = (*it)[1] + ((*it)[1] *percentage);
            }
            else if (((*it)[1]) >= nwVertex->Y) {
                nwVertex->Y = (*it)[1] + ((*it)[1] *percentage);
                neVertex->Y = (*it)[1] + ((*it)[1] *percentage);
            }
        }

        borderVertexVec.push_back(swVertex);
        borderVertexVec.push_back(seVertex);
        borderVertexVec.push_back(neVertex);
        borderVertexVec.push_back(nwVertex);

        for (auto i : borderVertexVec) {
            i->print();
            std::cout << "\n";
        }

        Triangle<numType>* topTriangle = new Triangle<numType>(neVertex, nwVertex, swVertex);
        Triangle<numType>* botTriangle = new Triangle<numType>(swVertex, seVertex, neVertex);
        topTriangle->triangleList[1] = botTriangle;
        botTriangle->triangleList[1] = topTriangle;

        boundingTriangles.push_back(topTriangle);
        boundingTriangles.push_back(botTriangle);

        allTriangles.push_back(topTriangle);
        allTriangles.push_back(botTriangle);
    }

    void borderCheck(Triangle<numType> *t, Vertex<numType> *v) {
        if(t->containsVertex(*v)) { boundingTriangles.push_back(t); }
        else { triangleVec.push_back(t); }
    }

    std::vector<Vertex<numType> *> getBorderVertexes() {
        return borderVertexVec;
    }

    std::vector<Triangle<numType> *> getTriangles() {
        return triangleVec;
    }

    std::vector<Triangle<numType> *> getVertexes() {
        return vertexVec;
    }

    std::vector<Triangle<numType> *> getAllTriangles() {
        return allTriangles;
    }

};

#endif //DELAUNAYT_HPP
