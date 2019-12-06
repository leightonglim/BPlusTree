/*
 * Group project B+ Tree
 *
 *
 *
 *
 *
 *
 * Last Modified: 11/25/2019
 *
 *
 *11/27/2019
 * -add utility function,insertion and solve for overflow(neither checked)
 *
 * 12/2/2019
 * -modified insert,solve for overflow,level order traversal and search
 * -initial value to -1 is unnecessary, a node with no parents(disconnected node) is not yet have value stored
 */


#ifndef B_TREE_BTREENODE_H
#define B_TREE_BTREENODE_H

#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>
#include <list>
#include "SDL_Plotter.h"
#include "rectangle.h"
#include "line.h"


using namespace std;

class Bptree {
private:

    //degree of the tree
    int order;
    unsigned int delay;
    SDL_Plotter g;

    struct node {
        point upperLeft,downRight;
        rectangle it;
        node* parent;
        vector<int> key;
        vector<rectangle> keyBlock[7];
        bool isleaf;
        int value;
        vector<node*> children;
        node *leftSib = nullptr,*rightSib = nullptr;

        node() {

            rectangle it;
            parent = nullptr;
            isleaf = true;
            vector<int> key[7];
            vector<node*> children[9];
//            node* leftSib = nullptr;
//            node* rightSib = nullptr;

            value = -1; //value initialized to -1 to show that nothing is stored in the node
            // (Like with the visualization, only positive numbers can be added to the tree)
        }

        ~node(){};
    };

    node* root = nullptr;

    //element that last visited
    node* last_visited = nullptr;

    list<node*> leaves;

public:


    Bptree(int o,SDL_Plotter& p){
        root = nullptr;
        order = o;
        g = p;
        delay = 5;
    }

    ~Bptree(){ //not implemented

    }

    node* search(int x) {
        node* v = root;
        int i;
        while (v) {
            for (i = 0; i < v->key.size() && x >= v->key[i] ; i++){
            }
            if (x == v->key[i] && v->isleaf) {
                last_visited = v;
                return v;
            }else if(x == v->key[i] && !v->parent){
                last_visited = v;
                return v;
            }


            last_visited = v;
            if(hasChildren(v)){
                v = v->children[i];
            }else{
                return nullptr;
            }

            i = 0;


        }

        return nullptr;

    }



    node* merge(node*, node*);

    size_t findPos(vector<int> arr,int comp) {
        size_t i;
        for (i = 0; i < arr.size() && comp > arr[i]; i++) {}
        return i;
    }

    bool isFull(node* n) {
        return n->key.size() == this->order;
    }

    bool hasChildren(node* n) {
        return n->children.size()!= 0;
    }

//    rectangle LeftSibiling(node* n){
//        if(n != root && n != n->parent->children[0]){
//            return;
//        }
//    }


    void shiftRight(node* n,size_t pos){
//        T a;
//        v.push_back(a);
        for(size_t i = n->key.size(); i > pos; i--){
            n->key.insert(n->key.begin()+i,n->key[i-1]);
        }
        //adjustGraphR(n);
    }

    void shiftRight(vector<node*> v,size_t pos){
//        T a;
//        v.push_back(a);
        for(size_t i = v.size(); i > pos; i--){
//            node* temp = v[i];
//            point x1(temp->upperLeft.x+=40,temp->upperLeft.y);
//            point x2(temp->downRight.x+=40,temp->downRight.y);
            v.insert(v.begin()+i,v[i-1]);

//            moveToPosition(temp->it,x1,x2);


        }
    }

    void solveOverFlow(node* ptr) {
        while (ptr && ptr->key.size() >= order) {
            size_t pivot = ceil(static_cast<double>(ptr->key.size()) / 2.0);

            if(!ptr->isleaf){
                //create a right children
                node* rc = new node();
//                rc->leftSib = ptr;
//                if(ptr->rightSib){
//                    rc->rightSib = ptr->rightSib;
//                    rc->rightSib->leftSib = rc;
//                }
//
//                ptr->rightSib = rc;



                if(root == ptr && !hasChildren(root)){
                    for (int i = pivot; i < ptr->key.size(); i++) {
                        rc->key.push_back(ptr->key[i]);
                    }

                    ptr->key.erase(ptr->key.begin() + pivot, ptr->key.end());

                    node* temp = new node();
                    temp->isleaf = false;
                    rc->parent = temp;

                    //new root has the key that suppose to be pushed up
                    temp->key.push_back(rc->key[0]);


                    //store the children in new root
                    temp->children.push_back(ptr);
                    temp->children.push_back(rc);

                    point x1;
                    point x2 = ptr->it.getP2();
                    x1.x = 750-((order*order)*25);
                    x1.y = root->it.getP2().y + 30;
                    x2.x = x1.x + 50;
                    x2.y = x2.y + 30;

                    rectangle r1(x1,x2);
                    ptr->keyBlock->push_back(r1);
                    ptr->it = r1;
                    r1.draw(g);

                    x2.x = 750+((order*order)*25);
                    x1.x = x2.x - 30;
                    rectangle r2(x1,x2);
                    rc->it = r2;
                    rc->keyBlock->push_back(r2);
                    r2.draw(g);





                    this->root = temp;
                    ptr->parent = root;
                    ptr->isleaf = true;


                }else{
                    int pushed = ptr->key[pivot];
                    for (int i = pivot + 1; i < ptr->key.size(); i++) {
                        rc->key.push_back(ptr->key[i]);
                    }

                    ptr->key.erase(ptr->key.begin() + pivot, ptr->key.end());

                    if (hasChildren(ptr)) {
                        for (size_t i = pivot + 1,j = 0; i < ptr->children.size(); i++,j++) {
                            rc->children.push_back(ptr->children[i]);
                            rc->children[j]->parent = rc;
                        }


                        ptr->children.erase(ptr->children.begin() + pivot+1, ptr->children.end());
                    }

                    rc->isleaf = false;
                    ptr->isleaf = false;

                    if (root == ptr) {

                        node* temp = new node();
                        temp->isleaf = false;
                        rc->parent = temp;

                        temp->key.push_back(pushed);
                        //store the children in new root
                        temp->children.push_back(ptr);
                        temp->children.push_back(rc);
                        this->root = temp;
                        ptr->parent = root;

                    }

                    else {
                        size_t pos = findPos(ptr->parent->key, ptr->key[pivot]);
                        shiftRight(ptr->parent, pos);

                        ptr->parent->key.insert(ptr->parent->key.begin()+pos,pushed);
                        shiftRight(ptr->parent->children, pos + 1);

                        //ptr->parent->children.insert(ptr->parent->children.begin()+pos,ptr);
                        ptr->parent->children.insert(ptr->parent->children.begin()+pos+1,rc);
                        rc->parent = ptr->parent;
                    }



                }



            }else{

                size_t pos = findPos(ptr->parent->key, ptr->key[pivot]);

                shiftRight(ptr->parent,pos);
                ptr->parent->key.insert(ptr->parent->key.begin()+pos,ptr->key[pivot]);

                if(pos == 0){

                    node* left = new node();
                    left->rightSib = ptr;
                    ptr->leftSib = left;

                    for(size_t i = 0; i < pivot; i++){
                        left->key.push_back(ptr->key[i]);
                    }
                    left->parent = ptr->parent;
                    size_t i = pivot,j = 0,size = ptr->key.size();
                    for(i,j; i < size; i++,j++){
                        swap(ptr->key[j], ptr->key[i]);
                    }
                    ptr->key.erase(ptr->key.begin()+j,ptr->key.end());


                    shiftRight(ptr->parent->children,0);
                    ptr->parent->children.insert(ptr->parent->children.begin(), left);
                    left->parent = ptr->parent;

                }else{
                    node* right = new node();
                    right->leftSib = ptr;
                    right->rightSib = ptr->rightSib;
                    right->rightSib->leftSib = right;
                    ptr->rightSib = right;

                    for(size_t i = pivot; i < ptr->key.size(); i++){
                        right->key.push_back(ptr->key[i]);

                    }
                    ptr->key.erase(ptr->key.begin()+pivot,ptr->key.end());


                    shiftRight(ptr->parent->children,pos+1);
                    ptr->parent->children.insert(ptr->parent->children.begin()+pos+1,right);
                    right->parent = ptr->parent;



                }

            }

            ptr = ptr->parent;


        }
    }


    //insert success or not
    bool insert(int item) {

//        rectangle temp;
//        temp.draw(g);
//        g.update();

        node* y = search(item);
        if (y) {
            return false;
        }
        if (root == nullptr) {
            root = new node();
            root->isleaf = false;
//            root->leftSib = nullptr;
//            root->rightSib = nullptr;

            root->key.push_back(item);
            last_visited = root;
            point x1(675,400);
            point x2(725,430);
            rectangle rt1(x1,x2);
            root->it = rt1;
            root->it.draw(g);
            root->keyBlock->push_back(root->it);


        }else if(!hasChildren(root)){
            size_t pos = findPos(root->key,item);
//            rectangle r1 = drawKeyPos(root,item);
            shiftRight(root,pos);
            root->key.insert(root->key.begin()+pos,item);
            root->it.erase(g);
            point x1 = root->it.getP1();
            x1.x += 50;
            point x2 = root->it.getP2();
            x2.x +=50;

            rectangle rec(x1,x2);
            root->it.setP2(x2);

            root->keyBlock->insert(root->keyBlock->begin()+pos,rec);
            rec.draw(g);

//            moveToPosition(temp,x1,x2);
//            root->it.draw(g);
//            g.update();
        }
        else {


            int i = findPos(last_visited->key, item);
            //make room for store item at position
            shiftRight(last_visited,i);

            //store the item
            last_visited->key.insert(last_visited->key.begin()+i,item);

        }

         solveOverFlow(last_visited);
    }

    void remove(int);


    void levelOrderInSDL(ostream& os){
        queue<node *> queue1;
        queue1.push(root);

        while(!queue1.empty()){
            node* temp = queue1.front();
            queue1.pop();

            if (temp == nullptr) {
                os << "NULL ";
            }else {
                temp->it.draw(g);
                g.update();
                for(int i = 0; i < temp->children.size(); i++){
                    queue1.push(temp->children[i]);
                }
            }
        }
        os << endl;
    }


    void levelOrder(ostream& os){
        queue<node *> queue1, queue2;
        if(!root){
            os << "NULL" << endl;
            return;
        }
        queue1.push(root);
        while(!queue1.empty() || !queue2.empty()){
            while(!queue1.empty()){
                if(hasChildren(queue1.front())){
                    for (auto i : queue1.front()->children) {
                        queue2.push(i);
                    }
                }
                for(int i = 0; i<queue1.front()->key.size(); i++){
                    if(!queue1.front()->isleaf && queue1.front()!=root){
                        os << "K: ";
                    }
                    os << queue1.front()->key[i] << " ";
                }
                queue1.pop();
                os << "   ";
            }
            os << endl;
            while(!queue2.empty()){
                if(hasChildren(queue2.front())){
                    for (auto i : queue2.front()->children) {
                        queue1.push(i);
                    }
                }
                for(int i = 0; i<queue2.front()->key.size(); i++){
                    if(!queue2.front()->isleaf && queue2.front()!=root){
                        os << "K: ";
                    }
                    os << queue2.front()->key[i] << " ";
                }
                queue2.pop();
                os << "   ";
            }
            os << endl;
        }
        os << endl;



    }

    void setSpeed(unsigned int dl){
        delay = dl;
    }

    void findSib(node* n){
        if(n == root){
            return;
        }else if(n->isleaf){

        }
    }

    int findCpos(node* n){
        int i = 0;
        for(i ; n != n->parent->children[i] && i < n->parent->children.size(); i++){}
        return i;
    }




    rectangle drawKeyPos(node*,int );

    rectangle findPosition(node*);

    void conncetNode(node*,node*);

    void draw(){
        root->it.draw(g);
    }

    void moveToPosition(rectangle& ,point&, point&);

    void adjustGraphL(node*);




};

#endif //B_TREE_BTREENODE_H