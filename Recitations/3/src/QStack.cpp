/* @saidt
Student Name: <Muhammed Said Soykan>
Student ID : <150190732>
Date: <07/04/2022> */
#include <iostream>
#include <queue>
#include <QStack.h>


using namespace std;

void QStack::push(int x)
{
    //Fill this method
    int s = main.size();
    if(!main.empty()){
        int* arr = new int(s);
        for(int i=0;i<s;i++){
            arr[i] = main.front();
            main.pop();
        }
        main.push(x);
        for(int k=0;k<s;k++){
            main.push(arr[k]);
        }
        delete []arr;
    }
    else
        main.push(x);
}

void QStack::pop()
{
    //Fill this method
    if(main.empty()){
        cout<<"Stack is empty"<<endl;
    }
    else{
        cout<<main.front()<<" is popped"<<endl;
        main.pop();
    }
}

void QStack::printStack()
{
    if (main.empty())
        return;

    int x;
    for(unsigned long int i=0;i<main.size();i++)
    {
        x = main.front();
        main.pop();
        cout << x << ' ';
        main.push(x);
    }
}