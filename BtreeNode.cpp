#include "BtreeNode.h"

using namespace std;


rectangle Bptree::drawKeyPos(node* n,int key){

    int i = findPos(n->key,key);
    point x1 = n->it.getP1();
    x1.x += i*50;
    point x2 = n->it.getP2();
    x2.x += i*50;
    rectangle r1(x1,x2);
    n->keyBlock.insert(n->keyBlock.begin()+i,r1);
    return r1;


}


rectangle Bptree::findPosition(node* n1){
    if(n1 == root){
        point x1(475,10);
        point x2(525,40);
        rectangle r1(x1,x2);
        return r1;
    }else if(n1->leftSib == nullptr){
        point x1 = n1->parent->it.getP1();
        x1.x -= order*60;
        x1.y += 60;
        point x2 = n1->parent->it.getP2();
        x2.x -= order*60;
        x2.y += 60;

        rectangle r1(x1,x2);
        n1->parent->keyBlock[0] = r1;

        return r1;
    }else{
        int pos = findCpos(n1);
        point x1 = n1->leftSib->it.getP1();
        x1.x += order*60;
        point x2 = n1->leftSib->it.getP2();
        x2.x += order*60;
    }

}

void Bptree::conncetNode(node*,node*){

}


void Bptree::moveToPosition(rectangle& a, point& p1,point& p2){

    while(a.getP1().y != p1.y ){
        if(p1.y > a.getP1().y){
            a.move(DOWN);
        }else{
            a.move(UP);
        }
        a.draw(g);
        g.update();
        a.erase(g);
        g.Sleep(delay);
    }


    while(a.getP1().x != p1.x){
        if(p1.x > a.getP1().x){
            a.move(RIGHT);
        }else{
            a.move(LEFT);
        }
        a.draw(g);
        g.update();
        a.erase(g);
        g.Sleep(delay);
    }


    a.draw(g);
}


void Bptree::adjustGraphL(node* n){

}

void Bptree::adjustGraphR(node* n){
    if(n){
        node* temp = n;
        while(n->rightSib){
            n = n->rightSib;
        }

        while(n && n != temp){
            for(int i = n->keyBlock.size()-1 ;i > 0;i++){
                point x1 = n->keyBlock[i].getP1();
                x1.x += 60;

                point x2 = n->keyBlock[i].getP2();
                x2.x += 60;

                moveToPosition(n->keyBlock[i],x1,x2);
            }
            temp = temp->leftSib;
        }
    }

}