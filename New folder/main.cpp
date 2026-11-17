
#include <iostream>
#include <limits>
#include <string>

#include "StudentManager.h"

using namespace std;

int readInt(const string& prompt) {
    int value;

    while (true) {
        cout << prompt;

        if (cin >> value) {
            cin.ignore(
                numeric_limits<streamsize>::max(), '\n'
            );
            return value;
        }

        cout << "Invalid input! Enter an integer.\n";

        cin.clear();
        cin.ignore(
            numeric_limits<streamsize>::max(), '\n'
        );
    }
}

double readDouble(const string& prompt) {
    double value;

    while (true) {
        cout << prompt;

        if (cin >> value) {
            cin.ignore(
                numeric_limits<streamsize>::max(), '\n'
            );
            return value;
        }

        cout << "Invalid input! Enter a number.\n";

        cin.clear();
        cin.ignore(
            numeric_limits<streamsize>::max(), '\n'
        );
    }
}

string readName() {
    string name;

    cout << "Enter Student Name: ";
    getline(cin, name);

    return name;
}

void displayMenu() {
    cout << "\n";
    cout << "========================================\n";
    cout << "       STUDENT MANAGEMENT SYSTEM\n";
    cout << "========================================\n";

    cout << "1. Add Student\n";
    cout << "2. Display All Students\n";
    cout << "3. Search Student\n";
    cout << "4. Update Student\n";
    cout << "5. Delete Student\n";
    cout << "6. Sort Students by Marks\n";
    cout << "7. Show Class Statistics\n";
    cout << "8. Save Records\n";
    cout << "9. Exit\n";

    cout << "========================================\n";
}

int main() {

    StudentManager manager;

    const string filename = "students.csv";

    // Load previous records
    manager.loadFromFile(filename);

    int choice;

    do {
        displayMenu();

        choice = readInt("Enter your choice: ");

        try {

            switch (choice) {

                case 1: {
                    int id = readInt("Enter Student ID: ");
                    string name = readName();
                    int age = readInt("Enter Age: ");
                    double marks = readDouble("Enter Marks: ");

                    Student s(id, name, age, marks);

                    manager.addStudent(s);
                    break;
                }

                case 2:
                    manager.displayAll();
                    break;

                case 3: {
                    int id = readInt("Enter Student ID to search: ");

                    manager.searchStudent(id);
                    break;
                }

                case 4: {
                    int id = readInt("Enter Student ID to update: ");

                    string name = readName();
                    int age = readInt("Enter New Age: ");
                    double marks = readDouble("Enter New Marks: ");

                    manager.updateStudent(
                        id, name, age, marks
                    );

                    break;
                }

                case 5: {
                    int id = readInt("Enter Student ID to delete: ");

                    manager.deleteStudent(id);
                    break;
                }

                case 6:
                    manager.sortByMarks();
                    break;

                case 7:
                    manager.showStatistics();
                    break;

                case 8:
                    manager.saveToFile(filename);
                    cout << "\nRecords saved successfully!\n";
                    break;

                case 9:
                    manager.saveToFile(filename);

                    cout << "\nRecords saved successfully.\n";
                    cout << "Thank you for using the system!\n";
                    break;

                default:
                    cout << "\nInvalid choice! Try again.\n";
            }

        }
        catch (const exception& e) {
            cout << "\nError: " << e.what() << endl;
        }

    } while (choice != 9);

    return 0;
}
