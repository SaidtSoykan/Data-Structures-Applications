#pragma once
#include "MultiNode.h"
#include <string>

using namespace std;

class MultiList{
    private:
        DateNode* head;
        DateNode* tail;

    public:
        MultiList();
        ~MultiList();
        void add_node(string,string,string);
        void remove_node(string,string);
        void print_list();
        DateNode* search_prev_hor(string);
        TSiteNode* search_prev_ver(string,TSiteNode*);
        void add_ver(string,string,DateNode*);
        void delete_ver(string,DateNode*);

};