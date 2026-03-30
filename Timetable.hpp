#ifndef TIMETABLE_HPP
#define TIMETABLE_HPP

#include <iostream>
#include <string>
using namespace std;

//Represents a single timetable entry.Each entry stores scheduling information for one course.

class Timetable {
public:
    int courseID;         // course being scheduled
    string teacherID;    // teacher assigned to the course
    string day;         // day of the week (Monday–Friday)
    string timeSlot;   // time slot (08:00–16:00)
    int roomID;       // classroom number
    Timetable* next; // pointer to next timetable entry

    // Constructor to initialize a timetable node
    Timetable(int cID, string tID, string d, string t, int rID) {
        courseID = cID;
        teacherID = tID;
        day = d;
        timeSlot = t;
        roomID = rID;
        next = NULL;
    }
};

//Manages the weekly timetable using a linked list.Handles scheduling, clash detection, and display.
class TimetableManager {
private:
    Timetable* head; // points to first timetable entry

public:
    // Constructor initializes empty timetable
    TimetableManager() {
        head = NULL;
    }
    //Checks if a teacher already has a class on the same day and time slot.
    bool checkClash(string teacherID, string day, string timeSlot) {
        Timetable* t = head;
        while (t != NULL) {
            if (t->teacherID == teacherID &&
                t->day == day &&
                t->timeSlot == timeSlot)
                return true;
            t = t->next;
        }
        return false;
    }
    //Adds a course to the timetable if no clash exists.Each course is scheduled with a teacher, day, time, and room
    void addToTimetable(int courseID,
        string teacherID,
        string day,
        string timeSlot,
        int roomID) {
        if (checkClash(teacherID, day, timeSlot)) {
            cout << "Clash detected: Teacher already has a class at this time.\n";
            return;
        }

        Timetable* entry = new Timetable(courseID, teacherID, day, timeSlot, roomID);

        if (head == NULL) {
            head = entry;
        }
        else {
            Timetable* t = head;
            while (t->next != NULL)
                t = t->next;
            t->next = entry;
        }

        cout << "Course scheduled successfully.\n";
    }
    // Displays all timetable entries for the week
    void displayTimetable() {
        if (head == NULL) {
            cout << "No timetable entries available.\n";
            return;
        }

        cout << "\n===== WEEKLY TIMETABLE =====\n";
        Timetable* t = head;
        while (t != NULL) {
            cout << "Course ID : " << t->courseID << endl;
            cout << "Teacher   : " << t->teacherID << endl;
            cout << "Day       : " << t->day << endl;
            cout << "Time Slot : " << t->timeSlot << endl;
            cout << "Room ID   : " << t->roomID << endl;
            cout << "----------------------------\n";
            t = t->next;
        }
    }
    // Updates the classroom for a scheduled course
    void updateRoom(int courseID, int roomID) {
        Timetable* t = head;
        while (t != NULL) {
            if (t->courseID == courseID) {
                t->roomID = roomID;
                cout << "Room updated successfully.\n";
                return;
            }
            t = t->next;
        }
        cout << "Course not found in timetable.\n";
    }
};

#endif
