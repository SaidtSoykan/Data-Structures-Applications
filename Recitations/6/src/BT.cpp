#include <iostream>
#include <stack>
#include <list>
#include <queue>
#include "BT.h"

using namespace std;

BT::BT()
{
    root = nullptr;
}

BT::~BT()
{
    if (this->root != nullptr)
        this->postorder_destruct(this->root);
    this->root=nullptr;
}

Node* BT::get_root()
{
    return this->root;
}

void BT::add(vector<int> data)
{
    queue<Node*> q;
    Node* temp;
    int turn = 0;    // Suggests the left turn
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

void BT::inorder_traverse(Node* n)
{
    if (n != nullptr){
        postorder_traverse(n->get_left());
        cout << n->get_data() << " ";
        postorder_traverse(n->get_right());
    }
}

void BT::postorder_traverse(Node* n)
{
    if (n != nullptr){
        postorder_traverse(n->get_left());
        postorder_traverse(n->get_right());
        cout << n->get_data() << " ";
    }
}

void BT::postorder_destruct(Node* n)
{
    if (n != nullptr){
        this->postorder_destruct(n->get_left());
        this->postorder_destruct(n->get_right());
        delete n;
    }
}

void BT::printPostOrder()
{
    this->postorder_traverse(this->root);
    cout << endl;
}

void BT::printInOrder()
{
    this->inorder_traverse(this->root);
    cout << endl;
}