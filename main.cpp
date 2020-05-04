#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <cstdlib>
#include <ctime>

#include "DelaunayT.hpp"

DelaunayT<float> aTriangulation;
DelaunayT<int> aIntTriangulation;
std::vector<std::vector<int> > intNumList;
std::vector<std::vector<float> > numList;
std::vector<std::vector<float> > numListRect;

std::vector<std::vector<float> > numListSimple = std::vector<std::vector<float> >(
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

void drawPoints( Vertex<float> *v) {

    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex2f(v->X, v->Y);
    glEnd();
}

void drawTriangles(Triangle<float>* t) {
    // Triangle
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f); // White

    for (Vertex<float>* v : t->vertexList) {
        glVertex2f(v->X, v->Y);
    }
    glEnd();

    // Points
    for (Vertex<float>* v : t->vertexList) {
        drawPoints(v);
    }
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
    glLoadIdentity();

    for (Triangle<float>* t : aTriangulation.getAllTriangles() ) {
        drawTriangles(t);
    }

    // Render now
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float west = aTriangulation.getBorderVertexes()[0]->X;
    float east = aTriangulation.getBorderVertexes()[2]->X;
    float south = aTriangulation.getBorderVertexes()[0]->Y;
    float north = aTriangulation.getBorderVertexes()[2]->Y;

    gluOrtho2D(1.05*west - 0.05,
            1.05*east,
            1.05*south - 0.05,
            1.05*north);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    //aIntTriangulation = DelaunayT<int>(intNumList);

    std::srand(std::time(nullptr));

    for (float i = -1; i<2; i++) {
        for (float j = -1; j<2; j++) {
            numListRect.push_back({i, j});
        }
    }

    for (int i = 0; i<100; i++) {
        float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        numList.push_back({x, y});
    }

    aTriangulation = DelaunayT<float>(numList);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowSize(800, 800);   // Set the window's initial width & height
    glutInitWindowPosition(100, 100); // Position the window's initial top-left corner
    glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title

    glutDisplayFunc(display); // Register display callback handler for window re-paint
    glutReshapeFunc(reshape);
    init();
    glutMainLoop();           // Enter the infinitely event-processing loop

    std::cout << "Need a light?" << std::endl;
    return 0;
}
