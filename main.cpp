#include <iostream>
#include <GL/glut.h>
#include <math.h>

#include "DelaunayT.hpp"

DelaunayT<float> aTriangulation;

//std::vector<std::vector<float> > numList = std::vector<std::vector<float> >(
//        {{-10.0f, 10.0f}, {0.0f, 9.0f}, {10.0f, 10.0f},
//         {-5.0f, 5.0f}, {5.0f, 5.0f},
//         {-9.0f, 0.0f}, {0.0f, 0.0f}, {9.0f, 0.0f},
//         {-5.0f, -5.0f}, {5.0f, -5.0f},
//         {-10.0f, -10.0f}, {0.0f, -9.0f}, {10.0f, -10.0f}}
//);

    std::vector<std::vector<float> > numList = std::vector<std::vector<float> >(
            {{-1.0f, 1.0f}, {0.0f, 0.9f}, {1.0f, 1.0f},
             {-0.5f, 0.5f}, {0.5f, 0.5f},
             {-0.9f, 0.0f}, {0.0f, 0.0f}, {0.9f, 0.0f},
             {-0.5f, -0.5f}, {0.5f, -0.5f},
             {-1.0f, -1.0f}, {0.0f, -0.9f}, {1.0f, -1.0f}}
            );

void drawPoints( Vertex<float> *v, int r) {

    float a[2] = {v->X, v->Y};

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    for (int i=0; i < 360; i++) {
        double rad =  i * (M_PI / 180);
        glVertex2f(a[0] + cos(rad)*r/5, a[1] + sin(rad)*r/5);
        glVertex2f(a[0], a[1]);
    }
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
        drawPoints(v, v->X*0.01);
    }
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
    glLoadIdentity();

    for (Triangle<float>* t : aTriangulation.getTriangles() ) {
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

    gluOrtho2D(west + west*0.05, east + east*0.05, south + south*0.05, north + north*0.05);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {

    aTriangulation = DelaunayT<float>(numList);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowSize(1000, 1000);   // Set the window's initial width & height
    glutInitWindowPosition(500, 500); // Position the window's initial top-left corner
    glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title

    glutDisplayFunc(display); // Register display callback handler for window re-paint
    glutReshapeFunc(reshape);
    init();
    glutMainLoop();           // Enter the infinitely event-processing loop

    std::cout << "Need a light?" << std::endl;
    return 0;
}
