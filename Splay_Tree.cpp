#include <iostream>
#include <stdio.h>

using namespace std;

struct node{
    int key;
    node* left;
    node* right;
    node* parent;
};

void rotate(node* child, node* parent);                 // Rotation
bool find(node*& root, int value);                      // Search
node* insert(node* root, int value);                    // Insertion
node* splay(node* t);                                   // Splay t to root
void display(node* r);                                  // Display Tree In Order

node* insert(node* root, int value){
    node* r = root;

    if(r == nullptr){                                   //IF root is null, return tree with given value
        r = new node{value, nullptr, nullptr, nullptr};
        return r;
    }
    else{                                               //ELSE create tree
        while(r != nullptr){
            node* r_shadow = r;                         //shadow clone node before moving left or right
            if(value <= r->key){
                if(r->left == nullptr){

                    r->left = new node;                 //Create new Node
                    r->left->key = value;               //Set value to new Node
                    r->left->left = nullptr;            //Left Child set to Null
                    r->left->right = nullptr;           //Right child set to Null
                    r->left->parent = r_shadow;         //Link parent to grand parent

                    return root = splay(r->left);       //return new root after it's splayed
                }
                else
                    r = r->left;
            }
            else{
                if(r->right == nullptr){

                    r->right = new node;
                    r->right->key = value;
                    r->right->left = nullptr;
                    r->right->right = nullptr;
                    r->right->parent = r_shadow;

                    return root = splay(r->right);
                }
                else
                    r = r->right;
            }
        }//end of inserting nodes
    }
    return r;
}
bool find(node*& root, int value){          //Function to find node in Splay Tree
    node* r = root;

    while(r != nullptr){
        if(r->key == value){
            root = splay(r);                //splayed found node
            return true;
        }
        else{
            if(value < r->key)
                r = r->left;
            else
                r = r->right;
        }
    }
    return false;
}
node* splay(node* t){                       //Function to SPLAY Tree

    if(t->parent == nullptr){               //base case to root
        return t;
    }
    else{
        rotate(t, t->parent);
        return splay(t);                    //return the splayed result
    }
}

void rotate(node* child, node* parent){     //Rotation Function

    node* X = nullptr;
    node* Y = nullptr;
    node* Z = nullptr;

    if(child == parent->left){              //rotate right

        /**    P
              / \
             C   Z
            / \
           X   Y    **/

        X = child->left;
        Y = child->right;
        Z = parent->right;
        node* Alpha = parent;

        parent->left = X;
        parent = child;
        parent->right = Alpha;

        if(Alpha->parent == nullptr){
            parent->parent = nullptr;
        }
        else{
            node* Bravo = Alpha->parent;    //grand parent
            if(Bravo->key > parent->key)    //determine if grand parent is less or greater than
                Bravo->left = parent;
            else
                Bravo->right = parent;
            parent->parent = Bravo;
        }

        if(X != nullptr)
            X->parent = parent;
        Alpha->parent = parent;

        Alpha->left = Y;
        Alpha->right = Z;
        if(Y != nullptr)
            Y->parent = Alpha;
        if(Z != nullptr)
            Z->parent = Alpha;
    }
    else{                                   //rotate LEFT

        /**   P
             / \
            X   C
               / \
              Y   Z  **/

        X = parent->left;
        Y = child->left;
        Z = child->right;
        node* Alpha = parent;

        parent->right = Z;
        parent = child;
        parent->left = Alpha;

        if(Alpha->parent == nullptr)
            parent->parent = nullptr;
        else{
            node* Bravo = Alpha->parent;    //grand parent
            if(parent->key > Bravo->key)    //determine if grand parent is less than equal
                Bravo->right = parent;
            else
                Bravo->left = parent;
            parent->parent = Bravo;         //set parent node to grand parent
        }

        if(Z != nullptr)
            Z->parent = parent;
        Alpha->parent = parent;

        Alpha->left = X;
        Alpha->right = Y;
        if(X != nullptr)
            X->parent = Alpha;
        if(Y != nullptr)
            Y->parent = Alpha;
    }
}

void display(node* r){                      //Display Inorder
    if(r != nullptr){
        display(r->left);
        cout <<r->key<<endl;
        display(r->right);
    }

}
