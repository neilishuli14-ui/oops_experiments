
#include "Student.h"
#include <iostream>
#include <iomanip>
using namespace std;

Student::Student(int i, string n, int a, double m)
    : Person(n, a), id(i), marks(m) {}

int Student::getId() const {
    return id;
}

string Student::getName() const {
    return name;
}

int Student::getAge() const {
    return age;
}

double Student::getMarks() const {
    return marks;
}

void Student::setName(string n) {
    name = n;
}

void Student::setAge(int a) {
    age = a;
}

void Student::setMarks(double m) {
    marks = m;
}

string Student::getGrade() const {
    if (marks >= 90) return "A+";
    else if (marks >= 80) return "A";
    else if (marks >= 70) return "B";
    else if (marks >= 60) return "C";
    else if (marks >= 40) return "D";
    else return "F";
}

void Student::display() const {
    cout << left
         << setw(10) << id
         << setw(20) << name
         << setw(10) << age
         << setw(12) << fixed << setprecision(2) << marks
         << setw(10) << getGrade()
         << endl;
}
