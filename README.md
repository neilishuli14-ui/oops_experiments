
# Student Management System

## Project Overview
The Student Management System is a console-based
C++ application designed to manage student records.

It allows users to add, display, search, update and
delete student information. It also calculates grades,
class averages and grade distributions.

## Technologies Used
- C++
- Object-Oriented Programming
- STL
- Exception Handling
- File Handling
- Git and GitHub

## OOP Concepts Used

1. Encapsulation:
   Student data is private and accessed through
   public getter and setter methods.

2. Inheritance:
   Student inherits from the abstract Person class.

3. Abstraction:
   Person is an abstract class with a pure virtual
   display() function.

4. Polymorphism:
   Student overrides the virtual display() function.

## STL Concepts Used
- vector: Stores student records.
- unordered_map: Provides student ID indexing.
- map: Stores grade distribution.
- sort(): Sorts students by marks.
- find_if(): Searches for a student.
- transform(): Extracts student grades.
- accumulate(): Calculates total marks.

## Exception Handling
Custom exceptions are used for:
- Duplicate student IDs
- Missing student records
- Invalid student data
- File-saving errors

## Features
1. Add student records.
2. Display student records.
3. Search by student ID.
4. Update student information.
5. Delete student records.
6. Sort by marks.
7. Calculate class average.
8. Display grade distribution.
9. Save and load records using CSV files.

## How to Run

Compile all source files:

g++ -std=c++17 main.cpp Student.cpp StudentManager.cpp -o student

Run the application:

Windows:
student.exe

Linux/macOS:
./student

## Data Storage
Student records are stored in students.csv.
Records are automatically loaded when the application
starts and saved when the user exits.

## Conclusion
This project demonstrates the practical application
of OOP principles, STL containers and algorithms,
custom exception handling, and file handling in C++.
