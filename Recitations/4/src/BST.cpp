#include <iostream>
#include <stack>
#include <list>
#include <queue>
#include "BST.h"

using namespace std;

BST::BST()
{
    this->root=nullptr;
}

BST::~BST()
{
    postorder_destruct(root);
}

Node* BST::get_root()
{
    return this->root;
}

void BST::add(int data)
{
    if(this->get_root() == NULL){
        this->root = new Node(data);
    }
    else {
        this->get_root()->add(data);
    }
}

void Node::add(int data)
{
    if(this->get_data() > data){
        if(this->get_left() != NULL){
            this->get_left()->add(data);
        }  
        else{
            this->set_left(new Node(data));
        } 
    }          
    else if(this->get_data() < data){
        if(this->get_right() != NULL){
            this->get_right()->add(data);
        }
        else{
            this->set_right(new Node(data));
        } 
    }         
    else{
        return;
    }
}

void BST::corrupted_add(vector<int> data)
{
    queue<Node*> q;
    Node* temp;
    int turn = 0;
    while (!data.empty()){
        int num = data.back();
        data.pop_back();

        if (num == INT32_MIN){
            q.pop();
            continue;
        }

        Node* n = new Node(num);

        if (root == nullptr){
            root = n;
            q.push(root);
            q.push(root);
        }
        else{
            temp = q.front();
            q.pop();
            if(turn == 0){
                temp->set_left(n);
                turn = 1;
            }
            else if(turn == 1){
                temp->set_right(n);
                turn = 0;
            }
            q.push(n);
            q.push(n);
        }
    }
}

bool BST::contains(int data)
{
    Node* temp = root;
    while(true){
        if(temp->get_data() == data){
            return true;
        }
        else if(temp->get_data() < data && temp->get_right() == nullptr){
            return false;
        }
        else if(temp->get_data() > data && temp->get_left() == nullptr){
            return false;
        }
        else if(temp->get_data() < data){
            temp = temp->get_right();
        }
        else if(temp->get_data() > data){
            temp = temp->get_left();
        }
    }
}

void BST::postorder_traverse(Node* temp)
{
    //Here, since the postorder traverse function cannot return a value or a pointer, I printed the output in this function.
    if (temp == NULL){
        return;
    }
    else{
        postorder_traverse(temp->get_left());
        postorder_traverse(temp->get_right());
        cout << temp->get_data() << " ";
    }
}

void BST::postorder_destruct(Node* temp)
{
   if(temp){
        postorder_destruct(temp->get_left());
        postorder_destruct(temp->get_right());
        delete temp;
    }
}

void BST::printPostOrder()
{
    this->postorder_traverse(this->get_root());
    cout << endl;
}

bool BST::isBST(Node* node)
{
    //Here I checked if a subtree is valid if it's valid function returns true
    if (node == NULL){
        return true;
    }    
    if (node->get_left() != NULL && node->get_left()->get_data() > node->get_data()){
        return false;
    }       
    if (node->get_right() != NULL && node->get_right()->get_data() < node->get_data()){
        return false;
    }  
    if (!isBST(node->get_left()) || !isBST(node->get_right())){
        return false;
    }
        return true;
}

int BST::sumBST(Node *root)
{
    //Here I calculated the sum of all elements of a valid subtree
    int sum;
    if (root == NULL){
        return 0;
    }
    sum = root->get_data() + sumBST(root->get_left()) + sumBST(root->get_right());
    return sum;
}

int BST::maxSumBST(Node* node)
{
    // Find the sum of the Binary Search Tree with the maximum sum within the Binary Tree
    int sum = 0;
    while(true){
        //In this loop, if the subtree is valid, I add its elements and compare it with the sum of the elements of other valid subtrees and return the largest sum
        if(node == nullptr){
            break;
        }
        else{
            if(isBST(node)){
                if(sum < sumBST(node)){
                    sum = sumBST(node);
                }
                break;
            }
            else{
                return maxSumBST(node->get_left()) , maxSumBST(node->get_right());
            }
        }
    }
    return sum;
}