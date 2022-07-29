#include <vector>
#include <bits/stdc++.h>
#include "Set.h"


vector<int> Set::get_intersection(BT* bt1, BT* bt2)
{
    vector<int> intersections;
    //     ___     ___      _        _     
    //    | __|   |_ _|    | |      | |    
    //    | _|     | |     | |__    | |__  
    //   _|_|_    |___|    |____|   |____| 
    // _| """ | _|"""""| _|"""""| _|"""""| 
    // "`-0-0-' "`-0-0-' "`-0-0-' "`-0-0-' 
    unordered_map <int,int> intersections_map;
    Node* root1 = bt1->get_root();
    Node* root2 = bt2->get_root();
    vector<Node*> s,g;
    //Using the "Stack" we first add the elements from the bt1 tree to the unordered_map
    while (root1 != NULL || s.empty() == false)
    {
        while (root1 !=  NULL)
        {
            s.push_back(root1);
            root1 = root1->get_left();
        }
        root1 = s.back();
        s.pop_back();
        //While adding to the unordered_map, we use the elements from bt1 as key_values and fill the map with 1.
        intersections_map.emplace(root1->get_data(),1);
        root1 = root1->get_right();
    }
    //Using the "Stack" we first add the elements from the bt2 tree to the unordered_map
    while (root2 != NULL || g.empty() == false)
    {
        while (root2 !=  NULL)
        {
            g.push_back(root2);
            root2 = root2->get_left();
        }
        root2 = g.back();
        g.pop_back();
        //To find the intersection elements, we add the values to the intersection vector according to the key_values of the unordered_map we created.
        if(intersections_map[root2->get_data()] == 1){
            intersections.push_back(root2->get_data());
        }
        //If the same element is not in the unordered_map, we add it to the unordered_map, not the intersection vector.
        else{
            intersections_map.emplace(root2->get_data(),1);
        }
        root2 = root2->get_right();
    }
    return intersections;
}

vector<int> Set::get_union(BT* bt1, BT* bt2)
{
    vector<int> unions;
    //     ___     ___      _        _     
    //    | __|   |_ _|    | |      | |    
    //    | _|     | |     | |__    | |__  
    //   _|_|_    |___|    |____|   |____| 
    // _| """ | _|"""""| _|"""""| _|"""""| 
    // "`-0-0-' "`-0-0-' "`-0-0-' "`-0-0-' 
    unordered_map <int,int> unions_map;
    Node* root1 = bt1->get_root();
    Node* root2 = bt2->get_root();
    vector<Node*> s,g;
    //Using the "Stack" we first add the elements from the bt1 and bt2 tree to the unordered_map
    while (root1 != NULL || s.empty() == false)
    {
        while (root1 !=  NULL)
        {
            s.push_back(root1);
            root1 = root1->get_left();
        }
        root1 = s.back();
        s.pop_back();
        //While adding to the unordered_map, we use the elements from bt1 as key_values and fill the map with 1.
        unions_map.emplace(root1->get_data(),1);
        //Since we need to find the union set, we add all the elements to the union vector
        unions.push_back(root1->get_data());
        root1 = root1->get_right();
    }
    //Using the "Stack" we first add the elements from the bt2 tree to the unordered_map
    while (root2 != NULL || g.empty() == false)
    {
        while (root2 !=  NULL)
        {
            g.push_back(root2);
            root2 = root2->get_left();
        }
        root2 = g.back();
        //If the same element is not in the unordered_map we add to both the union vector and the unordered_map
        if(unions_map[root2->get_data()] != 1){
            unions_map.emplace(root2->get_data(),1);
            unions.push_back(root2->get_data());
        }
        g.pop_back();
        root2 = root2->get_right();
    }
    return unions;
}

