#ifndef TEACHER_HPP
#define TEACHER_HPP

#include <iostream>
#include <string>
using namespace std;

//Represents a single teacher.Each teacher acts as a node in a linked list.
class Teacher {
public:
    string teacherID; //unique teacher ID
    string name;      // teacher name
    int assignedClasses;     //number of subjects assigned(max 4)
    Teacher* next; // pointer to next teacher in the list

    // Constructor to initialize a teacher node
    Teacher(string id, string n) {
        teacherID = id;
        name = n;
        assignedClasses = 0;
        next = NULL;
    }
};

// TEACHER Manager to manage all Teacher using a linked list. Handles adding, searching, sorting, and displaying students.
class TeacherManager {
private:
    Teacher* head; // points to first teacher in the list
    int idCounter; // used to generate unique teacher IDs

    // Generates a teacher ID in the format T-001
    string generateTeacherID() {
        idCounter++;
        string num = to_string(idCounter);
        while (num.length() < 3)
            num = "0" + num;
        return "T-" + num;
    }

public:
    // Constructor initializes empty teacher list
    TeacherManager() {
        head = NULL;
        idCounter = 0;
    }

    // Adds a new teacher to the linked list
    void addTeacher(string name) {
        string id = generateTeacherID();
        Teacher* t = new Teacher(id, name);

        if (head == NULL) {
            head = t;
        }
        else {
            Teacher* cur = head;
            while (cur->next != NULL)
                cur = cur->next;
            cur->next = t;
        }

        cout << "Teacher added. ID: " << id << endl;
    }

    // Searches for a teacher by ID using sequential search
    Teacher* searchTeacher(string id) {
        Teacher* t = head;
        while (t != NULL) {
            if (t->teacherID == id)
                return t;
            t = t->next;
        }
        return NULL;
    }

    // Assigns a class to a teacher (maximum 4 classes allowed)
    void assignClass(string id) {
        Teacher* t = searchTeacher(id);
        if (t == NULL) {
            cout << "Teacher not found.\n";
            return;
        }

        if (t->assignedClasses >= 4) {
            cout << "Maximum workload reached.\n";
            return;
        }

        t->assignedClasses++;
    }

    // Displays only teachers who can still take more classes
    void displayAvailableTeachers() {
        Teacher* t = head;
        bool found = false;

        cout << "\nAvailable Teachers:\n";
        while (t != NULL) {
            if (t->assignedClasses < 4) {
                cout << "ID: " << t->teacherID
                    << " | Name: " << t->name
                    << " | Workload: " << t->assignedClasses << "/4\n";
                found = true;
            }
            t = t->next;
        }

        if (!found)
            cout << "No teachers available.\n";
    }

    //Displays a performance report for a teacher based on their current workload.
    void trackTeacherPerformance(string teacherID) {
        Teacher* t = searchTeacher(teacherID);
        if (t == NULL) {
            cout << "Teacher not found.\n";
            return;
        }

        cout << "\n[Teacher Performance Report]\n";
        cout << "Teacher ID   : " << t->teacherID << endl;
        cout << "Name         : " << t->name << endl;
        cout << "Workload     : " << t->assignedClasses << " / 4 subjects\n";

        if (t->assignedClasses <= 2)
            cout << "Performance  : Light workload\n";
        else if (t->assignedClasses == 3)
            cout << "Performance  : Normal workload\n";
        else
            cout << "Performance  : Heavy workload\n";
    }
    // Edits an existing teacher name using teacher ID
    void editTeacher(string teacherID, string newName) {
        Teacher* t = searchTeacher(teacherID);

        if (t == NULL) {
            cout << "Teacher not found.\n";
            return;
        }

        t->name = newName;
        cout << "Teacher updated successfully.\n";
    }
    // Deletes a teacher from the linked list using teacher ID
    void deleteTeacher(string teacherID) {
        if (head == NULL) {
            cout << "No teachers to delete.\n";
            return;
        }

        // If first teacher is the one to delete
        if (head->teacherID == teacherID) {
            Teacher* temp = head;
            head = head->next;
            delete temp;
            cout << "Teacher deleted successfully.\n";
            return;
        }

        Teacher* prev = head;
        Teacher* curr = head->next;

        while (curr != NULL) {
            if (curr->teacherID == teacherID) {
                prev->next = curr->next;
                delete curr;
                cout << "Teacher deleted successfully.\n";
                return;
            }
            prev = curr;
            curr = curr->next;
        }

        cout << "Teacher not found.\n";
    }


    // Returns the total number of teachers in the system
    int getTeacherCount() {
        int count = 0;
        Teacher* t = head;
        while (t != NULL) {
            count++;
            t = t->next;
        }
        return count;
    }

};

#endif
