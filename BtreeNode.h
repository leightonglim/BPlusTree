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
			vector<int> key(order+1);
		}

		node(node* p, vector<int> k,vector<node*> c) {
			parent = p;
			vector<int> key(order+1);
			if (k.size() !=0) {
				for (int i = 0; i < order - 1; i++) {
					key.push_back(k[i]);
				}
			}
			isleaf = false;
			for (int i = 0; i < c.size(); i++) {
				children.push_back(c[i]);
			}
		}

		node(node* p, vector<int> k, bool l) {
			parent = p;
			vector<int> key(order+1);
			if (k.size() != 0) {
				for (int i = 0; i < order - 1; i++) {
					key.push_back(k[i]);
				}
			}
			isleaf = l;
		}

		~node() {}
	};

	node* root = nullptr;

	//element that last visited
	node* last_visited = nullptr;

public:
	Bptree(int, int);

	~Bptree();

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

	int findPos(vector<int> arr,int comp) {
		int i;
		for (i = -1; i < arr.size() && comp > arr[i + 1]; i++) {}
		return i+1;
	}

	bool isFull(node* n) {
		return n->key.size() == this->order;
	}

	bool hasChildren(node* n) {
		return n->children.size();
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

	void levelOrder(ostream&);





};











#endif //B_TREE_BTREENODE_H
