
#include "StudentManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cctype>

using namespace std;

// Rebuild ID index after vector modifications
void StudentManager::rebuildIndex() {
    studentIndex.clear();

    for (size_t i = 0; i < students.size(); i++) {
        studentIndex[students[i].getId()] = i;
    }
}

// Validate student information
void StudentManager::validateStudent(
    const string& name, int age, double marks
) const {

    if (name.empty() || name.find(',') != string::npos) {
        throw InvalidStudentDataException(
            "Name cannot be empty or contain commas!"
        );
    }

    if (name.find_first_not_of(" \t") == string::npos) {
        throw InvalidStudentDataException(
            "Name cannot contain only spaces!"
        );
    }

    if (age < 1 || age > 100) {
        throw InvalidStudentDataException(
            "Age must be between 1 and 100!"
        );
    }

    if (marks < 0 || marks > 100) {
        throw InvalidStudentDataException(
            "Marks must be between 0 and 100!"
        );
    }
}

// Add student
void StudentManager::addStudent(const Student& s) {

    validateStudent(s.getName(), s.getAge(), s.getMarks());

    if (studentIndex.find(s.getId()) != studentIndex.end()) {
        throw DuplicateStudentException();
    }

    students.push_back(s);
    rebuildIndex();

    cout << "\nStudent added successfully!\n";
}

// Display all students
void StudentManager::displayAll() const {

    if (students.empty()) {
        cout << "\nNo student records available.\n";
        return;
    }

    cout << "\n========== STUDENT RECORDS ==========\n";

    cout << left
         << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(10) << "Age"
         << setw(12) << "Marks"
         << setw(10) << "Grade"
         << endl;

    cout << string(62, '-') << endl;

    for (const Student& s : students) {
        s.display();
    }
}

// Search student using unordered_map and find_if
void StudentManager::searchStudent(int id) const {

    auto it = studentIndex.find(id);

    if (it == studentIndex.end()) {
        throw StudentNotFoundException();
    }

    auto student = find_if(
        students.begin(),
        students.end(),
        [id](const Student& s) {
            return s.getId() == id;
        }
    );

    if (student != students.end()) {
        cout << "\nStudent Found:\n";
        student->display();
    }
}

// Update student
void StudentManager::updateStudent(
    int id, string name, int age, double marks
) {

    auto it = studentIndex.find(id);

    if (it == studentIndex.end()) {
        throw StudentNotFoundException();
    }

    validateStudent(name, age, marks);

    Student& s = students[it->second];

    s.setName(name);
    s.setAge(age);
    s.setMarks(marks);

    cout << "\nStudent updated successfully!\n";
}

// Delete student
void StudentManager::deleteStudent(int id) {

    auto it = studentIndex.find(id);

    if (it == studentIndex.end()) {
        throw StudentNotFoundException();
    }

    students.erase(students.begin() + it->second);

    rebuildIndex();

    cout << "\nStudent deleted successfully!\n";
}

// Sort students according to marks
void StudentManager::sortByMarks() {

    sort(
        students.begin(),
        students.end(),
        [](const Student& a, const Student& b) {
            return a.getMarks() > b.getMarks();
        }
    );

    rebuildIndex();

    cout << "\nStudents sorted by marks (highest first).\n";

    displayAll();
}

// Display class statistics using map and transform
void StudentManager::showStatistics() const {

    if (students.empty()) {
        cout << "\nNo records available for statistics.\n";
        return;
    }

    double total = accumulate(
        students.begin(),
        students.end(),
        0.0,
        [](double sum, const Student& s) {
            return sum + s.getMarks();
        }
    );

    double average = total / students.size();

    // Count students by grade
    map<string, int> gradeCount;

    vector<string> grades(students.size());

    transform(
        students.begin(),
        students.end(),
        grades.begin(),
        [](const Student& s) {
            return s.getGrade();
        }
    );

    for (const string& grade : grades) {
        gradeCount[grade]++;
    }

    cout << "\n========== CLASS STATISTICS ==========\n";

    cout << "Total Students: " << students.size() << endl;

    cout << fixed << setprecision(2);
    cout << "Class Average: " << average << endl;

    cout << "\nGrade Distribution:\n";

    for (const auto& entry : gradeCount) {
        cout << "Grade " << entry.first
             << " : " << entry.second
             << " student(s)\n";
    }
}

// Save records in CSV file
void StudentManager::saveToFile(
    const string& filename
) const {

    ofstream file(filename);

    if (!file.is_open()) {
        throw FileException();
    }

    for (const Student& s : students) {

        file << s.getId() << ","
             << s.getName() << ","
             << s.getAge() << ","
             << s.getMarks() << "\n";
    }

    if (!file) {
        throw FileException();
    }

    file.close();
}

// Load records from CSV file
void StudentManager::loadFromFile(
    const string& filename
) {

    ifstream file(filename);

    // First run: file may not exist yet
    if (!file.is_open()) {
        return;
    }

    vector<Student> loadedStudents;
    unordered_map<int, bool> loadedIds;

    string line;

    while (getline(file, line)) {

        if (line.empty()) {
            continue;
        }

        stringstream ss(line);

        string idStr, name, ageStr, marksStr;

        if (!getline(ss, idStr, ',') ||
            !getline(ss, name, ',') ||
            !getline(ss, ageStr, ',') ||
            !getline(ss, marksStr)) {

            continue;
        }

        try {
            size_t p1, p2, p3;

            int id = stoi(idStr, &p1);
            int age = stoi(ageStr, &p2);
            double marks = stod(marksStr, &p3);

            if (p1 != idStr.size() ||
                p2 != ageStr.size() ||
                p3 != marksStr.size()) {
                continue;
            }

            validateStudent(name, age, marks);

            if (id <= 0 || loadedIds.count(id)) {
                continue;
            }

            loadedStudents.emplace_back(
                id, name, age, marks
            );

            loadedIds[id] = true;

        }
        catch (const exception&) {
            // Skip invalid or corrupted CSV rows
            continue;
        }
    }

    students = move(loadedStudents);

    rebuildIndex();

    cout << "\nStudent records loaded successfully.\n";
}
