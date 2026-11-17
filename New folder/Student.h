
#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include <string>
using namespace std;

class Student : public Person {
private:
    int id;
    double marks;

public:
    Student(int i, string n, int a, double m);

    int getId() const;
    string getName() const;
    int getAge() const;
    double getMarks() const;

    void setName(string n);
    void setAge(int a);
    void setMarks(double m);

    string getGrade() const;

    void display() const override;
};

#endif
