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
 */



#ifndef B_TREE_BTREENODE_H
#define B_TREE_BTREENODE_H

#include <iostream>
#include <vector>



using namespace std;


class Bptree{
private:

    int size;
    static int order;

    struct node{
        node* parent;
        int* key;
        bool isleaf;
        vector<node*> children;

        node(){
            parent = nullptr;
            isleaf = true;
            key = new int[order-1];
        }

        node(node* p, int* k, bool l,vector<node*> c){
            parent = p;
            key = new int[order];
            if(k){
                for(int i=0; i<order-1; i++){
                    key[i] = k[i];
                }
            }
            isleaf = l;
            for(int i=0; i<order; i++){
                children.push_back(c[i]);
            }
        }

        ~node(){
            delete [] key;
        }



    };

    node* root = nullptr;

public:
    Bptree(int,int);

    ~Bptree();

    bool find(int);

    node* split(node*);

    node* merge(node*,node*);

    void insert(int);

    void remove(int);

    void levelOrder(ostream&);





};











#endif //B_TREE_BTREENODE_H
