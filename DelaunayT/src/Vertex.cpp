//
// Created by KasiSanchez on 18/04/2020.
//

template <class numType>
struct Vertex {
    numType X;
    numType Y;

    Vertex(numType x, numType y) {
        this->X = x;
        this->Y = y;
    }

    numType CrossProd(Vertex v) {
        return (this->X * v->Y) - (this->Y * v->X);
    }

    bool operator==(Vertex v) {
        return (this->X == v->Y) && (this->Y == v->Y);
    }
} ;