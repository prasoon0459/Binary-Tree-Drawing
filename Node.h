/* @brief holds all necessary information about a node*/
class Node 
{
public:
    char info;
    Node* left;
    Node* right;
    int x;
    int y;
    int offset;
    bool thread;
    Node* parent;
    int status;

    Node(char info, Node *parent): info(info), left(nullptr), right(nullptr), x(-1), y(-1), offset(0), thread(false), parent(parent), status(0) {}

    ~Node() {
        if(left != nullptr)
            left->~Node();
        if(right != nullptr)
            right->~Node();
    }
};

struct Extreme{
    Node* addr; // address
    int off; // offset from root of subtree 
    int lev; // tree level
};

void TRPlotTree(Node *, int );