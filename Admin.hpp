#ifndef ADMIN_HPP
#define ADMIN_HPP

#include <iostream>
#include "Stack.hpp"   // Used to manage action history
using namespace std;

//Handles basic administrative operations.Generates system reports and manages action logs.
class AdminManager {
public:
    // Displays a summary report of the system
    void generateSystemReport(int students, int teachers, int courses) {
        cout << "\n===== SYSTEM REPORT =====\n";
        cout << "Total Students : " << students << endl;
        cout << "Total Teachers : " << teachers << endl;
        cout << "Total Courses  : " << courses << endl;
        cout << "=========================\n";
    }
    // Clears all recorded actions from the system stack
    void clearActionHistory(Stack& log) {
        log.clear();
        cout << "Action history cleared.\n";
    }
};

#endif
