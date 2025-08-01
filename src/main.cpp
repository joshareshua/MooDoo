#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "Storage.h"
using namespace std;

void clearScreen() {
    cout << "\033[2J\033[1;1H"; // Clear screen
}

void showMenu() {
    cout << "\n=== MooDoo: Your Mood-Aware Planner ===" << endl;
    cout << "1. Add a new task" << endl;
    cout << "2. Add a mood entry" << endl;
    cout << "3. View all tasks" << endl;
    cout << "4. View mood history" << endl;
    cout << "5. Exit" << endl;
    cout << "Choose an option (1-5): ";
}

void addTask(Storage& storage) {
    clearScreen();
    cout << "=== Add New Task ===" << endl;
    
    Task task;
    task.id = storage.getNextTaskId();
    
    cout << "Task title: ";
    getline(cin, task.title);
    
    cout << "Description: ";
    getline(cin, task.description);
    
    cout << "Priority (1=Low, 2=Medium, 3=High): ";
    int priorityChoice;
    cin >> priorityChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    switch(priorityChoice) {
        case 1: task.priority = Priority::LOW; break;
        case 3: task.priority = Priority::HIGH; break;
        default: task.priority = Priority::MEDIUM; break;
    }
    
    if (storage.saveTask(task)) {
        cout << "✓ Task saved successfully!" << endl;
    } else {
        cout << "✗ Error saving task" << endl;
    }
}

void addMoodEntry(Storage& storage) {
    clearScreen();
    cout << "=== Add Mood Entry ===" << endl;
    
    MoodEntry entry;
    entry.id = storage.getNextMoodId();
    
    cout << "How are you feeling? ";
    getline(cin, entry.content);
    
    cout << "Mood level:" << endl;
    cout << "1. Very Low" << endl;
    cout << "2. Low" << endl;
    cout << "3. Neutral" << endl;
    cout << "4. Good" << endl;
    cout << "5. Excellent" << endl;
    cout << "Choose (1-5): ";
    
    int moodChoice;
    cin >> moodChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    switch(moodChoice) {
        case 1: entry.mood = MoodLevel::VERY_LOW; break;
        case 2: entry.mood = MoodLevel::LOW; break;
        case 4: entry.mood = MoodLevel::GOOD; break;
        case 5: entry.mood = MoodLevel::EXCELLENT; break;
        default: entry.mood = MoodLevel::NEUTRAL; break;
    }
    
    if (storage.saveMoodEntry(entry)) {
        cout << "✓ Mood entry saved successfully!" << endl;
    } else {
        cout << "✗ Error saving mood entry" << endl;
    }
}

void viewTasks(Storage& storage) {
    clearScreen();
    cout << "=== Your Tasks ===" << endl;
    
    vector<Task> tasks;
    if (storage.loadTasks(tasks)) {
        if (tasks.empty()) {
            cout << "No tasks found. Add some tasks to get started!" << endl;
        } else {
            for (const auto& task : tasks) {
                string priorityStr;
                switch(task.priority) {
                    case Priority::LOW: priorityStr = "Low"; break;
                    case Priority::HIGH: priorityStr = "High"; break;
                    default: priorityStr = "Medium"; break;
                }
                
                string status = task.completed ? "✓ Done" : "○ Pending";
                cout << "[" << task.id << "] " << status << " | " << priorityStr << " | " << task.title << endl;
                cout << "    " << task.description << endl << endl;
            }
        }
    } else {
        cout << "Error loading tasks" << endl;
    }
}

void viewMoodHistory(Storage& storage) {
    clearScreen();
    cout << "=== Mood History ===" << endl;
    
    vector<MoodEntry> entries;
    if (storage.loadMoodEntries(entries)) {
        if (entries.empty()) {
            cout << "No mood entries found. Add some entries to track your feelings!" << endl;
        } else {
            for (const auto& entry : entries) {
                string moodStr;
                switch(entry.mood) {
                    case MoodLevel::VERY_LOW: moodStr = "😞 Very Low"; break;
                    case MoodLevel::LOW: moodStr = "😔 Low"; break;
                    case MoodLevel::NEUTRAL: moodStr = "😐 Neutral"; break;
                    case MoodLevel::GOOD: moodStr = "😊 Good"; break;
                    case MoodLevel::EXCELLENT: moodStr = "😄 Excellent"; break;
                }
                
                cout << "[" << entry.id << "] " << moodStr << endl;
                cout << "    " << entry.content << endl << endl;
            }
        }
    } else {
        cout << "Error loading mood entries" << endl;
    }
}

int main() {
    Storage storage;
    int choice;
    
    cout << "Welcome to MooDoo: Your Mood-Aware Planner!" << endl;
    cout << "Let's start planning with your mood in mind." << endl;
    
    while (true) {
        showMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                addTask(storage);
                break;
            case 2:
                addMoodEntry(storage);
                break;
            case 3:
                viewTasks(storage);
                break;
            case 4:
                viewMoodHistory(storage);
                break;
            case 5:
                cout << "Thanks for using MooDoo! Take care of yourself! 💙" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        
        cout << "\nPress Enter to continue...";
        cin.get();
    }
    
    return 0;
}
