#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "BT.h"
#include "Set.h"
using namespace std;


void readAndFill(BT* bt1, BT* bt2, const char* path)
{
    fstream infile;                 // Initializes the file operation
    infile.open(path, ios::in);     // Opens the file pointer
    string buffer;
    string delim = " ";
    int digit;
    int turn = 1;

    vector<int> digits;

    if (infile.is_open()){
        while(getline(infile,buffer)){
            auto start = 0U;
            auto end = buffer.find(delim);

            while (end != std::string::npos){
                digit = stoi(buffer.substr(start, end - start));
                start = end + delim.length();
                end = buffer.find(delim, start);
                digits.push_back(digit);
            }

            if (buffer != ""){
                digit = stoi(buffer.substr(start, end - start));
                digits.push_back(digit);
            }

            if (turn == 1){
                bt1->add(digits);
                turn++;
                digits.clear();
            }
            else if (turn == 2){
                bt2->add(digits);
                break;
            }
        }
    }
}


int main(int argc, char** argv){

    BT* bt1 = new BT();
    BT* bt2 = new BT();
    Set set;

    readAndFill(bt1, bt2, argv[1]);

    vector<int> intersect_members = set.get_intersection(bt1, bt2);
    vector<int> union_members = set.get_union(bt1, bt2);

    // I sort the intersection and union set members for evaluation purposes
    sort(intersect_members.begin(), intersect_members.end());
    sort(union_members.begin(), union_members.end());

    if (!intersect_members.empty()){
        cout << "Intersecting nodes" << endl;
        for(auto data: intersect_members){
            cout << data << " ";
        }
    }
    else{
        cout << "No intersecting nodes found.";
    }
    cout << endl;
    cout << "Union nodes" << endl;
    for(auto data: union_members){
        cout << data << " ";
    }
    cout << endl;
    
    delete bt1;
    delete bt2;

    return EXIT_SUCCESS;
}