//
// Created by KasiSanchez on 18/04/2020.
//

#ifndef VERTEX_HPP
#define VERTEX_HPP

template <class numType>
struct Vertex {
    numType X;
    numType Y;

    Vertex(numType x, numType y);

    numType CrossProd(Vertex v);
    bool operator==(Vertex v);
} ;

#endif //DELAUNAYTRIANGULATION_VERTEX_H
