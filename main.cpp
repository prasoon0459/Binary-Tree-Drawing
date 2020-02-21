#include<bits/stdc++.h>
#include <GL/glut.h>
#include <cmath>
#include"tools.h"
#include "drawings.h"

using namespace std;

Node* node;
int CIRCLE_RADIUS, FACTOR = 1;
/*@param root root of tree*/
void plott(Node *root) {
    if(root != nullptr){
    	CIRCLE_RADIUS = 20/FACTOR;
        plott(root->getLeftNode());
        drawNode(root->getX(),root->getY(), CIRCLE_RADIUS);
        if(root->getLeftNode()!= nullptr){
            connectNodes(root->getX(),root->getY(),root->getLeftNode()->getX(),
                            root->getLeftNode()->getY(), CIRCLE_RADIUS);
        }
        if(root->getRightNode()!= nullptr){
            connectNodes(root->getX(),root->getY(),root->getRightNode()->getX(),
                            root->getRightNode()->getY(), CIRCLE_RADIUS);
        }
        plott(root->getRightNode());
    }
}


void display(){
    plott(node);
    glFlush();
    glEnd();
}

int main(int argc, char** argv){
    if(argc < 2){
        cout << "[ERROR] Pass command line argument for mode"<<endl<<"Exiting..."<<endl;
        exit(1);
    }
    char mode = argv[1][0];
    node = inputTree(mode);
    auto start = chrono::steady_clock::now(); 
    TRPlotTree(node, 100);
    // cout<<"Relative coordinates: "<<endl;
    // printTree(node);
    FACTOR = alignTree(node,10,1000,1000);
    // cout<<"After alignment: "<<endl;
    // printTree(node);
    auto calculation_done = chrono::steady_clock::now();
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
    auto end = chrono::steady_clock::now(); 
    auto calculation_time = chrono::duration_cast<chrono::microseconds>(calculation_done - start).count();
    auto plot_time = chrono::duration_cast<chrono::microseconds>(end - calculation_done).count();
    cout << "Calculation: " << calculation_time << endl;
    cout << "Plotting: " << plot_time << endl;
    glutMainLoop();
    return 0;
}