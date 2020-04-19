#ifndef VERTEX_HPP
#define VERTEX_HPP

template <class numType>
struct Vertex {
    numType X;
    numType Y;

    Vertex() : X(0), Y(0) { };
    Vertex(numType x, numType y) : X(x), Y(y) { };

    bool operator==(Vertex v) { return (X == v.X) && (Y == v.Y); }
} ;

#endif //VERTEX_H
