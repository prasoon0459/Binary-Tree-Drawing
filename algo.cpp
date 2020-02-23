// #include "Node.h"
#include <cmath>
#include "tools.h"
#include <bits/stdc++.h>
int MINSEP = 7;

using namespace std;
/**
@brief The TR tree drawing algorithm
@param root root of tree
@param level current level of node
@param rMost rightmost 
@param lMost leftmost

*/
void TRSetup(Node *root, int level, struct Extreme& rMost, struct Extreme& lMost, int stepY) {
    Node *l, *r;
    struct Extreme ll, lr, rl, rr;

    int currSep, rootSep, lOffSum, rOffSum;
    if(root == nullptr) {
        rMost.lev = -1;
        lMost.lev = -1;
    }
    else {
        root->y = level;
        l = root->left;
        r = root->right;
        TRSetup(l, level+1, lr, ll, stepY);
        TRSetup(r, level+1, rr, rl, stepY);
        if(r == nullptr && l == nullptr) {
            rMost.addr = root;
            lMost.addr = root;
            rMost.lev = level;
            lMost.lev = level;
            rMost.off = 0;
            lMost.off = 0;
            root->offset = 0;
        }
        else {
            currSep = MINSEP;
            rootSep = MINSEP;
            lOffSum = 0;
            rOffSum = 0;

            while(l != nullptr && r != nullptr) {
                if(currSep < MINSEP) {
                    rootSep += (MINSEP - currSep);
                    currSep = MINSEP;
                }
                if(l->right != nullptr) {
                    lOffSum += l->offset;
                    currSep -= l->offset;
                    l = l->right;
                }
                else {
                    lOffSum -= l->offset;
                    currSep += l->offset;
                    l = l->left;
                }

                if(r->left != nullptr) {
                    rOffSum -= r->offset;
                    currSep -= r->offset;
                    r = r->left;
                }
                else {
                    rOffSum += r->offset;
                    currSep += r->offset;
                    r = r->right;
                }
            } /* while ends */
            root->offset = ((rootSep + 1)/2);
            lOffSum -= root->offset;
            rOffSum += root->offset;

            if(rl.lev > ll.lev || root->left == nullptr) {
                lMost.addr = rl.addr;
                lMost.lev = rl.lev;
                lMost.off = rl.off;
                lMost.off += root->offset;
            }
            else {
                lMost.addr = ll.addr;
                lMost.lev = ll.lev;
                lMost.off = ll.off;
                lMost.off -= root->offset;
            }
            if(lr.lev > rr.lev || root->right == nullptr) {
                rMost.addr = lr.addr;
                rMost.lev = lr.lev;
                rMost.off = lr.off;
                rMost.off -= root->offset;
            }
            else {
                rMost.addr = rr.addr;
                rMost.lev = rr.lev;
                rMost.off = rr.off;
                rMost.off += root->offset;
            }

            if (l != nullptr && l != root->left) {
                rr.addr->thread = true;
                rr.addr->offset = (abs((rr.off + root->offset) - lOffSum));
                if((lOffSum - root->offset) <= rr.off) {
                    rr.addr->left = l;
                }
                else {
                    rr.addr->right = l;
                }
            }
            else if(r != nullptr && r != root->right) {
                ll.addr->thread = true;
                ll.addr->offset = (abs((ll.off - root->offset) - rOffSum));
                if((rOffSum + root->offset) >= ll.off) {
                    ll.addr->right = r;
                }
                else {
                    ll.addr->left = r;
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
        root->x = xPos;
        if(root->thread) {
            root->thread = false;
            root->left = nullptr;
            root->right = nullptr;
        }
        TRPetrify(root->left, xPos - root->offset);
        TRPetrify(root->right, xPos + root->offset);
    }
}
/* @brief driver code to draw trees
@param root root of tree
@param minsep minimum separation */
void TRPlotTree(Node *root, int minsep) {
    MINSEP = minsep;
    struct Extreme rm, lm;
    cout<<"BEFORE"<<endl;
    printTree(root);
    TRSetup(root, 0, rm, lm, minsep);
    TRPetrify(root, 0);
}