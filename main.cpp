#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Base class for both Student and Staff
class Person {
protected:
    string name;
    string prn_no;

public:
    // Default constructor with default values for name and PRN
    Person() : name(""), prn_no("") {}

    // Constructor
    Person(const string& name, const string& prn_no) : name(name), prn_no(prn_no) {}

    // Virtual destructor
    virtual ~Person() {}

    // Virtual function to display information
    virtual void displayInfo() const = 0; // Pure virtual function
};

// Student class inherits from Person
class Student : public Person {
    int roll_no;
    int pending;

public:
    // Default constructor
    Student() : roll_no(0), pending(0) {}

    // Constructor
    Student(int roll_no, const string& name, const string& prn_no, int pending)
        : Person(name, prn_no), roll_no(roll_no), pending(pending) {}

    // Destructor
    ~Student() {}

    // Function to display student information
    void displayInfo() const override {
        cout << "Roll number : " << roll_no << "\n"
             << "Name: " << name << "\n"
             << "PRN: " << prn_no << "\n";
    }

    // Getter for pending fees
    int getPendingFees() const {
        return pending;
    }

    // Getter for roll number
    int getRoll_no() const {
        return roll_no;
    }
};

// Function to search student by roll number
int searchStudent(Student S1[], int roll_no, int n) {
    for (int i = 0; i < n; i++) {
        if (S1[i].getRoll_no() == roll_no) {
            return i;
        }
    }
    return -1;
}

// Function to display all students
void displayStudents(Student S1[], int n) {
    for (int i = 0; i < n; i++) {
        S1[i].displayInfo();
    }
}

// Function to calculate total pending fees
int calculatePendingFees(Student S1[], int n) {
    int totalPending = 0;
    for (int i = 0; i < n; i++) {
        totalPending += S1[i].getPendingFees();
    }
    return totalPending;
}

int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Error: Could not open file.\n";
        return 1;
    }

    const int MAX_STUDENTS = 20;
    Student students[MAX_STUDENTS];
    string temp;
    int i = 0;

    // Read student data from file
    while (file >> temp) {
        int roll_no = stoi(temp);
        file >> temp; // Read name
        string name = temp;
        file >> temp; // Read PRN
        string prn = temp;
        file >> temp; // Read pending fees
        int pending = stoi(temp);

        // Create student object and store in array
        students[i++] = Student(roll_no, name, prn, pending);
    }

    int choice;
    do {
        cout << "\n1. Display all students\n2. Search by roll number\n3. Calculate Total Pending Fees\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayStudents(students, i);
                break;
            case 2: {
                int roll_no_to_search;
                cout << "Enter roll number to search: ";
                cin >> roll_no_to_search;

                int index = searchStudent(students, roll_no_to_search, i);

                if (index != -1) {
                    cout << "Student found:\n";
                    students[index].displayInfo();
                } else {
                    cout << "Student not found.\n";
                }
                break;
            }
            case 3:
                cout << "Total Pending Fees: " << calculatePendingFees(students, i) << "\n";
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please enter 1, 2, 3, or 4.\n";
                break;
        }
    } while (choice != 4);

    return 0;
}
