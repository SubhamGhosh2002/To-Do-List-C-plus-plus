#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

struct Task {
    string name;
    bool completed;
    time_t dueTime;
};

// Function to display the to-do list
void displayToDoList(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "Your to-do list is empty." << endl;
    } else {
        cout << "To-Do List:" << endl;
        for (int i = 0; i < tasks.size(); i++) {
            cout << i + 1 << ". ";
            if (tasks[i].completed) {
                cout << "[Completed] ";
            }

            // Use strftime to format the time
            char timeStr[80];
            struct tm* timeinfo = localtime(&tasks[i].dueTime);
            strftime(timeStr, sizeof(timeStr), "%H:%M", timeinfo);

            cout << tasks[i].name << " (Due: " << timeStr << ")" << endl;
        }
    }
}

// Function to parse time input (HH:MM)
time_t parseTime(const string& timeString) {
    struct tm timeinfo = {};
    if (sscanf(timeString.c_str(), "%d:%d", &timeinfo.tm_hour, &timeinfo.tm_min) == 2) {
        // Set default date (January 1, 1970)
        timeinfo.tm_year = 70;  // Years since 1900
        timeinfo.tm_mon = 0;   // Month (0-11)
        timeinfo.tm_mday = 1;  // Day of the month (1-31)

        // Use mktime to convert to a time_t value
        return mktime(&timeinfo);
    }
    return -1; // Invalid input
}

int main() {
    vector<Task> tasks; // Vector of tasks (including name, completion status, and due time)
    char choice;

    cout << "Welcome to the To-Do List Application!" << endl;

    do {
        cout << "\nChoose an option:" << endl;
        cout << "1. Add a task" << endl;
        cout << "2. Remove a task" << endl;
        cout << "3. Mark a task as completed" << endl;
        cout << "4. Clear all tasks" << endl;
        cout << "5. Display tasks" << endl;
        cout << "6. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1': {
                Task task;
                cout << "Enter the task: ";
                cin.ignore();
                getline(cin, task.name);
                cout << "Enter the due time (HH:MM): ";
                string timeString;
                getline(cin, timeString);
                task.dueTime = parseTime(timeString);
                if (task.dueTime != -1) {
                    task.completed = false;
                    tasks.push_back(task);
                    cout << "Task added to the list." << endl;
                } else {
                    cout << "Invalid time format. Task not added." << endl;
                }
                break;
            }
            case '2': {
                int taskIndex;
                displayToDoList(tasks);
                cout << "Enter the task number to remove: ";
                cin >> taskIndex;
                if (taskIndex >= 1 && taskIndex <= tasks.size()) {
                    tasks.erase(tasks.begin() + taskIndex - 1);
                    cout << "Task removed from the list." << endl;
                } else {
                    cout << "Invalid task number." << endl;
                }
                break;
            }
            case '3': {
                int taskIndex;
                displayToDoList(tasks);
                cout << "Enter the task number to mark as completed: ";
                cin >> taskIndex;
                if (taskIndex >= 1 && taskIndex <= tasks.size()) {
                    tasks[taskIndex - 1].completed = true;
                    cout << "Task marked as completed." << endl;
                } else {
                    cout << "Invalid task number." << endl;
                }
                break;
            }
            case '4':
                tasks.clear();
                cout << "All tasks cleared." << endl;
                break;
            case '5':
                displayToDoList(tasks);
                break;
            case '6':
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != '6');

    return 0;
}
