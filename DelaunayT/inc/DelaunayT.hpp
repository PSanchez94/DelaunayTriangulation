//
// Created by KasiSanchez on 20/04/2020.
//
#ifndef DELAUNAYT_HPP
#define DELAUNAYT_HPP

#include <vector>
#include <algorithm>
#include "Triangle.hpp"
#include "Geometries.hpp"

template<class numType>
class DelaunayT {
private:
    std::vector<Vertex<numType> *> vVec;
    std::vector<Vertex<numType> *> borderVVec;

    std::vector<Triangle<numType> *> tVec;
    std::vector<Triangle<numType> *> boundingTVec;
    std::vector<Triangle<numType> *> allTVec;

    Vertex<numType>* swVertex;
    Vertex<numType>* seVertex;
    Vertex<numType>* neVertex;
    Vertex<numType>* nwVertex;

public:
    DelaunayT() {
        vVec = std::vector<Vertex<numType> *>();
        borderVVec = std::vector<Vertex<numType> *>();

        tVec = std::vector<Triangle<numType> *>();
        boundingTVec = std::vector<Triangle<numType> *>();
        allTVec = std::vector<Triangle<numType> *>();
    }
    explicit DelaunayT(std::vector<std::vector<numType> > input) {

        findBoundingTriangles(input);
        std::random_shuffle ( input.begin(), input.end() );

        for (auto it = input.begin(); it != input.end(); ++it) {
            Vertex<numType>* v = new Vertex<numType>((*it)[0], (*it)[1]);
            vVec.push_back(v);
            addPoint(v);
        }


        std::cout << "Done building. " << "\n" << "Triangles Created: ";
        std::cout << allTVec.size() << "\n";
        std::cout << "Draw Triangles: " << tVec.size() << "\n";
        std::cout << "Border Triangles: " << boundingTVec.size() << "\n";


    }

    void addPoint(Vertex<numType> *v) {
        for (Triangle<numType>* t : allTVec) {
            if (t->PointInside(v)) {
                if (t->PointOnEdge(v) != -1) {


                    //std::cout << "Before Update Point added as edge:";
                    //v->print();
                    //std::cout << "\n" << "Triangle:";
                    //t->print();
                    //std::cout << "\n";


                    updateByPointOnEdge(t, v, t->PointOnEdge(v));


                    //std::cout << "Point added as edge:";
                    //v->print();
                    //std::cout << "\n" << "To triangle:";
                    //t->print();
                    //std::cout << "\n";


                } else {

                    //std::cout << "Before Update Point inside:";
                    //v->print();
                    //std::cout << "\n" << "Triangle:";
                    //t->print();
                    //std::cout << "\n";

                    updateByPointInside(t, v);

                    //std::cout << "Point inside added:";
                    //v->print();
                    //std::cout << "\n" << "To triangle:";
                    //t->print();
                    //std::cout << "\n";
                }

                t->calcBarycentric();
                break;
            }
        }
    }

    void updateByPointInside(Triangle<numType>* t, Vertex<numType>* v) {

        // Vertex Definition
        Triangle<numType>* AT = new Triangle<numType>(v, t->vList[1], t->vList[2]);
        Triangle<numType>* BT = new Triangle<numType>(t->vList[0], v, t->vList[2]);
        t->vList[2] = v;

        // ATriangle neighbours
        if (t->tList[0] != 0) {
            AT->tList[0] = t->tList[0];
            AT->indexOppT[0] = t->indexOppT[0];
            AT->tList[0]->tList[AT->indexOppT[0]] = AT;
            AT->tList[0]->indexOppT[AT->indexOppT[0]] = 0;
        }

        AT->tList[1] = BT;
        AT->indexOppT[1] = 0;
        AT->tList[2] = t;
        AT->indexOppT[2] = 0;

        t->tList[0] = AT;
        t->indexOppT[0] = 2;

        // BTriangle neighbours
        BT->tList[0] = AT;
        BT->indexOppT[0] = 1;
        if (t->tList[1] != 0) {
            BT->tList[1] = t->tList[1];
            BT->indexOppT[1] = t->indexOppT[1];
            BT->tList[1]->tList[BT->indexOppT[1]] = BT;
        }
        BT->tList[2] = t;
        BT->indexOppT[2] = 1;

        t->tList[1] = BT;
        t->indexOppT[1] = 2;

        legalizeEdge(t, 2);
        legalizeEdge(AT, 0);
        legalizeEdge(BT, 1);
        allTVec.push_back(AT);
        allTVec.push_back(BT);
    }

    void updateByPointOnEdge(Triangle<numType>* t, Vertex<numType>* v, int i) {

        Triangle<numType>* AT = new Triangle<numType>(t->vList[i], v, t->vList[(i+2) %3]);
        t->vList[(i+2) %3] = v;

        if (t->tList[(i+1) %3] != 0) {
            AT->tList[1] = t->tList[(i+1) %3];
            AT->indexOppT[1] = t->indexOppT[(i+1) %3];
            AT->tList[1]->tList[AT->indexOppT[1]] = AT;
        }
        AT->tList[2] = t;
        AT->indexOppT[2] = (i+1) %3;

        t->tList[(i+1) %3] = AT;
        t->indexOppT[(i+1) %3] = 2;

        if (t->tList[i] != 0) {
            Triangle<numType>* u = t->tList[i];
            int j = t->indexOppT[i];

            Triangle<numType>* BT = new Triangle<numType>(u->vList[j], u->vList[(j+1) %3], v);
            u->vList[(j+1) %3] = v;

            BT->tList[0] = AT;
            BT->indexOppT[0] = 0;
            BT->tList[1] = u;
            BT->indexOppT[1] = (j+2) %3;
            if (u->tList[(j+2) %3] != 0) {
                BT->tList[2] = u->tList[(j+2) %3];
                BT->indexOppT[2] = u->indexOppT[(j+2) %3];
                BT->tList[2]->tList[BT->indexOppT[2]] = BT;
            }
            u->tList[(j+2) %3] = BT;
            u->indexOppT[(j+2) %3] = 1;

            AT->tList[0] = BT;
            AT->indexOppT[0] = 0;

            legalizeEdge(u, (j+1) %3);
            legalizeEdge(BT, 2);
            allTVec.push_back(BT);

            u->calcBarycentric();
        }

        legalizeEdge(t, (i+2) %3);
        legalizeEdge(AT, 1);
        allTVec.push_back(AT);
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

        borderVVec.push_back(swVertex);
        borderVVec.push_back(seVertex);
        borderVVec.push_back(neVertex);
        borderVVec.push_back(nwVertex);

        Triangle<numType>* topTriangle = new Triangle<numType>(neVertex, nwVertex, swVertex);
        Triangle<numType>* botTriangle = new Triangle<numType>(swVertex, seVertex, neVertex);
        topTriangle->tList[1] = botTriangle;
        topTriangle->indexOppT[1] = 1;
        botTriangle->tList[1] = topTriangle;
        botTriangle->indexOppT[1] = 1;

        boundingTVec.push_back(topTriangle);
        boundingTVec.push_back(botTriangle);
        allTVec.push_back(topTriangle);
        allTVec.push_back(botTriangle);
    }

//    void borderCheck(Triangle<numType> *t) {
//        for (auto borderv : borderVVec) {
//            for (auto v : t->vList) {
//                if(*v == *borderv) { boundingTVec.push_back(t); break;}
//                tVec.push_back(t);
//            }
//        }
//

    void legalizeEdge(Triangle<numType>* t, int i) {
        if (t->tList[i] != 0) {
            if (InCircle(t, t->tList[i]->vList[t->indexOppT[i]]) > 0) {
                std::cout << "Edge flipped inside:";
                std::cout << "\n" << i << "To triangle:";
                t->print();
                std::cout << "\n";
                flipEdge(t, i);
                std::cout << "After Edge flipped inside:";
                std::cout << "\n" << i << "To triangle:";
                t->print();
                std::cout << "\n";
            }
        }
    }

    void flipEdge(Triangle<numType>* t, int i) {
        Triangle<numType>* u = t->tList[i];
        int j = t->indexOppT[i];

        // Vertex Definition
        t->vList[(i+2) %3] = u->vList[j];
        u->vList[(j+2) %3] = t->vList[i];

        // Neighbour Update
        if (t->tList[(i+1) %3] != 0) {
            u->tList[j] = t->tList[(i+1) %3];
            u->indexOppT[j] = t->indexOppT[(i+1) %3];
            u->tList[j]->tList[u->indexOppT[j]] = u;
            u->tList[j]->indexOppT[u->indexOppT[j]] = j;
        } else {
            u->tList[j] = 0;
            u->indexOppT[j] = -1;
        }

        if (u->tList[(j+1) %3] != 0) {
            t->tList[i] = u->tList[(j+1) %3];
            t->indexOppT[i] = u->indexOppT[(j+1) %3];
            t->tList[i]->tList[t->indexOppT[i]] = t;
            t->tList[i]->indexOppT[t->indexOppT[i]] = i;
        } else {
            t->tList[i] = 0;
            t->indexOppT[i] = -1;
        }

        t->tList[(i+1) %3] = u;
        t->indexOppT[(i+1) %3] = (j+1) %3;
        u->tList[(j+1) %3] = t;
        u->indexOppT[(j+1) %3] = (i+1) %3;
    }

    std::vector<Vertex<numType> *> getBorderVertexes() {
        return borderVVec;
    }

    std::vector<Triangle<numType> *> getBorderTriangles() {
        return boundingTVec;
    }

    std::vector<Triangle<numType> *> getTriangles() {
        return tVec;
    }

    std::vector<Triangle<numType> *> getVertexes() {
        return vVec;
    }

    std::vector<Triangle<numType> *> getAllTriangles() {
        return allTVec;
    }

};

#endif //DELAUNAYT_HPP
