#include <bits/stdc++.h>
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

Node* interactive_input() {
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

Node* array_to_tree(vector<int> tree, int index, Node* parent){
    if(index >= tree.size() || tree[index] == -1){
		return nullptr;
	}
	Node* root = new Node(tree[index], nullptr);
	root->left = array_to_tree(tree, index * 2 + 1, root);
	root->right = array_to_tree(tree, index * 2 + 2, root);
	return root;
}

Node* inputTree(char mode){
	if(mode == 'i' || mode == 'I'){
		// interactive mode
		return interactive_input();
	}
	else if(mode == 'a' || mode == 'a'){
		// array mode: represent binary tree as array.
        int n;
		cin >> n;
		vector<int> tree;
		for(int i=0;i<n;i++){
			int a;
            cin >> a; 
            tree.push_back(a);
		}
		return array_to_tree(tree, 0, nullptr);
	}
    else{
        cout<<"[ERROR] "<< mode <<" is not recognized"<<endl;
        cout<<"Available modes of input: interactive (i) or array (a)"<<endl;
        cout<<"Exiting..."<<endl;
        exit(1);
    }
}
int getHeight(Node *root) {
    if(root == nullptr) return 0;
    int max_l = getHeight(root->getLeftNode())+1;
    int max_r = getHeight(root->getRightNode())+1;
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

void scaleDown(Node* root, int factor, int mid){
    if(root!=nullptr){
        root->setX((root->getX()-mid)/factor + mid);
        root->setY((root->getY()-mid)/factor + mid);
        scaleDown(root->getLeftNode(), factor, mid);
        scaleDown(root->getRightNode(), factor, mid);
    }
}

int alignTree(Node *root, int radius, int HEIGHT, int WIDTH) {	
    mulHeight(root, 10*radius);

    int height = getHeight(root);
    invertTreeX(root, height);

    translateY(root, HEIGHT - 100);

    int arr[2];
    arr[0] = INT_MAX;
    arr[1] = -INT_MAX;
    getXExtreme(root, arr);
    centerTree(root, (arr[0]+arr[1])/2);

    int factor = (2 * abs(arr[0]))/1000;
    cout << factor << endl;
    translateX(root, WIDTH/2);
    scaleDown(root, factor + 1, WIDTH/2);
    return factor + 1;
}