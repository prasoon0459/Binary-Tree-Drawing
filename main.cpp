#include<bits/stdc++.h>
#include <GL/glut.h>
#include <cmath>
#include"tools.h"
#include "drawings.h"

using namespace std;

Node* node;

void plott(Node *root) {
    if(root != nullptr){
        plott(root->getLeftNode());
        drawNode(root->getX(),root->getY(), 20);
        if(root->getLeftNode()!= nullptr){
            connectNodes(root->getX(),root->getY(),root->getLeftNode()->getX(),
                            root->getLeftNode()->getY(), 20);
        }
        if(root->getRightNode()!= nullptr){
            connectNodes(root->getX(),root->getY(),root->getRightNode()->getX(),
                            root->getRightNode()->getY(), 20);
        }
        plott(root->getRightNode());
    }
    glEnd();
    glFlush();
}


void display(){
    plott(node);
}

int main(int argc, char** argv){
    
    node =inputTree();
    TRPlotTree(node, 100);
    printTree(node);
    alignTree(node,10,1000,1000);
    printTree(node);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize(1000,1000);
    glutInitWindowPosition(300, 100);
    glutCreateWindow("Binary Tree");
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1000, 0, 1000, -1.0, 1.0);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
    
}