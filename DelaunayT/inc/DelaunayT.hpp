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
public:
    DelaunayT() { }

    void boundingTriangles(std::vector<std::vector<numType>> input) {
        swVertex = Vertex<numType>(std::numeric_limits<numType>::min(), std::numeric_limits<numType>::min());
        seVertex = Vertex<numType>(std::numeric_limits<numType>::max(), std::numeric_limits<numType>::min());
        neVertex = Vertex<numType>(std::numeric_limits<numType>::max(), std::numeric_limits<numType>::max());
        nwVertex = Vertex<numType>(std::numeric_limits<numType>::min(), std::numeric_limits<numType>::max());

        for (auto it = input.begin(); it != input.end(); ++it) {
            //
            if (*it[0] >= swVertex.x) {
                swVertex.X = *it[0] - (*it[0] *0.001);
                nwVertex.X = *it[0] - (*it[0] *0.001);
            }
            else if (*it[0] <= seVertex.X) {
                seVertex.X = *it[0] - (*it[0] *0.001);
                neVertex.X = *it[0] - (*it[0] *0.001);
            }
            else if (*it[1] >= swVertex.Y) {
                swVertex.X = *it[1] + (*it[1] *0.001);
                seVertex.X = *it[1] + (*it[1] *0.001);
            }
            else if (*it[1] <= nwVertex.Y) {
                nwVertex.X = *it[1] + (*it[1] *0.001);
                neVertex.X = *it[1] + (*it[1] *0.001);
            }
        }
    }

private:
    std::vector<Vertex<numType> > vertexVec;
    std::vector<Triangle<numType> > triangleVec;

    Vertex<numType> swVertex;
    Vertex<numType> seVertex;
    Vertex<numType> neVertex;
    Vertex<numType> nwVertex;
};

#endif //DELAUNAYT_HPP
