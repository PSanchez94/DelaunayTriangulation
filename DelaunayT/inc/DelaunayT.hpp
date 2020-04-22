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
    std::vector<Vertex<numType> > vertexVec;
    std::vector<Vertex<numType> > borderVertexVec;

    std::vector<Triangle<numType> > triangleVec;
    std::vector<Triangle<numType> > boundingTriangles;
    std::vector<Triangle<numType> > allTriangles;

    Vertex<numType> swVertex;
    Vertex<numType> seVertex;
    Vertex<numType> neVertex;
    Vertex<numType> nwVertex;

public:
    DelaunayT() {
        vertexVec = std::vector<Vertex<numType> >();
        borderVertexVec = std::vector<Vertex<numType> >();

        triangleVec = std::vector<Triangle<numType> >();
        boundingTriangles = std::vector<Triangle<numType> >();
        allTriangles = std::vector<Triangle<numType> >();

        swVertex = Vertex<numType>();
        seVertex = Vertex<numType>();
        neVertex = Vertex<numType>();
        nwVertex = Vertex<numType>();
    }
    explicit DelaunayT(std::vector<std::vector<numType> > input) {

        findBoundingTriangles(input);
        std::random_shuffle ( input.begin(), input.end() );

        for (auto it = input.begin(); it != input.end(); ++it) {

            Vertex<numType> v = Vertex<numType>((*it)[0], (*it)[1]);
            vertexVec.push_back(v);
            addPoint(v);
        }
    }

    void addPoint(Vertex<numType> v) {

//        for (auto it : allTriangles ) {
//            it.print();
//        }
        for (auto it = boundingTriangles.begin(); it != boundingTriangles.end(); ++it) {
            it->print();


            if (it->PointInside(v)) {
                Triangle<numType> ATriangle;
                Triangle<numType> BTriangle;
                Triangle<numType> CTriangle;

                if (it->PointOnEdge(v) != -1) {
                    int i = it->PointOnEdge(v);

                    ATriangle = Triangle<numType>(it->vertexList[i], it->vertexList[(i+1)%3], &v);
                    BTriangle = Triangle<numType>(it->vertexList[i], &v, it->vertexList[(i+2)%3]);
                    CTriangle = Triangle<numType>(it->vertexList[i], it->vertexList[(i+1)%3], &v);
                    Triangle<numType> DTriangle = Triangle<numType>(it->vertexList[i], &v, it->vertexList[(i+2)%3]);

                    ATriangle.triangleList[0] = &DTriangle;
                    ATriangle.triangleList[1] = &BTriangle;
                    ATriangle.triangleList[2] = it->triangleList[2];
                    it->triangleList[2] = &ATriangle;

                    BTriangle.triangleList[0] = &CTriangle;
                    BTriangle.triangleList[1] = it->triangleList[1];
                    BTriangle.triangleList[2] = &ATriangle;
                    it->triangleList[1] = &BTriangle;

                    CTriangle.triangleList[0] = &BTriangle;
                    CTriangle.triangleList[1] = &DTriangle;
                    CTriangle.triangleList[2] = it->triangleList[2];
                    it->triangleList[2] = &CTriangle;

                    DTriangle.triangleList[0] = &ATriangle;
                    DTriangle.triangleList[1] = it->triangleList[1];
                    DTriangle.triangleList[2] = &CTriangle;
                    it->triangleList[1] = &DTriangle;

                    //triangleVec.erase(it->triangleList[i]);
                    allTriangles.push_back(DTriangle);
                    for (auto it2 = borderVertexVec.begin(); it2 != borderVertexVec.end(); ++it2) {
                        borderCheck(DTriangle, *it2);
                    }

                } else {
                    ATriangle = Triangle<numType>(&v, it->vertexList[0], it->vertexList[1]);
                    BTriangle = Triangle<numType>(&v, it->vertexList[1], it->vertexList[2]);
                    CTriangle = Triangle<numType>(&v, it->vertexList[2], it->vertexList[0]);

                    ATriangle.triangleList[0] = it->triangleList[2];
                    ATriangle.triangleList[1] = &BTriangle;
                    ATriangle.triangleList[2] = &CTriangle;
                    it->triangleList[2] = &ATriangle;

                    BTriangle.triangleList[0] = it->triangleList[0];
                    BTriangle.triangleList[1] = &CTriangle;
                    BTriangle.triangleList[2] = &ATriangle;
                    it->triangleList[0] = &BTriangle;

                    CTriangle.triangleList[0] = it->triangleList[1];
                    CTriangle.triangleList[1] = &ATriangle;
                    CTriangle.triangleList[2] = &BTriangle;
                    it->triangleList[1] = &CTriangle;

                    triangleVec.erase(std::find(triangleVec.begin(), triangleVec.end(), *it));
                    allTriangles.push_back(ATriangle);
                    allTriangles.push_back(BTriangle);
                    allTriangles.push_back(CTriangle);
                }

                triangleVec.erase(it);
                allTriangles.push_back(ATriangle);
                allTriangles.push_back(BTriangle);
                allTriangles.push_back(CTriangle);
                for (auto it2 = borderVertexVec.begin(); it2 != borderVertexVec.end(); ++it2) {
                    borderCheck(ATriangle, *it2);
                    borderCheck(BTriangle, *it2);
                    borderCheck(CTriangle, *it2);
                }
            } else {
                v.print();
                std::cout << " Vertex not inside bounding box" << "\n";

            }
        }
    }

    void findBoundingTriangles(std::vector<std::vector<numType>> input) {
        swVertex = Vertex<numType>(0, 0);
        seVertex = Vertex<numType>(0, 0);
        neVertex = Vertex<numType>(0, 0);
        nwVertex = Vertex<numType>(0, 0);

        for (auto it = input.begin(); it != input.end(); ++it) {
            numType percentage = 0.01;

            if ((*it)[0] <= swVertex.X) {
                swVertex.X = (*it)[0] + ((*it)[0] *percentage);
                nwVertex.X = (*it)[0] + ((*it)[0] *percentage);
            }
            else if (((*it)[0]) >= seVertex.X) {
                seVertex.X = (*it)[0] + ((*it)[0] *percentage);
                neVertex.X = (*it)[0] + ((*it)[0] *percentage);
            }
            if (((*it)[1]) <= swVertex.Y) {
                swVertex.Y = (*it)[1] + ((*it)[1] *percentage);
                seVertex.Y = (*it)[1] + ((*it)[1] *percentage);
            }
            else if (((*it)[1]) >= nwVertex.Y) {
                nwVertex.Y = (*it)[1] + ((*it)[1] *percentage);
                neVertex.Y = (*it)[1] + ((*it)[1] *percentage);
            }
        }

        borderVertexVec.push_back(swVertex);
        borderVertexVec.push_back(seVertex);
        borderVertexVec.push_back(neVertex);
        borderVertexVec.push_back(nwVertex);

        Triangle<numType> topTriangle = Triangle<numType>(&neVertex, &nwVertex, &swVertex);
        Triangle<numType> botTriangle = Triangle<numType>(&swVertex, &seVertex, &neVertex);
        topTriangle.triangleList[1] = &botTriangle;
        botTriangle.triangleList[1] = &topTriangle;

        boundingTriangles.push_back(topTriangle);
        boundingTriangles.push_back(botTriangle);

        allTriangles.insert(allTriangles.end(), boundingTriangles.begin(), boundingTriangles.end());
    }

    void borderCheck(Triangle<numType> t, Vertex<numType> v) {
        if(t.containsVertex(v)) { boundingTriangles.push_back(t); }
        else { triangleVec.push_back(t); }
    }

    std::vector<Triangle<numType> > getTriangles() {
        return triangleVec;
    }

    std::vector<Triangle<numType> > getVertexes() {
        return vertexVec;
    }

};

#endif //DELAUNAYT_HPP
