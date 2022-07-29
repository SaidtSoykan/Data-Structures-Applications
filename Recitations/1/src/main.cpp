/* @Author
Student Name: <Muhammed Said Soykan>
Student ID : <150190732>
Date: <10.03.2022> */
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;


class Student{
    private:
        string name;
        int grade;
    public:
        Student();
        ~Student();
        void set_grade(int);
        int get_grade();
        string get_name();
        void set_name(string);
};

Student::Student()
{
}

Student::~Student()
{
}

void Student::set_grade(int sgrade)
{
    if(sgrade<0)
        grade=0;
    else
        grade = sgrade;
}

int Student::get_grade()
{
    return grade;
}

string Student::get_name()
{
    return name;
}

void Student::set_name(string sname)
{
    name = sname;
}



bool perform_operation(char);
void print_menu();
void listStudents();
void addStudent();
void maxGradeStudent();


int capacity = 0;
Student astudents[10];

int main(){

    bool end = false;
    char choice;


    while (!end)
    {
        print_menu();
        cin >> choice;
        end = perform_operation(choice);
    }

    return EXIT_SUCCESS;
}

void print_menu()
{
    cout << "Choose an operation" << endl;
    cout << "A: Add student" << endl;
    cout << "L: List students" << endl;
    cout << "M: Name and grade of the student with the highest grade" << endl;
    cout << "E: Exit" << endl;
    cout << "Enter a choice {A,L,M,E}: ";
}

bool perform_operation(char choice)
{
    bool terminate = false;
    string strday;

    switch (choice)
    {
    case 'L':
    case 'l':
        listStudents();
        break;
    case 'A':
    case 'a':
        addStudent();
        break;
    case 'M':
    case 'm':
        maxGradeStudent();
        break;
    case 'E':
    case 'e':
        terminate = true;
        break;
    default:
        cout << "Error: You have entered an invalid choice" << endl;
        cin >> choice;
        terminate = perform_operation(choice);
        break;
    }
    return terminate;
}

void listStudents()
{   //*** Fill here. List astudents array with student name and grades.
    for(int i = 0;i<capacity;i++){
        cout<<astudents[i].get_name()<<":"<<astudents[i].get_grade()<<endl;
    }
}

void addStudent()
{
    string name;
    int grade;
    cout << "Enter the name of student: ";
    cin >> name;
    cout << "Enter the grade of student: ";
    cin >> grade;

    //*** Fill here. Set the name and grade of the student for astudents array
    //and increase capacity by 1.
    if(capacity == 10)
        return;
    else{
        astudents[capacity].set_name(name);
        astudents[capacity].set_grade(grade);
        capacity++;
    }
}

void maxGradeStudent()
{
    //*** Fill here. Find the student with the highest grade.
    int mark = 0;
    if(capacity == 1)
        cout<<astudents[0].get_name()<<":"<<astudents[0].get_grade()<<endl;
    else if(capacity == 0)
        return;
    else{
        for(int i=1;i<capacity;i++){
            if(astudents[mark].get_grade()<astudents[i].get_grade()){
                mark = i;
            }
    }
        cout<<astudents[mark].get_name()<<":"<<astudents[mark].get_grade()<<endl;
    }
    
}