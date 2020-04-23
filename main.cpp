#include <iostream>
#include <GL/glut.h>
#include <math.h>

#include "DelaunayT.hpp"

int main() {

    std::vector<std::vector<float> > numList = std::vector<std::vector<float> >(
            {{-10.0f, 10.0f}, {0.0f, 9.0f}, {10.0f, 10.0f},
             {-5.0f, 5.0f}, {5.0f, 5.0f},
             {-9.0f, 0.0f}, {0.0f, 0.0f}, {9.0f, 0.0f},
             {-5.0f, -5.0f}, {5.0f, -5.0f},
             {-10.0f, -10.0f}, {0.0f, -9.0f}, {10.0f, -10.0f}}
            );

//    std::vector<std::vector<float> > numList = std::vector<std::vector<float> >(
//            {{-1.0f, 1.0f}, {0.0f, 0.9f}, {1.0f, 1.0f},
//             {-0.5f, 0.5f}, {0.5f, 0.5f},
//             {-0.9f, 0.0f}, {0.0f, 0.0f}, {0.9f, 0.0f},
//             {-0.5f, -0.5f}, {0.5f, -0.5f},
//             {-1.0f, -1.0f}, {0.0f, -0.9f}, {1.0f, -1.0f}}
//            );

    DelaunayT<float> aTriangulation;
    aTriangulation = DelaunayT<float>(numList);

    std::cout << "Need a light?" << std::endl;
    return 0;
}
