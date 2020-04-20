//
// Created by KasiSanchez on 20/04/2020.
//
#ifndef DELAUNAYT_HPP
#define DELAUNAYT_HPP

#include <vector>
#include <limits>
#include "Triangle.hpp"

template<class numType>
class DelaunayT {
private:
    std::vector<Vertex<numType> > vertexVec;
    std::vector<Triangle<numType> > triangleVec;
    std::vector<Triangle<numType> > boundingTriangles;

    Vertex<numType> swVertex;
    Vertex<numType> seVertex;
    Vertex<numType> neVertex;
    Vertex<numType> nwVertex;

public:
    DelaunayT() {
        vertexVec = std::vector<Vertex<numType> >();
        triangleVec = std::vector<Vertex<numType> >();
        boundingTriangles = std::vector<Vertex<numType> >();
    }

    explicit DelaunayT(std::vector<std::vector<numType> > input) {
        findBoundingTriangles(input);

        for (std::vector<std::vector<numType> > it = input.begin(); it != input.end(); ++it) {
            addPoint(*it);
        }
    }

    void addPoint(Triangle<numType> t,Vertex<numType> v) {
        for (auto it = triangleVec.begin(); it != triangleVec.end(); ++it) {
            if (*it->PointInside(v)) {
                updateByPointInside(it, v);
                break;
            }
        }
        for (auto it = boundingTriangles.begin(); it != boundingTriangles.end(); ++it) {
            if (*it->PointInside(v)) {
                updateByPointInside(it, v);
                break;
            }
        }
    }


    void updateByPointInside(typename std::vector<Triangle<numType> >::iterator it, Vertex<numType> v) {
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
        triangleVec.insert(ATriangle);
        triangleVec.insert(BTriangle);
        triangleVec.insert(CTriangle);
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

        boundingTriangles.insert(Triangle<numType>(swVertex, seVertex, neVertex));
        boundingTriangles.insert(Triangle<numType>(neVertex, nwVertex, swVertex));
    }

    std::vector<Triangle<numType> > getBTriangles() {
        return boundingTriangles;
    }

    std::vector<Triangle<numType> > getTriangles() {
        return triangleVec;
    }

    std::vector<Triangle<numType> > getVertexes() {
        return triangleVec;
    }

};

#endif //DELAUNAYT_HPP
