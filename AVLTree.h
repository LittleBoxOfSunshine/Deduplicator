#ifndef Avl_and_hash_AVL_h
#define Avl_and_hash_AVL_h

#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstring>

template<typename key>/// avl node template with just a key
class AVLNode {
  private:
    int height;
    key* k;
    AVLNode* left;
    AVLNode* right;
  public:
    /// constructor
    AVLNode() {
        height = 0;
        left = nullptr;
        right = nullptr;
        k = new key();
    }


    int getHeight() {
        return height;
    }
    void setHeight(int h) {
        height = h;
    }
    key &getKey() {
        return *k;
    }
    void setKey(key &s) {
        delete k;
        k = new key(s);
    }
    AVLNode* &Left() {
        return left;
    }
    AVLNode* &Right() {
        return right;
    }
    ~AVLNode() {
        delete k;
    }
};

template<typename key>
class AVLTree {
  private:
    AVLNode<key>* tree;
  public:
    AVLTree() {
        tree = nullptr;
    }

    AVLNode<key>* &getTree() {
        return tree;
    }


    ///takes node key and a key pointer to insert to tree
    void insert(AVLNode<key>* &t, key &k, key* &kptr) {
        if (t == nullptr) {// if t is a null pointer, allocate t, set the key to key and kpter to memory address of key that was inserted
            t = new AVLNode<key>();
            t->setKey(k);
            kptr = &(t->getKey());
        }
        else if (k < t->getKey()) {//recursively call insert on the left child if k < the value in t
            insert(t->Left(), k, kptr);

            if (height(t->Left()) - height(t->Right()) == 2) {//if the height difference between the left and right child i 2
                if (k < t->Left()->getKey()) {//if k< the left child of key, rotate with left child, otherwise double rotate
                    rotateWithLChild(t);
                }
                else {
                    doubleRotateWithLChild(t);
                }
            }
        }
        else  if (t->getKey() < k) {//same as above, opposite conditions
            insert(t->Right(), k, kptr);

            if (height(t->Right()) - height(t->Left()) == 2) {
                if (t->Right()->getKey() < k) {
                    rotateWithRChild(t);
                }
                else {
                    doubleRotateWithRChild(t);
                }
            }
        }
        else {
            kptr = &(t->getKey());
        }

        t->setHeight(std::max(height(t->Left()), height(t->Right())) + 1);
    }
    ///same as above, without rotation, used to load an index
    void insertNoRotate(AVLNode<key>* &t, key &k, key* &kptr) {
        if (t == nullptr) {
            t = new AVLNode<key>();
            t->setKey(k);
            kptr = &(t->getKey());
        }
        else if (k < t->getKey()) {
            insert(t->Left(), k, kptr);
        }
        else  if (t->getKey() < k) {
            insert(t->Right(), k, kptr);
        }
        else {
            kptr = &(t->getKey());
        }

        t->setHeight(std::max(height(t->Left()), height(t->Right())) + 1);
    }

    ///return height if t is not null
    int height(AVLNode<key>* &t) {
        return t == nullptr ? -1 : t->getHeight();
    }

    ///prints contents of tree recursively, debugging purposes
    void printKey(AVLNode<key>* &t) {
        if (t != nullptr) {
            if (t->Left() != nullptr) {
                printKey(t->Left());
            }

            std::cout << t->getKey().getWord() << std::endl;

            if (t->Right() != nullptr) {
                printKey(t->Right());
            }
        }
    }

    ///rotate node with left child
    void rotateWithLChild(AVLNode<key>* &k2) {
        AVLNode<key>* k1 = k2->Left();//set k1 to the left child of k2
        k2->Left() = k1->Right();//since k1;'s right child is less than k2, k2's left child is now k1's right
        k1->Right() = k2;//k2 is bigger than k1 thus k2's right child =k2
        k2->setHeight(std::max(height(k1->Left()), k2->getHeight()) - 1);//update height
        k2 = k1;//set k2 to point to the new highest node
    }

    ///rotate ndoe with right child
    void rotateWithRChild(AVLNode<key>* &k2) {
        AVLNode<key>* k1 = k2->Right();
        k2->Right() = k1->Left();
        k1->Left() = k2;
        k2->setHeight(std::max(height(k1->Right()), k2->getHeight()) - 1);
        k2 = k1;
    }

    ///double rotate with left child
    void doubleRotateWithLChild(AVLNode<key>* &k3) {
        rotateWithRChild(k3->Left());
        rotateWithLChild(k3);
    }

    ///double rotate with right child
    void doubleRotateWithRChild(AVLNode<key>* &k3) {
        rotateWithLChild(k3->Right());
        rotateWithRChild(k3);
    }

    ///recursively deallocate pointers in the tree
    void makeEmpty(AVLNode<key>* &t) {
        // delete method from http://users.cis.fiu.edu/
        if (t != nullptr) {
            makeEmpty(t->Left());
            makeEmpty(t->Right());
            delete t;
        }

        t = nullptr;
    }

    /// recursively go through tree until the key - the key in the AVLNode and return the pointer
    key* find(AVLNode<key>* &t, key &k) {
        if (t == nullptr) {
            return nullptr;
        }

        if (k == t->getKey()) {
            return &t->getKey();
        }

        if (k < t->getKey()) {
            return find(t->Left(), k);
        }
        else {
            return find(t->Right(), k);
        }
    }

    ///used to recurse through tree and output the key using the output stream
    void output(AVLNode<key>* &t, std::ofstream &out) {
        if (t != nullptr) {
            t->getKey().saveToDisk(out);

            if (t->Left() != nullptr) {
                output(t->Left(), out);
            }

            if (t->Right() != nullptr) {
                output(t->Right(), out);
            }
        }
    }
    ///checks if a key is in the tree
    bool contains(AVLNode<key>* &t, key k) {
        if (t == nullptr) {
            return false;//recurse until t!=nullptr
        }

        if (k == t->getKey()) {
            return true;
        }

        if (k < t->getKey()) {
            return contains(t->Left(), k);
        }
        else {
            return contains(t->Right(), k);
        }
    }

    ///remove all nodes upon destruction
    ~AVLTree() {
        makeEmpty(this->tree);
    }
};
#endif
