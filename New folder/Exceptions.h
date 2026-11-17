
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>
using namespace std;

class DuplicateStudentException : public runtime_error {
public:
    DuplicateStudentException()
        : runtime_error("Student ID already exists!") {}
};

class StudentNotFoundException : public runtime_error {
public:
    StudentNotFoundException()
        : runtime_error("Student record not found!") {}
};

class InvalidStudentDataException : public runtime_error {
public:
    InvalidStudentDataException(const string& message)
        : runtime_error(message) {}
};

class FileException : public runtime_error {
public:
    FileException()
        : runtime_error("Unable to save student records!") {}
};

#endif
