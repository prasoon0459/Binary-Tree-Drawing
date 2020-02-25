#include <bits/stdc++.h>
#include "tools.h"
#include <climits>

using namespace std;

/*  @brief prints a tree by recursion of nodes
 *  @param root root node of tree 
 */
void printTree(Node *root) 
{   if(root != nullptr){
        printTree(root->left);
        std::cout << "info = " << root->info << " x = " << root->x << " y = " << root->y << std::endl;
        printTree(root->right);
    }
}

/* @brief finds the specified node
 * @param root root node of tree 
 * @param i value of node being searched for
 * @return pointer to node
 */
Node* getNode(Node *root, char i) 
{
    if(root != nullptr) {
        if(root->info == i)
            return root;
        Node *c;
        c = getNode(root->left, i);
        if(c != nullptr && c->info == i)
            return c;
        c = getNode(root->right, i);
        if(c != nullptr && c->info == i)
            return c;
    }
    else return nullptr;
}
/* 
 * @brief takes input from the user to draw a tree
 */ 
Node* interactive_input() 
{
    cout << "Enter the info for root of the tree : ";
    char info;
    cin >> info;
    Node *root = new Node(info, nullptr);
    
    cout<<"Enter the other nodes in the following format-"<<endl;
    cout<<"[parent] 0 [node_info] if the node is the left child of parent"<<endl;
    cout<<"[parent] 0 [node_info] if the node is the left child of parent"<<endl;
    cout<<"eg: 8 0 6 for left node      or      8 1 9 for right node"<<endl;
    cout<<endl;
    cout<<"Press 'y/Y' if you want to enter a new node or press anything else to exit ";

    char resp, parentInfo;
    cin >> resp;
    int child;
    while(resp == 'y' || resp == 'Y') {
        cin >> parentInfo >> child >> info;
        Node *parent = getNode(root, parentInfo);
        if(parent == nullptr) {
                cout << "Not a valid parent, please try again!" << endl;
        }
        else {
            Node *newNode = new Node(info, parent);
            if(child == 0) {
                parent->left = newNode;
            }
            else if(child == 1) {
                parent->right = newNode;
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

/* @brief numbering nodes according to array index
 * @param tree input array
 * @param index current node 
 * @param parent parent of current node
 * @return pointer to root
 */
Node* array_to_tree(vector<char> tree, int index, Node* parent) 
{
    if(index >= tree.size() || tree[index] == '-'){
        return nullptr;
	}
	Node* root = new Node(tree[index], nullptr);
    root->left = array_to_tree(tree, index * 2 + 1, root);
	root->right = array_to_tree(tree, index * 2 + 2, root);
	return root;
}

/* @param mode mode of input
 * @return pointer to root 
 */
Node* inputTree(char mode)
{
	if(mode == 'i' || mode == 'I'){
		/* interactive mode */
		return interactive_input();
	}
	else if(mode == 'a' || mode == 'a'){
		/* array mode: represent binary tree as array. */
        int n;
		cin >> n;
		vector<char> tree;
		for(int i=0;i<n;i++){
			char c;
            cin >> c; 
            tree.push_back(c);
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

/* 
 * @brief Finds max y coordinate
 * @return max y coordinate
 * @param root root of tree
 */
int getHeight(Node *root) 
{
    if(root == nullptr) return 0;
    int max_l = getHeight(root->left)+1;
    int max_r = getHeight(root->right)+1;
    return (max_r > max_l) ? max_r : max_l;
}

/* @param root root of tree
 * @param height height of tree
 */
void invertTreeX(Node *root, int height) {
    if(root != nullptr) {
        root->y = (height - root->y -1);
        invertTreeX(root->left, height);
        invertTreeX(root->right, height);
    }
}

/* @param root root of tree
 * @param dist distance to be shifted by
 */
void translateY(Node *root, int dist) {
    if(root != nullptr) {
        root->y = (dist + root->y);
        translateY(root->left, dist);
        translateY(root->right, dist);
    }
}

/* @param root root of tree
 * @param arr array to determine left son or right son
 */
void getXExtreme(Node *root, int arr[2]) {
    if(root != nullptr) {
        if(arr[0] > root->x)   /* min */
            arr[0] = root->x;
        if(arr[1] < root->x)   /* max */
            arr[1] = root->x;
        getXExtreme(root->left, arr);
        getXExtreme(root->right, arr);
    }
}

/* @param root root of tree
 * @param center center of tree
 */
void centerTree(Node *root, int center) {
    if(root != nullptr) {
        root->x = (root->x - center);
        centerTree(root->left, center);
        centerTree(root->right, center);
    }
}

/* @param root root of tree
 * @param dist distance between nodes
 */
void translateX(Node *root, int dist) {
     if(root != nullptr) {
        root->x = (dist + root->x);
        translateX(root->left, dist);
        translateX(root->right, dist);
    }
}

/* @param root root of tree
 * @param mul multiplication factor for y axis
 */
void mulHeight(Node *root, int mul) {
    if(root != nullptr) {
        root->y = (root->y * mul);
        mulHeight(root->left, mul);
        mulHeight(root->right, mul);
    }
}

/* @param root root of tree
 * @param factor scaling factor for both axes
 * @param mid midpoint of tree
 */
void scaleDown(Node* root, int factor, int mid){
    if(root!=nullptr){
        root->x = (root->x-mid)/factor + mid;
        root->y = (root->y-mid)/factor + mid;
        scaleDown(root->left, factor, mid);
        scaleDown(root->right, factor, mid);
    }
}

/* @param root root of tree
 * @param radius radius of node
 * @param HEIGHT height of tree
 * @param WIDTH width of tree
 * @return scale factor to shrink the tree by 
 */
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
    translateX(root, WIDTH/2);
    scaleDown(root, factor + 1, WIDTH/2);
    return factor + 1;
}