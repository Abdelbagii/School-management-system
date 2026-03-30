#ifndef COURSE_HPP
#define COURSE_HPP

#include <iostream>
#include <string>
using namespace std;
//Represents a student enrolled in a course.Each node stores one student ID.
class EnrolledStudent {
public:
    string studentID;// ID of enrolled student
    EnrolledStudent* next;// pointer to next enrolled student

    // Constructor to initialize enrolled student node
    EnrolledStudent(string id) {
        studentID = id;
        next = NULL;
    }
};
// course class.
class Course {
public:
    int courseID;// unique course ID
    string courseName;// course name
    string teacherID; // assigned teacher ID
    EnrolledStudent* studentHead; // list of enrolled students
    int studentCount;  // number of enrolled students
    Course* next;     // pointer to next course

    // Constructor to initialize course
    Course(int id, string name) {
        courseID = id;
        courseName = name;
        teacherID = "";
        studentHead = NULL;
        studentCount = 0;
        next = NULL;
    }
};
// Course Manager to manage all course using a linked list.Handles course creation, enrollment, and teacher assignment.

class CourseManager {
private:
    Course* head; // points to the first course in the list

public:
    // Constructor initializes empty course list

    CourseManager() {
        head = NULL;
    }

    // Searches for a course by ID using sequential search
    Course* searchCourse(int id) {
        Course* c = head;
        while (c) {
            if (c->courseID == id) return c;
            c = c->next;
        }
        return NULL;
    }
    // Adds a new course to the linked list
    void addCourse(int id, string name) {
        Course* c = new Course(id, name);
        if (!head) head = c;
        else {
            Course* t = head;
            while (t->next) t = t->next;
            t->next = c;
        }
    }
    // Displays all courses 
    void displayCourses() {
        if (head == NULL) {
            cout << "No courses available.\n";
            return;
        }

        Course* c = head;
        cout << "\n[Course List]\n";
        while (c != NULL) {
            cout << "Course ID   : " << c->courseID << endl;
            cout << "Course Name : " << c->courseName << endl;

            if (c->teacherID == "")
                cout << "Teacher     : Not assigned\n";
            else
                cout << "Teacher     : " << c->teacherID << endl;

            cout << "Students    : " << c->studentCount << "/100\n";
            cout << "-----------------------------\n";

            c = c->next;
        }
    }

    // Assigns a teacher to a course
    void assignTeacher(int courseID, string teacherID) {
        Course* c = searchCourse(courseID);
        if (!c) {
            cout << "Course not found.\n";
            return;
        }
        c->teacherID = teacherID;
    }
    // Enrolls a student into a course (max 100 students)
    void enrollStudent(int courseID, string studentID) {
        Course* c = searchCourse(courseID);
        if (!c) return;

        if (c->studentCount >= 100) {
            cout << "Course full.\n";
            return;
        }

        EnrolledStudent* s = new EnrolledStudent(studentID);
        if (!c->studentHead) c->studentHead = s;
        else {
            EnrolledStudent* t = c->studentHead;
            while (t->next) t = t->next;
            t->next = s;
        }

        c->studentCount++;
    }
    // Returns total number of courses in the system
    int getCourseCount() {
        int count = 0;
        Course* c = head;
        while (c != NULL) {
            count++;
            c = c->next;
        }
        return count;
    }
    // Edits an existing course name using course ID
    void editCourse(int courseID, string newName) {
        Course* c = searchCourse(courseID);

        if (c == NULL) {
            cout << "Course not found.\n";
            return;
        }

        c->courseName = newName;
        cout << "Course updated successfully.\n";
    }
    // Deletes a course from the linked list using course ID
    void deleteCourse(int courseID) {
        if (head == NULL) {
            cout << "No courses to delete.\n";
            return;
        }

        // If first course is the one to delete
        if (head->courseID == courseID) {
            Course* temp = head;
            head = head->next;
            delete temp;
            cout << "Course deleted successfully.\n";
            return;
        }

        Course* prev = head;
        Course* curr = head->next;

        while (curr != NULL) {
            if (curr->courseID == courseID) {
                prev->next = curr->next;
                delete curr;
                cout << "Course deleted successfully.\n";
                return;
            }
            prev = curr;
            curr = curr->next;
        }

        cout << "Course not found.\n";
    }

    // Returns the teacher assigned to a course
    string getTeacherForCourse(int courseID) {
        Course* c = searchCourse(courseID);
        if (c == NULL) return "";
        return c->teacherID;
    }

};

#endif
