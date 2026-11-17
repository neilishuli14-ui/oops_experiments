
#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include "Student.h"
#include "Exceptions.h"

#include <vector>
#include <unordered_map>
#include <map>
#include <string>
using namespace std;

class StudentManager {
private:
    vector<Student> students;
    unordered_map<int, size_t> studentIndex;

    void rebuildIndex();
    void validateStudent(
        const string& name, int age, double marks
    ) const;

public:
    void addStudent(const Student& s);
    void displayAll() const;
    void searchStudent(int id) const;
    void updateStudent(int id, string name, int age, double marks);
    void deleteStudent(int id);

    void sortByMarks();
    void showStatistics() const;

    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);
};

#endif
