#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <string>
using namespace std;

// Represents a single node in the stack. Each node stores one action.
class StackNode {
public:
    string action;        // description of the action performed
    StackNode* next; // pointer to the next node in the stack

    // Constructor to initialize a stack node
    StackNode(string act) {
        action = act;
        next = NULL;
    }
};

// Stack ADT implemented using a linked list.Stores system actions using LIFO principle.
class Stack {
private:
    StackNode* top; // pointer to the top of the stack
    int count;  // number of elements in the stack

public:
    // Constructor initializes empty stack
    Stack() {
        top = NULL;
        count = 0;
    }

    // Pushes a new action onto the stack
    void push(string action) {
        StackNode* newNode = new StackNode(action);
        newNode->next = top;
        top = newNode;
        count++;
    }

    // Removes and returns the most recent action
    string pop() {
        if (isEmpty()) {
            cout << "Stack is empty.\n";
            return "";
        }

        StackNode* temp = top;
        string lastAction = temp->action;
        top = top->next;
        delete temp;
        count--;
        return lastAction;
    }

    // Returns the most recent action without removing it
    string peek() {
        if (isEmpty()) {
            cout << "Stack is empty.\n";
            return "";
        }
        return top->action;
    }

    // Checks whether the stack is empty
    bool isEmpty() {
        return top == NULL;
    }

    // Returns the number of actions stored
    int size() {
        return count;
    }

    // Displays all actions from latest to oldest
    void displayStack() {
        if (isEmpty()) {
            cout << "No actions recorded.\n";
            return;
        }

        cout << "Action History (Latest First):\n";
        StackNode* temp = top;
        while (temp != NULL) {
            cout << "- " << temp->action << endl;
            temp = temp->next;
        }
    }

    //Clear all actions 
    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
};

#endif
