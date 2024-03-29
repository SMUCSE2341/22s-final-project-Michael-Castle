//
// Created by willk on 4/10/2022.
//

//using code from https://www.programiz.com/dsa/avl-tree

#ifndef INC_22S_FINAL_PROJ_DSAVLTREE_H
#define INC_22S_FINAL_PROJ_DSAVLTREE_H

template <typename type>
struct DSNode {
int height = 0;
DSNode* left = nullptr;
DSNode* right = nullptr;
type data;

DSNode(type input, DSNode<type>* l, DSNode<type>* r, int h) {
    data = input;
    left = l;
    right = r;
    height = h;
}

DSNode(type d) {
    data = d;
    left = nullptr;
    right = nullptr;
    height = 0;
}



};

template <typename type>
class DSTree {

public:
    DSNode<type>* head = nullptr;
    int height(DSNode<type>* input) {
        if(input == nullptr)
            return -1;
        return input->height;
    }
    int getBalance(DSNode<type>* input) {
        if(input == nullptr) {
            return 0;
        }
        return (height(input->left) - height(input->right));
    }

    DSNode<type>* findValue(type input) {
        return findValue(input, head);
    }

    DSNode<type>* findValue(type input, DSNode<type>* head) {

        if(head == nullptr) {
            return nullptr;
        }
        if(head->data == input) {
            return head;
        }
        else if(head->data < input) {
            return findValue(input, head->right);
        }
        else  {
            return findValue(input, head->left);
        }
    }

    DSNode<type>* leftLeftRotate(DSNode<type>* input) {
        DSNode<type>* leftChild = input->left;
        input->right = leftChild->left;

        //input->right = rightChild->left;
        //rightChild->left = input;

    }
    DSNode<type>* insert(type x) {
        return insert(x, head);

    }
    DSNode<type>* insert(type& x, DSNode<type> * & top) {
        if(top == nullptr) {
            top = new DSNode<type>(x);


        }
        else if (x < top->data)
            insert(x,top->left);
        else if (top->data < x)
            insert(x, top->right);
        else
        {
            //do stuff for duplicate
        }
        balance(top);

        return top;

    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    void rotateWithLeftChild(DSNode<type>* & k2) {
        DSNode<type>* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) +1;
        k2 = k1;
        //not done yet???

    }
    void rotateWithRightChild(DSNode<type>* & k2) {
        DSNode<type>* k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        k2->height = max(height(k2->left), height(k2->right))+1;
        k1->height = max(height(k1->right), k2->height) + 1;
        k2 = k1;
    }

    void doubleWithLeftChild( DSNode<type> * & k3 )
     {
         rotateWithRightChild( k3->left );
         rotateWithLeftChild( k3 );
     }

     void doubleWithRightChild(DSNode<type> * & k3) {
         rotateWithLeftChild( k3->right );
         rotateWithRightChild( k3 );
    }

    void balance(DSNode<type>* & t) {
        if(t == nullptr) {
            return;
        }
        if( height( t->left ) - height( t->right ) > 1) {
            if(height(t->left->left) >= height(t->left->right)){
                rotateWithLeftChild(t);
            }
            else {
                doubleWithLeftChild(t);
            }
        }
        else if(height( t->right ) - height( t->left ) > 1) {
            if(height(t->right->right) >= height(t->right->left)) {
                rotateWithRightChild(t);
            }
            else {
                doubleWithRightChild(t);
            }
        }
        t->height = max(height(t->left), height(t->right)) + 1;
    }

    ~DSTree() {
        recursiveDelete(head);
    }

    void recursiveDelete(DSNode<type>* input) {
        if(input != nullptr) {
            recursiveDelete(input->left);
            recursiveDelete(input->right);
            delete input;
        }
    }
    vector<type> toVector() {
        vector<type> outVector;
        recursiveVector(head, &outVector);
        return outVector;

    }

    void recursiveVector(DSNode<type>* input, vector<type>* v) {
        if(input != nullptr) {
            recursiveVector(input->left, v);
            recursiveVector(input->right, v);
            v->push_back(input->data);
        }
    }


};

#endif //INC_22S_FINAL_PROJ_DSAVLTREE_H
