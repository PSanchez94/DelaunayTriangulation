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

    DelaunayT<float> aTriangulation = DelaunayT<float>(numList);

    std::cout << "Need a light?" << std::endl;
    return 0;
}
