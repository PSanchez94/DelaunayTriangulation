//
// Created by KasiSanchez on 04/05/2020.
//

#ifndef DELAUNAYTRIANGULATION_GEOMETRIES_HPP
#define DELAUNAYTRIANGULATION_GEOMETRIES_HPP

#include <cmath>
#include "Vertex.hpp"

template<class numType>
numType InCircle(Vertex<numType>* a,
        Vertex<numType>* b,
        Vertex<numType>* c,
        Vertex<numType>* d){

    if (d == 0) {
        return -1.0;
    } else {
        numType m[3][3];
        Vertex<numType>* vList[3] = {a, b, c};

        for (int i = 0; i < 3; i++) {
            m[0][i] = vList[i]->X - d->X;
            m[1][i] = vList[i]->Y - d->Y;
            m[2][i] = pow((vList[i]->X - d->X)) + pow((vList[i]->Y - d->Y));
        }
        return determinant(m);
    }
}

template<class numType>
numType determinant( numType m[3][3]) {
    numType det = 0;
    numType subm[2][2];

    for (int x = 0; x < 3; x++) {
        int subi = 0;
        for (int i = 1; i < 3; i++) {
            int subj = 0;
            for (int j = 0; j < 3; j++) {
                if (j == x)
                    continue;
                subm[subi][subj] = m[i][j];
                subj++;
            }
            subi++;
        }
        det = det + (pow(-1, x) * m[0][x] *
                (subm[0][0] * subm[1][1]) - (subm[1][0] * subm[0][1]));
    }
}

#endif //DELAUNAYTRIANGULATION_GEOMETRIES_HPP
