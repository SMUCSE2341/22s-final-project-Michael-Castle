//
// Created by willk on 4/10/2022.
//

//using code from https://www.programiz.com/dsa/avl-tree

#ifndef INC_22S_FINAL_PROJ_DSAVLTREE_H
#define INC_22S_FINAL_PROJ_DSAVLTREE_H

template <typename type>
class DSNode {
public:
int height = 0;
DSNode* left = nullptr;
DSNode* right = nullptr;
DSNode* above = nullptr;
type data;

DSNode(type input, DSNode<type>* l, DSNode<type>* r, int h) {
    data = input;
    left = l;
    right = r;
    height = h;
}

DSNode(type d) {
    data = d;
}



};

template <typename type>
class DSTree {

public:
    DSNode<type>* head;
    int getHeight(DSNode<type>* input) {
        if(input == nullptr)
            return -1;
        return input->height;
    }
    int getBalance(DSNode<type>* input) {
        if(input == nullptr) {
            return 0;
        }
        return (getHeight(input->left) - getHeight(input->right));
    }

    DSNode<type>* findValue(type input, DSNode<type>* head) {

        if(head == nullptr) {
            return nullptr;
        }
        if(head->data == input) {
            return head;
        }
        else if(head->data < input) {
            return findValue(input, head->left);
        }
        else  {
            return findValue(input, head->right);
        }
    }

    DSNode<type>* leftLeftRotate(DSNode<type>* input) {
        DSNode<type>* leftChild = input->left;
        input->right = leftChild->left;

        //input->right = rightChild->left;
        //rightChild->left = input;

    }
    void insert(type x, DSNode<type>* top) {
        if(top == nullptr)
            top = new DSNode<type>(x);
        else if (x < top->data)
            insert(x,top->left);
        else if (top->data < x)
            insert(x, top->right);
        else
        {
            //doo stuff for duplicate
        }

    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    void rotateWithLeftChild(DSNode<type>* k2) {
        DSNode<type>* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(hieght(k1->left), k2->height) +1;
        k2 = k1;
        //not done yet

    }
    void rotateWithRightChild(DSNode<type>* k2) {
        DSNode<type>* k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        k2->height = max(height(k2->left), height(k2->right))+1;
        k1->height = max(height(k1->right), k2->height) + 1;
        k2 = k1;
    }

    void doubleWithLeftChild( DSNode<type> *  k3 )
     {
         rotateWithRightChild( k3->left );
         rotateWithLeftChild( k3 );
     }

    void balance(DSNode<type>* t) {
        if(getBalance(t) > 1) {
            if(height(t->left->left >= height(t->left->right)))
                rotateWithLeftChild(t);
            else
                doubleWithLeftChild(t);

        }
        else if(getBalance(t) < -1) {
            if(height(t->right->right) >= height(t->right->right))
                rotateWithRightChild(t);
            else
                doubleWithRightChild(t);
        }
        t->height = max(t->right, t->left);
    }


};

#endif //INC_22S_FINAL_PROJ_DSAVLTREE_H
