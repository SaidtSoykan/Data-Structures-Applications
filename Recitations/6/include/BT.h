#ifndef BT_DEF
#define BT_DEF

#include <vector>
#include "BTNode.h"

using namespace std;

class BT{
    private:
        Node* root;

        void inorder_traverse(Node*);
        void postorder_traverse(Node*);
        void postorder_destruct(Node*);

    public:
        BT();
        ~BT();

        Node* get_root();
        void add(vector<int>);

        void printPostOrder();
        void printInOrder();
};

#endif
