#include <iostream>
#include "Student.hpp"
#include "Teacher.hpp"
#include "Course.hpp"
#include "Admin.hpp"
#include "Timetable.hpp"
#include "Stack.hpp"
using namespace std;

//CONSOLE COLOR DEFINITIONS
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

// Checks if a name contains only letters and spaces
bool isValidName(const string& name) {
    if (name.empty()) return false;

    for (char c : name) {
        if (!isalpha(c) && c != ' ')
            return false;
    }
    return true;
}
// STUDENT MENU. 
void studentMenu(StudentManager& sm, Stack& log) {
    int choice;
    do {
        cout << BOLD << CYAN << "\nSTUDENT MANAGEMENT " << RESET << endl;
        cout << "1. Add Student\n";
        cout << "2. View Progress Report\n";
        cout << "3. Track Enrollment History\n";
        cout << "4. Schedule Parent Meeting\n";
        cout << "5. Display All Students\n";
        cout << "6. Sort Students by Level\n";
        cout << YELLOW << "7. EDIT STUDENT.\n" << RESET;
        cout << RED << "8. DELETE STUDENT.\n" << RESET;
        cout << RED << "0. Back\n" << RESET;
        cout << "Enter option: ";
        cin >> choice;

        //Add new student
        if (choice == 1) {
            string name;
            int lvl;
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);

            if (!isValidName(name)) {
                cout << RED << "Invalid name. Use letters only.\n" << RESET;
                continue;
            }


            cout << "Select Level:\n";
            cout << "1. Freshman\n2. Sophomore\n3. Junior\n4. Senior\n";
            cout << "Choice: ";
            cin >> lvl;

            string level;
            if (lvl == 1) level = "Freshman";
            else if (lvl == 2) level = "Sophomore";
            else if (lvl == 3) level = "Junior";
            else if (lvl == 4) level = "Senior";
            else {
                cout << RED << "Invalid level.\n" << RESET;
                continue;
            }

            sm.addStudent(name, level);
            log.push("ADD_STUDENT: " + name);
        }
        //view student progress report
        else if (choice == 2) {
            string id;
            cout << "Enter Student ID: ";
            cin >> id;
            sm.viewProgressReport(id);
        }
        //Track enrollment history
        else if (choice == 3) {
            string id;
            cout << "Enter Student ID: ";
            cin >> id;
            sm.trackEnrollmentHistory(id);
        }
        //Schedule parent meeting
        else if (choice == 4) {
            string id;
            cout << "Enter Student ID: ";
            cin >> id;
            sm.autoScheduleMeeting(id);
        }
        //Display all students
        else if (choice == 5) {
            sm.displayStudents();
        }
        //Sort students by level
        else if (choice == 6) {
            sm.bubbleSortStudents();
            sm.displayStudents();

        } 
        // Edit student
        else if (choice == 7) {
            string id, name, level;
            int lvl;

            cout << "Enter Student ID: ";
            cin >> id;
            cin.ignore();

            cout << "Enter New Name: ";
            getline(cin, name);

            if (!isValidName(name)) {
                cout << RED << "Invalid name. Use letters only.\n" << RESET;
                continue;
            }


            cout << "Select New Level:\n";
            cout << "1. Freshman\n2. Sophomore\n3. Junior\n4. Senior\n";
            cout << "Choice: ";
            cin >> lvl;

            if (lvl == 1) level = "Freshman";
            else if (lvl == 2) level = "Sophomore";
            else if (lvl == 3) level = "Junior";
            else if (lvl == 4) level = "Senior";
            else {
                cout << RED << "Invalid level.\n" << RESET;
                return;
            }

            sm.editStudent(id, name, level);
            log.push("EDIT_STUDENT: " + id);
        }

        //DELETE STUDENT BY USING level
        else if (choice == 8) {
            string id;
            cout << "Enter Student ID: ";
            cin >> id;
            sm.deleteStudent(id);
            log.push("DELETE_STUDENT: " + id);
        }
        else if (choice != 0) {
            cout << RED << "Invalid option. Please select a valid menu number.\n" << RESET;
        }

    } while (choice != 0);
}

// TEACHER MENU 
void teacherMenu(TeacherManager& tm, Stack& log) {
    int choice;
    do {
        cout << BOLD << CYAN << "\nTEACHER MANAGEMENT " << RESET << endl;
        cout << "1. Add Teacher\n";
        cout << "2. View Teacher Performance\n";
        cout << "3. View Available Teachers\n";
        cout << YELLOW << "4. EDIT Teacher\n" << RESET;
        cout << RED << "5. DELETE Teacher\n" << RESET;
        cout << RED << "0. Back\n" << RESET;
        cout << "Enter option: ";
        cin >> choice;
        //Add new teacher
        if (choice == 1) {
            string name;
            cout << "Enter Teacher Name: ";
            cin.ignore();
            getline(cin, name);

            if (!isValidName(name)) {
                cout << RED << "Invalid name. Use letters only.\n" << RESET;
                continue;
            }

            tm.addTeacher(name);
            log.push("ADD_TEACHER: " + name);
        }
        //View teacher performance
        else if (choice == 2) {
            string id;
            cout << "Enter Teacher ID: ";
            cin >> id;
            tm.trackTeacherPerformance(id);
        }
        //Display available teachers
        else if (choice == 3) {
            tm.displayAvailableTeachers();
        }
        //EDIT  Teachers
        else if (choice == 4) {
            string id, name;
            cout << "Enter Teacher ID: ";
            cin >> id;
            cin.ignore();

            cout << "Enter Teacher Name: ";
            cin.ignore();
            getline(cin, name);

            if (!isValidName(name)) {
                cout << RED << "Invalid name. Use letters only.\n" << RESET;
                continue;
            }


            tm.editTeacher(id, name);
            log.push("EDIT_TEACHER: " + id);
        }
        //DELETE Teacher
        else if (choice == 5) {
            string id;
            cout << "Enter Teacher ID: ";
            cin >> id;

            tm.deleteTeacher(id);
            log.push("DELETE_TEACHER: " + id);
        }

        else if (choice != 0) {
            cout << RED << "Invalid option. Please select a valid menu number.\n" << RESET;
        }
    } while (choice != 0);
}

//COURSE MENU 
void courseMenu(CourseManager& cm, TeacherManager& tm, Stack& log) {
    int choice;
    do {
        cout << BOLD << CYAN << "\nCOURSE MANAGEMENT" << RESET << endl;
        cout << "1. Add Course\n";
        cout << "2. Assign Teacher to Course\n";
        cout << "3. Enroll Student in Course\n";
        cout << "4. View Available Course\n";
        cout << YELLOW << "5. EDIT COURSE\n" << RESET;
        cout << RED << "6. DELETE COURSE\n" << RESET;
        cout << RED << "0. Back\n" << RESET;
        cout << "Enter option: ";
        cin >> choice;
        //Add new course
        if (choice == 1) {
            int id;
            string name;
            cout << "Enter Course ID: ";
            cin >> id;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << RED << "Invalid Course ID. Numbers only.\n" << RESET;
                continue;
            }

            cout << "Enter Course Name: ";
            cin.ignore();
            getline(cin, name);

            if (!isValidName(name)) {
                cout << RED << "Invalid name. Use letters only.\n" << RESET;
                continue;
            }

            cm.addCourse(id, name);
            log.push("ADD_COURSE: " + name);
        }
        //Assign teacher to a course 
        else if (choice == 2) {
            int cid;
            string tid;
            cout << "Enter Course ID: ";
            cin >> cid;
            tm.displayAvailableTeachers();
            cout << "Enter Teacher ID: ";
            cin >> tid;
            cm.assignTeacher(cid, tid);
            tm.assignClass(tid);
            log.push("ASSIGN_TEACHER: " + tid + " TO COURSE " + to_string(cid));
        }
      //Enroll student in course
        else if (choice == 3) {
            int cid;
            string sid;
            cout << "Enter Course ID: ";
            cin >> cid;
            cout << "Enter Student ID: ";
            cin >> sid;
            cm.enrollStudent(cid, sid);
            log.push("ENROLL_STUDENT: " + sid + " IN COURSE " + to_string(cid));
        }
        // Display all courses
        else if (choice == 4) {
            cm.displayCourses();
        }

        // Edit course
        else if (choice == 5) {
            int id;
            string name;

            cout << "Enter Course ID: ";
            cin >> id;
            cin.ignore();

           
            cout << "Enter Course Name: ";
            cin.ignore();
            getline(cin, name);

            if (!isValidName(name)) {
                cout << RED << "Invalid name. Use letters only.\n" << RESET;
                continue;
            }

            cm.editCourse(id, name);
            log.push("EDIT_COURSE: " + to_string(id));
        }
        // Delete course
        else if (choice == 6) {
            int id;
            cout << "Enter Course ID: ";
            cin >> id;

            cm.deleteCourse(id);
            log.push("DELETE_COURSE: " + to_string(id));
        }

        else if (choice != 0) {
            cout << RED << "Invalid option. Please select a valid menu number.\n" << RESET;
        }
    } while (choice != 0);
}

//ADMIN MENU 
void adminMenu(AdminManager& am,
    StudentManager& sm,
    TeacherManager& tm,
    CourseManager& cm,
    Stack& log) {
    int choice;
    do {
        cout << BOLD << CYAN << "\nADMIN MANAGEMENT " << RESET << endl;
        cout << "1. Generate System Report\n";
        cout << "2. Clear Action History\n";
        cout << RED << "0. Back\n" << RESET;
        cout << "Enter option: ";
        cin >> choice;
       //Generate school report
        if (choice == 1) {
            am.generateSystemReport(
                sm.getStudentCount(),
                tm.getTeacherCount(),
                cm.getCourseCount()
            );
        } 
        //Clear action history
        else if (choice == 2) {
            am.clearActionHistory(log);
        }
        else if (choice != 0) {
            cout << RED << "Invalid option. Please select a valid menu number.\n" << RESET;
        }

    } while (choice != 0);
}

//TIMETABLE MENU 
void timetableMenu(TimetableManager& tt, CourseManager& cm) {
    int choice;
    do {
        cout << BOLD << CYAN << "\nTIMETABLE MANAGEMENT " << RESET << endl;
        cout << "1. Add Course to Timetable\n";
        cout << "2. Display Weekly Timetable\n";
        cout << "3. Update Classroom\n";
        cout << RED << "0. Back\n" << RESET;
        cout << "Enter option: ";
        cin >> choice;
        //Schedule a course
        if (choice == 1) {
            int courseID, roomID, dayChoice, timeChoice;
            string day, timeSlot;

            cout << "Enter Course ID: ";
            cin >> courseID;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << RED << "Invalid Course ID. Numbers only.\n" << RESET;
                continue;
            }


            string teacherID = cm.getTeacherForCourse(courseID);
            if (teacherID == "") {
                cout << RED << "Assign a teacher to the course first.\n" << RESET;
                continue;
            }

            cout << "Assigned Teacher: " << teacherID << endl;

            cout << "Select Day:\n";
            cout << "1. Monday\n2. Tuesday\n3. Wednesday\n4. Thursday\n5. Friday\n";
            cout << "Choice: ";
            cin >> dayChoice;

            if (dayChoice == 1) day = "Monday";
            else if (dayChoice == 2) day = "Tuesday";
            else if (dayChoice == 3) day = "Wednesday";
            else if (dayChoice == 4) day = "Thursday";
            else if (dayChoice == 5) day = "Friday";
            else {
                cout << RED << "Invalid day.\n" << RESET;
                continue;
            }

            cout << "Select Time Slot:\n";
            cout << "1. 08:00 - 10:00\n";
            cout << "2. 10:00 - 12:00\n";
            cout << "3. 12:00 - 14:00\n";
            cout << "4. 14:00 - 16:00\n";
            cout << "Choice: ";
            cin >> timeChoice;

            if (timeChoice == 1) timeSlot = "08:00 - 10:00";
            else if (timeChoice == 2) timeSlot = "10:00 - 12:00";
            else if (timeChoice == 3) timeSlot = "12:00 - 14:00";
            else if (timeChoice == 4) timeSlot = "14:00 - 16:00";
            else {
                cout << RED << "Invalid time slot.\n" << RESET;
                continue;
            }

            cout << "Enter Room ID: ";
            cin >> roomID;

            tt.addToTimetable(courseID, teacherID, day, timeSlot, roomID);
        }
        //Display weekly timetable
        else if (choice == 2) {
            tt.displayTimetable();
        }
        //Update classroom
        else if (choice == 3) {
            int cid, rid;
            cout << "Enter Course ID: ";
            cin >> cid;
            cout << "Enter New Room ID: ";
            cin >> rid;
            tt.updateRoom(cid, rid);
        }
        else if (choice != 0) {
            cout << RED << "Invalid option. Please select a valid menu number.\n" << RESET;
        }

    } while (choice != 0);
}

//MAIN FUNCTION 
int main() {
    StudentManager sm;
    TeacherManager tm;
    CourseManager cm;
    AdminManager am;
    TimetableManager ttm;
    Stack actionLog;

    int choice;
    do {
        cout << BOLD << BLUE << "\n MAIN MENU " << RESET << endl;
        cout << "1. Student Management\n";
        cout << "2. Teacher Management\n";
        cout << "3. Course Management\n";
        cout << "4. Admin Management\n";
        cout << "5. Timetable Management\n";
        cout << "6. View Action History\n";
        cout << RED << "0. Exit\n" << RESET;
        cout << "Enter option: ";
        cin >> choice;

        if (choice == 1) studentMenu(sm, actionLog);
        else if (choice == 2) teacherMenu(tm, actionLog);
        else if (choice == 3) courseMenu(cm, tm, actionLog);
        else if (choice == 4) adminMenu(am, sm, tm, cm, actionLog);
        else if (choice == 5) timetableMenu(ttm, cm);
        else if (choice == 6) actionLog.displayStack();
        else if (choice != 0) { 
            cout << RED << "Invalid option. Please select a valid menu number.\n" << RESET;
        }

    } while (choice != 0);

    cout << GREEN << "System closed successfully.\n" << RESET;
    return 0;
}
