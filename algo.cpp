#include "Node.h"
#include <cmath>

int MINSEP = 7;

Node::Node(int info, Node *parent) : info(info), left(nullptr), right(nullptr), x(-1), y(-1), offset(0), thread(false), parent(parent), status(0) { }

void Node::setInfo(int info) { info = info; }
int Node::getInfo() { return info; }

void Node::setLeftNode(Node *l) { left = l; }
Node *Node::getLeftNode(){ return left; }

void Node::setRightNode(Node *r) { right = r; }
Node *Node::getRightNode()  { return right; }

void Node::setX(int x) { this->x = x; }
int Node::getX()  { return x; }

void Node::setY(int y) { this->y = y; }
int Node::getY()  { return y; }

bool Node::isThread()  { return thread; }
void Node::setThread(bool thread) { thread = thread; }

void Node::setParent(Node *parent) { this->parent = parent; }
Node *Node::getParent()  {return this->parent; }

int Node::getStatus()  { return this->status; }
void Node::setStatus(int status) {this->status = status; }

int Node::getOffset()  {return this->offset; }
void Node::setOffset(int offset) {this->offset = offset;}



Node::~Node() {
    if(left != nullptr)
        left->~Node();
    if(right != nullptr)
        right->~Node();
}


/**
@brief The TR tree drawing algorithm
@param root root of tree
@param level current level of node
@param rMost rightmost 
@param lMost leftmost

*/
void TRSetup(Node *root, int level, struct Extreme *rMost, struct Extreme *lMost, int stepY) {
    Node *l, *r;
    struct Extreme ll, lr, rl, rr;

    int currSep, rootSep, lOffSum, rOffSum;
    if(root == nullptr) {
        rMost->lev = -1;
        lMost->lev = -1;
    }
    else {
        root->setY(level);
        l = root->getLeftNode();
        r = root->getRightNode();
        TRSetup(l, level+1, &lr, &ll, stepY);
        TRSetup(r, level+1, &rr, &rl, stepY);
        if(r == nullptr && l == nullptr) {
            rMost->addr = root;
            lMost->addr = root;
            rMost->lev = level;
            lMost->lev = level;
            rMost->off = 0;
            lMost->off = 0;
            root->setOffset(0);
        }
        else {
            currSep = MINSEP;
            rootSep = MINSEP;
            lOffSum = 0;
            rOffSum = 0;

            while(l != nullptr && r != nullptr) {
                if(currSep < MINSEP) {
                    rootSep += MINSEP - currSep;
                    currSep = MINSEP;
                }
                if(l->getRightNode() != nullptr) {
                    lOffSum += l->getOffset();
                    currSep -= l->getOffset();
                    l = l->getRightNode();
                }
                else {
                    lOffSum -= l->getOffset();
                    currSep += l->getOffset();
                    l = l->getLeftNode();
                }

                if(r->getLeftNode() != nullptr) {
                    rOffSum -= r->getOffset();
                    currSep -= r->getOffset();
                    r = r->getLeftNode();
                }
                else {
                    rOffSum += r->getOffset();
                    currSep += r->getOffset();
                    r = r->getRightNode();
                }
            } /* @remark while ends */
            root->setOffset((rootSep + 1)/2);
            lOffSum -= root->getOffset();
            rOffSum += root->getOffset();

            if(rl.lev > ll.lev || root->getLeftNode() == nullptr) {
                lMost->addr = rl.addr;
                lMost->lev = rl.lev;
                lMost->off = rl.off;
                lMost->off += root->getOffset();
            }
            else {
                lMost->addr = ll.addr;
                lMost->lev = ll.lev;
                lMost->off = ll.off;
                lMost->off -= root->getOffset();
            }
            if(lr.lev > rr.lev || root->getRightNode() == nullptr) {
                rMost->addr = lr.addr;
                rMost->lev = lr.lev;
                rMost->off = lr.off;
                rMost->off -= root->getOffset();
            }
            else {
                rMost->addr = rr.addr;
                rMost->lev = rr.lev;
                rMost->off = rr.off;
                rMost->off += root->getOffset();
            }

            if (l != nullptr && l != root->getLeftNode()) {
                rr.addr->setThread(true);
                rr.addr->setOffset(abs((rr.off + root->getOffset()) - lOffSum));
                if((lOffSum - root->getOffset()) <= rr.off) {
                    rr.addr->setLeftNode(l);
                }
                else {
                    rr.addr->setRightNode(l);
                }
            }
            else if(r != nullptr && r != root->getRightNode()) {
                ll.addr->setThread(true);
                ll.addr->setOffset(abs((ll.off - root->getOffset()) - rOffSum));
                if((rOffSum + root->getOffset()) >= ll.off) {
                    ll.addr->setRightNode(r);
                }
                else {
                    ll.addr->setLeftNode(r);
                }
            }
        }
    }
}

/** @brief
Assigns to the nodes their the absolute x coordinates
@param xPos x position of current node
@param root root of tree
*/
void TRPetrify(Node *root, int xPos) {
    if(root != nullptr){
        root->setX(xPos);
        if(root->isThread()) {
            root->setThread(false);
            root->setLeftNode(nullptr);
            root->setRightNode(nullptr);
        }
        TRPetrify(root->getLeftNode(), xPos - root->getOffset());
        TRPetrify(root->getRightNode(), xPos + root->getOffset());
    }
}
/* @brief driver code to draw trees
@param root root of tree
@param minsep minimum separation */
void TRPlotTree(Node *root, int minsep) {
    MINSEP = minsep;
    struct Extreme rm, lm;
    TRSetup(root, 0, &rm, &lm, minsep);
    TRPetrify(root, 0);
}