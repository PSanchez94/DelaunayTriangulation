//
// Created by KasiSanchez on 20/04/2020.
//
#ifndef DELAUNAYT_HPP
#define DELAUNAYT_HPP

#include <vector>
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
    }
    explicit DelaunayT(std::vector<std::vector<numType> > input) {

        findBoundingTriangles(input);
        std::random_shuffle ( input.begin(), input.end() );

        for (auto it = input.begin(); it != input.end(); ++it) {
            Vertex<numType>* v = new Vertex<numType>((*it)[0], (*it)[1]);
            vertexVec.push_back(v);
            addPoint(v);
        }

        std::cout << "Done building. " << "\n" << "Triangles Created: ";
        std::cout << allTriangles.size() << "\n";
        std::cout << "Draw Triangles: " << triangleVec.size() << "\n";
        std::cout << "Border Triangles: " << boundingTriangles.size() << "\n";
    }

    void addPoint(Vertex<numType> *v) {
        for (Triangle<numType>* t : allTriangles) {
            if (t->PointInside(v)) {
                Triangle<numType>* ATriangle;
                Triangle<numType>* BTriangle;

                Vertex<numType>* auxVer[3];
                Triangle<numType>* auxTri[3];

                std::cout << auxTri[0];
                if (t->PointOnEdge(v) != -1) {
                    int i = t->PointOnEdge(v);

                    auxVer[i] = t->vertexList[i];
                    auxVer[(i + 1) % 3] = t->vertexList[(i + 1) % 3];
                    auxVer[(i + 2) % 3] = t->vertexList[(i + 2) % 3];

                    auxTri[i] = t->triangleList[i];
                    auxTri[(i + 1) % 3] = t->triangleList[(i + 1) % 3];
                    auxTri[(i + 2) % 3] = t->triangleList[(i + 2) % 3];

                    ATriangle = new Triangle<numType>(auxVer[i], auxVer[(i + 1) % 3], v);
                    t->vertexList[0] = auxVer[i];
                    t->vertexList[1] = v;
                    t->vertexList[2] = auxVer[(i + 2) % 3];

                    ATriangle->triangleList[1] = t;
                    ATriangle->triangleList[2] = auxTri[2];

                    t->triangleList[1] = auxTri[1];
                    t->triangleList[2] = ATriangle;

                    if (auxTri[0] != 0) {
                        BTriangle = new Triangle<numType>(
                                auxTri[0]->vertexList[i],
                                v,
                                auxTri[0]->vertexList[(i + 2) % 3]);
                        Triangle<numType>* CTriangle = new Triangle<numType>(
                                auxTri[0]->vertexList[i],
                                auxTri[0]->vertexList[(i + 1) % 3],
                                v);

                        ATriangle->triangleList[0] = BTriangle;

                        t->triangleList[0] = CTriangle;
                        std::cout << auxTri[0];

                        BTriangle->triangleList[0] = ATriangle;
                        BTriangle->triangleList[1] = auxTri[0]->triangleList[(i + 1) % 3];
                        BTriangle->triangleList[2] = CTriangle;

                        CTriangle->triangleList[0] = t;
                        CTriangle->triangleList[1] = BTriangle;
                        CTriangle->triangleList[2] = auxTri[0]->triangleList[(i + 2) % 3];

                        allTriangles.push_back(BTriangle);
                        allTriangles.push_back(CTriangle);
                        //borderCheck(BTriangle);
                        //borderCheck(CTriangle)
                    }

                    std::cout << "Point added as edge:";
                    v->print();
                    std::cout << "\n" << "To triangle:";
                    t->print();
                    std::cout << "\n";
                } else {
                    auxVer[0] = t->vertexList[0];
                    auxVer[1] = t->vertexList[1];
                    auxVer[2] = t->vertexList[2];

                    auxTri[0] = t->triangleList[0];
                    auxTri[1] = t->triangleList[1];
                    auxTri[2] = t->triangleList[2];

                    // Vertex definition
                    ATriangle = new Triangle<numType>(v, auxVer[0], auxVer[1]);
                    BTriangle = new Triangle<numType>(v, auxVer[1], auxVer[2]);
                    t->vertexList[0] = v;
                    t->vertexList[1] = auxVer[2];
                    t->vertexList[2] = auxVer[0];

                    // Neighbour definition
                    ATriangle->triangleList[0] = auxTri[2];
                    ATriangle->triangleList[1] = BTriangle;
                    ATriangle->triangleList[2] = t;
                    if (auxTri[2] != 0) {
                        auxTri[2]->triangleList[2] = BTriangle;
                    }

                    BTriangle->triangleList[0] = auxTri[0];
                    BTriangle->triangleList[1] = t;
                    BTriangle->triangleList[2] = ATriangle;
                    if (auxTri[0] != 0) {
                        auxTri[0]->triangleList[0] = BTriangle;
                    }

                    t->triangleList[0] = auxTri[1];
                    t->triangleList[1] = ATriangle;
                    t->triangleList[2] = BTriangle;
                    if (auxTri[1] != 0) {
                        auxTri[1]->triangleList[1] = BTriangle;
                    }

                    allTriangles.push_back(BTriangle);
                    //borderCheck(BTriangle);
                }

                t->calcBarycentric();
                allTriangles.push_back(ATriangle);
                //borderCheck(ATriangle);
                //borderCheck(t);

                break;
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

        Triangle<numType>* topTriangle = new Triangle<numType>(neVertex, nwVertex, swVertex);
        Triangle<numType>* botTriangle = new Triangle<numType>(swVertex, seVertex, neVertex);
        topTriangle->triangleList[1] = botTriangle;
        botTriangle->triangleList[1] = topTriangle;

        boundingTriangles.push_back(topTriangle);
        boundingTriangles.push_back(botTriangle);
        allTriangles.push_back(topTriangle);
        allTriangles.push_back(botTriangle);
    }

//    void borderCheck(Triangle<numType> *t) {
//        for (auto borderv : borderVertexVec) {
//            for (auto v : t->vertexList) {
//                if(*v == *borderv) { boundingTriangles.push_back(t); break;}
//                triangleVec.push_back(t);
//            }
//        }
//    }

    std::vector<Vertex<numType> *> getBorderVertexes() {
        return borderVertexVec;
    }

    std::vector<Triangle<numType> *> getBorderTriangles() {
        return boundingTriangles;
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
