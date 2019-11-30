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
 *-add utility function,insertion and solve for overflow(neither checked)
 */


#ifndef B_TREE_BTREENODE_H
#define B_TREE_BTREENODE_H

#include <iostream>
#include <vector>
#include <cmath>
#include <queue>


using namespace std;


class Bptree {
private:

    //total items of the tree
    int size;

    //degree of the tree
    static int order;

    struct node {
        node* parent;
        vector<int> key;
        bool isleaf;
        int value;
        vector<node*> children;

        node() {
            parent = nullptr;
            isleaf = true;
            value = -1; //value initialized to -1 to show that nothing is stored in the node
            // (Like with the visualization, only positive numbers can be added to the tree)
        }

        node(node* p, vector<int> k, const vector<node*> c) {
            parent = p;
            if (!k.empty()) {
                for (int i = 0; i < order - 1; i++) {
                    key.push_back(k[i]);
                }
            }
            isleaf = false;
            for (auto i : c) {
                children.push_back(i);
            }
            value = -1;
        }

        node(node* p, vector<int> k, bool l) {
            parent = p;
            if (!k.empty()) {
                for (int i = 0; i < order - 1; i++) {
                    key.push_back(k[i]);
                }
            }
            isleaf = true;
            value = -1;
        }

        ~node() = default;
    };

    node* root = nullptr;

    //element that last visited
    node* last_visited = nullptr;

public:
    Bptree(int s, int o){
        root = nullptr;
        size = s;
        order = o;
    }

    ~Bptree(){ //not implemented

    }

    node* search(int x) {
        node* v = root;
        int i;
        bool found = false;
        while (v) {
            for (i = -1; i < v->key.size() && x > v->key[i+1] ; ++i){
                if (x == v->key[i] && v->isleaf) {
                    found = true;
                    last_visited = v;
                    return v;
                }
            }
            last_visited = v;
            v = v->children[i+1];

        }

        return nullptr;

    }



    node* merge(node*, node*);

    static int findPos(vector<int> arr,int comp) {
        int i;
        for (i = -1; i < arr.size() && comp > arr[i + 1]; i++) {}
        return i+1;
    }

    bool isFull(node* n) {
        return n->key.size() == this->order;
    }

    static bool hasChildren(node* n) {
        return n->children.empty();
    }

    // haven't tested yet
    void solveOverFlow(node* ptr) {
        while (ptr->key.size() > order) {
            if (!isFull(ptr->parent) ){
                int pivot = ptr->key.size() / 2;
                int pos = findPos(ptr->parent->key, ptr->key[pivot]);
                for (int j = ptr->parent->key.size() -1; j != pos; j--) {
                    swap(ptr->parent->key[j], ptr->parent->key[j - 1]);
                }
                ptr->parent->key[pos] = ptr->key[pivot];




                vector<int> left, right;

                for (int i = 0; i < pos; i++) {
                    left[i] = ptr->parent->children[pos]->key[i];
                }
                for (int i = pos; i < ptr->parent->children.size(); i++) {
                    right[i] = ptr->parent->children[pos]->key[i];
                }
                ptr->parent->children[pos]->key = left;
                ptr->parent->children[pos + 1]->key = right;

            }
        }
    }


    //insert success or not, not tested as well
    bool insert(int item) {

        if (root == nullptr || !hasChildren(root)) {
            root = new node();
            root->key.push_back(item);
            this->size++;
        }
        else {
            node* y = search(item);
            if (y) {
                return false;
            }
            int i = findPos(last_visited->key, item);

            //make room for store item at position
            for (int j = last_visited->key.size() -1; j != i; j--) {
                swap(last_visited->key[j], last_visited->key[j - 1]);
                swap(last_visited->children[j+1], last_visited->children[j]);
            }
            //store the item
            last_visited->key[i] = item;
            vector<node*> empty;

            last_visited->children[i]->key.push_back(item);
            last_visited->children[i]->value = item;
            last_visited->children[i]->isleaf = true;

            last_visited = last_visited->children[i];
        }

        solveOverFlow(last_visited);
    }

    void remove(int);

    void levelOrder(ostream& os){
        queue<node*> traversalQueue;
        traversalQueue.push(root);
        while(!traversalQueue.empty()){
            node * current = traversalQueue.front();
            traversalQueue.pop();
            for(size_t i = 0; i < current->key.size(); i++){

                if(!current->isleaf){
                    traversalQueue.push(current->children[i]);

                }
            }
        }

    }





};











#endif //B_TREE_BTREENODE_H
