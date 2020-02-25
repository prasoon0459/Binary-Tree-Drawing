#include<bits/stdc++.h>
#include <GL/glut.h>
#include <cmath>
#include"tools.h"
#include "drawings.h"

/*! \mainpage
 *
 *  Binary Tree Drawings. Most of the data required for the program to run is located in the
 * 	as objects of the Node class, which can be accesed by clicking the link below. For installation
 * 	instructions, read the Markdown file present in the root of the project. The markdown file also
 *  gives you a brief on the runtimes, the tools used, and the problems faced during coding. 
 *  
 *  \dot
 *  digraph example {
 *      node [shape=record, fontname=Helvetica, fontsize=10];
 *      b [ label="Node Class" URL="\ref Node"];
 *  }
 *  \enddot
 */


using namespace std;

Node* node;
int CIRCLE_RADIUS, FACTOR = 1;
/* @param root root of tree */
void plott(Node *root) {
    if(root != nullptr){
    	CIRCLE_RADIUS = 20/FACTOR;
        plott(root->left);
        drawNode(root->x,root->y, CIRCLE_RADIUS, root->info, FACTOR==1?true:false);
        if(root->left!= nullptr){
            connectNodes(root->x,root->y,root->left->x,
                            root->left->y, CIRCLE_RADIUS);
        }
        if(root->right!= nullptr){
            connectNodes(root->x,root->y,root->right->x,
                            root->right->y, CIRCLE_RADIUS);
        }
        plott(root->right);
    }
}


/* @brief display the tree by plotting the nodes calculating */
void display(){
    plott(node);
    glFlush();
    glEnd();
}

/* 
 * @brief main function to take inputs and draw the tree
 * @param argc number of command
 * @param argv argument list
 */
int main(int argc, char** argv){
    if(argc < 2){
        cout << "[ERROR] Pass command line argument for mode"<<endl<<"Exiting..."<<endl;
        exit(1);
    }
    char mode = argv[1][0];
    node = inputTree(mode);
    auto start = chrono::steady_clock::now(); 
    TRPlotTree(node, 100);
    FACTOR = alignTree(node,10,1000,1000);
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