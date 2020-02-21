/* @brief holds all necessary information about a node*/
class Node 
{
    public:

    int info;
    Node* left;
    Node* right;
    int x;
    int y;
    int offset;
    bool thread;
    Node* parent;
    int status;

    Node (int , Node*);
    ~Node();

	int getInfo();void setInfo(int );
    int getX();void setX(int ) ;
    int getY();void setY(int );
    Node* getLeftNode();void setLeftNode(Node* );
    Node* getRightNode();void setRightNode(Node* ) ;
    int getOffset();void setOffset(int );
    Node* getParent();void setParent(Node* );
	int getStatus();void setStatus(int ) ;
	bool isThread();void setThread(bool ) ;
};

struct Extreme{
    Node* addr;
    int off;
    int lev;
};

void TRPlotTree(Node *, int );