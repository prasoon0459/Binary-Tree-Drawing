#include <iostream>
#include "tools.h"
#include <climits>

using namespace std;

void printTree(Node *root) {
    if(root != nullptr){
        printTree(root->getLeftNode());
        std::cout << "info = " << root->getInfo() << " x = " << root-> getX() << " y = " << root->getY() << std::endl;
        printTree(root->getRightNode());
    }
}

Node* getNode(Node *root, int i) {
    if(root != nullptr) {
        if(root->getInfo() == i)
            return root;
        Node *c;
        c = getNode(root->getLeftNode(), i);
        if(c != nullptr && c->getInfo() == i)
            return c;
        c = getNode(root->getRightNode(), i);
        if(c != nullptr && c->getInfo() == i)
            return c;
    }
    else return nullptr;
}

Node *inputTree() {
    cout << "Enter the info for root of the tree : ";
    int info;
    cin >> info;
    Node *root = new Node(info, nullptr);
    
    cout<<"Enter the other nodes in the following format-"<<endl;
    cout<<"[parent] 0 [node_info] if the node is the left child of parent"<<endl;
    cout<<"[parent] 0 [node_info] if the node is the left child of parent"<<endl;
    cout<<"eg: 8 0 6 for left node      or      8 1 9 for right node"<<endl;
    cout<<endl;

    cout<<"Press 'y' if you want to enter a new node or press anything else to exit";

    char resp;
    cin >> resp;
    int parentInfo, child;
    while(resp == 'y') {

        cin >> parentInfo >> child >> info;
        Node *parent = getNode(root, parentInfo);
        if(parent == nullptr) {
                cout << "Not a valid parent, please try again!" << endl;
        }
        else {
            Node *newNode = new Node(info, parent);
            if(child == 0) {
                parent->setLeftNode(newNode);
            }
            else if(child == 1) {
                parent->setRightNode(newNode);
            }
            else {
                cout << "Not a valid child position, please try again!" << endl;
            }
        }

        cout<<"Press 'y' if you want to enter a new node or press anything else to exit";
        cin >> resp;
    }
    return root;
}
int getHieght(Node *root) {
    if(root == nullptr) return 0;
    int max_l = getHieght(root->getLeftNode())+1;
    int max_r = getHieght(root->getRightNode())+1;
    return (max_r > max_l) ? max_r : max_l;
}
void invertTreeX(Node *root, int height) {
    if(root != nullptr) {
        root->setY(height - root->getY()-1);
        invertTreeX(root->getLeftNode(), height);
        invertTreeX(root->getRightNode(), height);
    }
}
void translateY(Node *root, int dist) {
    if(root != nullptr) {
        root->setY(dist + root->getY());
        translateY(root->getLeftNode(), dist);
        translateY(root->getRightNode(), dist);
    }
}
void getXExtreme(Node *root, int arr[2]) {
    if(root != nullptr) {
        if(arr[0] > root->getX())   // min
            arr[0] = root->getX();
        if(arr[1] < root->getX())   // max
            arr[1] = root->getX();
        getXExtreme(root->getLeftNode(), arr);
        getXExtreme(root->getRightNode(), arr);
    }
}
void centerTree(Node *root, int center) {
    if(root != nullptr) {
        root->setX(root->getX() - center);
        centerTree(root->getLeftNode(), center);
        centerTree(root->getRightNode(), center);
    }
}
void translateX(Node *root, int dist) {
     if(root != nullptr) {
        root->setX(dist + root->getX());
        translateX(root->getLeftNode(), dist);
        translateX(root->getRightNode(), dist);
    }
}
void mulHeight(Node *root, int mul) {
    if(root != nullptr) {
        root->setY(root->getY() * mul);
        mulHeight(root->getLeftNode(), mul);
        mulHeight(root->getRightNode(), mul);
    }
}

void alignTree(Node *root, int radius, int HEIGHT, int WIDTH) {

    mulHeight(root, 10*radius);

    int height = getHieght(root);
    invertTreeX(root, height);

    translateY(root, HEIGHT - 100);

    int arr[2];
    arr[0] = INT_MAX;
    arr[1] = 0;
    getXExtreme(root, arr);

    centerTree(root, (arr[0]+arr[1])/2);
    translateX(root, WIDTH/2);
}