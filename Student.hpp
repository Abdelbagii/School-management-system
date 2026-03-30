#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <iostream>
#include <string>
using namespace std;



class Student {
public:
    string studentID;   // unique student ID
    string name;        // student name
    string level;       // student level
    Student* next;      // pointer to next student

    // Constructor to initialize a student node
    Student(string id, string n, string l) {
        studentID = id;
        name = n;
        level = l;
        next = NULL;
    }
};


  // Student Manager to manage all students using a linked list. Handles adding, searching, sorting, and displaying students.

class StudentManager {
private:
    Student* head;      // points to first student in the list
    long idCounter;     // used to generate unique student IDs

    // Returns numeric order of levels for sorting
    int levelOrder(string level) {
        if (level == "Freshman") return 1;
        if (level == "Sophomore") return 2;
        if (level == "Junior") return 3;
        if (level == "Senior") return 4;
        return 0;
    }

    // Generates a unique student ID (e.g. 2026000001)
    string generateStudentID() {
        idCounter++;
        string num = to_string(idCounter);
        while (num.length() < 6)
            num = "0" + num;
        return "2026" + num;
    }

public:
    // Constructor initializes empty list
    StudentManager() {
        head = NULL;
        idCounter = 0;
    }

    // Adds a new student to the linked list
    void addStudent(string name, string level) {
        string id = generateStudentID();
        Student* s = new Student(id, name, level);

        if (head == NULL) {
            head = s;
        }
        else {
            Student* t = head;
            while (t->next != NULL)
                t = t->next;
            t->next = s;
        }

        cout << "Student added. ID: " << id << endl;
    }

    // Sequential search to find a student by ID
    Student* searchStudent(string id) {
        Student* t = head;
        while (t != NULL) {
            if (t->studentID == id)
                return t;
            t = t->next;
        }
        return NULL;
    }

    // Displays all students in the system
    void displayStudents() {
        if (head == NULL) {
            cout << "No students available.\n";
            return;
        }

        Student* t = head;
        while (t != NULL) {
            cout << "ID: " << t->studentID
                << " | Name: " << t->name
                << " | Level: " << t->level << endl;
            t = t->next;
        }
    }

    //Sorts students by student level using bubble sort.Sorting is done by swapping data inside nodes.
    
    void bubbleSortStudents() {
        if (head == NULL || head->next == NULL)
            return;

        bool swapped;
        Student* ptr1;
        Student* lptr = NULL;

        do {
            swapped = false;
            ptr1 = head;

            while (ptr1->next != lptr) {
                if (levelOrder(ptr1->level) > levelOrder(ptr1->next->level)) {

                    string tempID = ptr1->studentID;
                    ptr1->studentID = ptr1->next->studentID;
                    ptr1->next->studentID = tempID;

                    string tempName = ptr1->name;
                    ptr1->name = ptr1->next->name;
                    ptr1->next->name = tempName;

                    string tempLevel = ptr1->level;
                    ptr1->level = ptr1->next->level;
                    ptr1->next->level = tempLevel;

                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);

        cout << "Students sorted by level.\n";
    }

    // Displays a simple progress report for a student
    void viewProgressReport(string studentID) {
        Student* s = searchStudent(studentID);
        if (s == NULL) {
            cout << "Student not found.\n";
            return;
        }

        cout << "\n[Progress Report]\n";
        cout << "Student ID: " << s->studentID << endl;
        cout << "Name      : " << s->name << endl;
        cout << "Level     : " << s->level << endl;
        cout << "Progress  : undergraduate\n";
    }

    // Displays enrollment history for a student
    void trackEnrollmentHistory(string studentID) {
        Student* s = searchStudent(studentID);
        if (s == NULL) {
            cout << "Student not found.\n";
            return;
        }

        cout << "\n[Enrollment History]\n";
        cout << "Student ID: " << s->studentID << endl;
        cout << "• Enrolled in courses successfully\n";
        cout << "• No drops recorded\n";
    }

    // Automatically schedules a parent meeting
    void autoScheduleMeeting(string studentID) {
        Student* s = searchStudent(studentID);
        if (s == NULL) {
            cout << "Student not found.\n";
            return;
        }

        cout << "\n[Parent Meeting]\n";
        cout << "Meeting scheduled automatically for student "
            << s->studentID << endl;
        cout << "Status: Pending confirmation\n";
    }
    // Edits an existing student's name and level using student ID
    void editStudent(string studentID, string newName, string newLevel) {
        Student* s = searchStudent(studentID);

        if (s == NULL) {
            cout << "Student not found.\n";
            return;
        }

        s->name = newName;
        s->level = newLevel;

        cout << "Student updated successfully.\n";
    }
    // Deletes a student from the linked list using student ID
    void deleteStudent(string studentID) {
        if (head == NULL) {
            cout << "No students to delete.\n";
            return;
        }

        // If the student to delete is the first node
        if (head->studentID == studentID) {
            Student* temp = head;
            head = head->next;
            delete temp;
            cout << "Student deleted successfully.\n";
            return;
        }

        // Search for the student in the list
        Student* prev = head;
        Student* curr = head->next;

        while (curr != NULL) {
            if (curr->studentID == studentID) {
                prev->next = curr->next;
                delete curr;
                cout << "Student deleted successfully.\n";
                return;
            }
            prev = curr;
            curr = curr->next;
        }

        cout << "Student not found.\n";
    }


    // Returns total number of students (used for system reports)
    int getStudentCount() {
        int count = 0;
        Student* t = head;
        while (t != NULL) {
            count++;
            t = t->next;
        }
        return count;
    }
};

#endif
