//
// Created by KasiSanchez on 20/04/2020.
//
#ifndef DELAUNAYT_HPP
#define DELAUNAYT_HPP

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
        for (std::vector<std::vector<numType> > it = input.begin(); it != input.end(); ++it) {
            addPoint(*it);
        }
    }

    void addPoint(Triangle<numType> t,Vertex<numType> v) {
        for (auto it = allTriangles.begin(); it != allTriangles.end(); ++it) {
            if (*it->PointInside(v)) {

                Triangle<numType> ATriangle = Triangle<numType>(v, *it[0], *it[1]);
                Triangle<numType> BTriangle = Triangle<numType>(v, *it[1], *it[2]);
                Triangle<numType> CTriangle = Triangle<numType>(v, *it[2], *it[0]);

                ATriangle.triangleList[0] = *it.triangleList[2];
                ATriangle.triangleList[1] = &BTriangle;
                ATriangle.triangleList[2] = &CTriangle;

                BTriangle.triangleList[0] = &*it.triangleList[0];
                BTriangle.triangleList[1] = &CTriangle;
                BTriangle.triangleList[2] = &ATriangle;

                CTriangle.triangleList[0] = &*it.triangleList[1];
                CTriangle.triangleList[1] = &ATriangle;
                CTriangle.triangleList[2] = &BTriangle;

                triangleVec.erase(it);
                allTriangles.insert(ATriangle);
                allTriangles.insert(BTriangle);
                allTriangles.insert(CTriangle);

                for (auto it = borderVertexVec.begin(); it != borderVertexVec.end(); ++it) {
                    if(ATriangle.containsVertex(*it)) { boundingTriangles.insert(ATriangle); }
                    else { triangleVec.insert(ATriangle); }

                    if (BTriangle.containsVertex(*it)) { boundingTriangles.insert(BTriangle); }
                    else { triangleVec.insert(BTriangle);}

                    if (CTriangle.containsVertex(*it)) { boundingTriangles.insert(CTriangle); }
                    else { triangleVec.insert(CTriangle); }
                }
            } else if (*it->PointOnEdge(v)) {

            }
        }
    }

    void findBoundingTriangles(std::vector<std::vector<numType>> input) {
        swVertex = Vertex<numType>(std::numeric_limits<numType>::min(), std::numeric_limits<numType>::min());
        seVertex = Vertex<numType>(std::numeric_limits<numType>::max(), std::numeric_limits<numType>::min());
        neVertex = Vertex<numType>(std::numeric_limits<numType>::max(), std::numeric_limits<numType>::max());
        nwVertex = Vertex<numType>(std::numeric_limits<numType>::min(), std::numeric_limits<numType>::max());

        for (auto it = input.begin(); it != input.end(); ++it) {
            //
            if (*it[0] >= swVertex.x) {
                swVertex.X = *it[0] - (*it[0] *0.01);
                nwVertex.X = *it[0] - (*it[0] *0.01);
            }
            else if (*it[0] <= seVertex.X) {
                seVertex.X = *it[0] - (*it[0] *0.01);
                neVertex.X = *it[0] - (*it[0] *0.01);
            }
            else if (*it[1] >= swVertex.Y) {
                swVertex.X = *it[1] + (*it[1] *0.01);
                seVertex.X = *it[1] + (*it[1] *0.01);
            }
            else if (*it[1] <= nwVertex.Y) {
                nwVertex.X = *it[1] + (*it[1] *0.01);
                neVertex.X = *it[1] + (*it[1] *0.01);
            }
        }

        borderVertexVec.insert({swVertex, seVertex, nwVertex, neVertex});

        boundingTriangles.insert(Triangle<numType>(swVertex, seVertex, neVertex));
        boundingTriangles.insert(Triangle<numType>(neVertex, nwVertex, swVertex));
        allTriangles.insert(boundingTriangles.end(), boundingTriangles.begin(), boundingTriangles.end());
    }

    std::vector<Triangle<numType> > getTriangles() {
        return triangleVec;
    }

    std::vector<Triangle<numType> > getVertexes() {
        return vertexVec;
    }

};

#endif //DELAUNAYT_HPP
