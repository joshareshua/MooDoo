#include <iostream>
#include <vector>
#include "Storage.h"
using namespace std;

int main() {
    cout << "Welcome to MooDoo: Your Mood-Aware Planner!" << endl;
    
    // Test the Storage system
    Storage storage;
    
    // Test task storage
    cout << "\n=== Testing Task Storage ===" << endl;
    
    Task task1;
    task1.id = storage.getNextTaskId();
    task1.title = "Complete project proposal";
    task1.description = "Write the initial draft for the new feature";
    task1.priority = Priority::HIGH;
    
    Task task2;
    task2.id = storage.getNextTaskId();
    task2.title = "Buy groceries";
    task2.description = "Milk, bread, eggs, and vegetables";
    task2.priority = Priority::LOW;
    
    if (storage.saveTask(task1)) {
        cout << "✓ Saved task: " << task1.title << endl;
    }
    
    if (storage.saveTask(task2)) {
        cout << "✓ Saved task: " << task2.title << endl;
    }
    
    // Test loading tasks
    vector<Task> loadedTasks;
    if (storage.loadTasks(loadedTasks)) {
        cout << "✓ Loaded " << loadedTasks.size() << " tasks" << endl;
        for (const auto& task : loadedTasks) {
            cout << "  - " << task.title << " (Priority: " << (int)task.priority << ")" << endl;
        }
    }
    
    // Test mood entry storage
    cout << "\n=== Testing Mood Entry Storage ===" << endl;
    
    MoodEntry entry1;
    entry1.id = storage.getNextMoodId();
    entry1.content = "Feeling overwhelmed today, lots of deadlines";
    entry1.mood = MoodLevel::LOW;
    entry1.keywords = {"overwhelmed", "deadlines", "stress"};
    
    MoodEntry entry2;
    entry2.id = storage.getNextMoodId();
    entry2.content = "Had a great morning workout, feeling energized!";
    entry2.mood = MoodLevel::GOOD;
    entry2.keywords = {"workout", "energized", "positive"};
    
    if (storage.saveMoodEntry(entry1)) {
        cout << "✓ Saved mood entry: " << entry1.content.substr(0, 30) << "..." << endl;
    }
    
    if (storage.saveMoodEntry(entry2)) {
        cout << "✓ Saved mood entry: " << entry2.content.substr(0, 30) << "..." << endl;
    }
    
    // Test loading mood entries
    vector<MoodEntry> loadedEntries;
    if (storage.loadMoodEntries(loadedEntries)) {
        cout << "✓ Loaded " << loadedEntries.size() << " mood entries" << endl;
        for (const auto& entry : loadedEntries) {
            cout << "  - Mood " << (int)entry.mood << ": " << entry.content.substr(0, 40) << "..." << endl;
        }
    }
    
    cout << "\n=== Storage Test Complete ===" << endl;
    cout << "Check the 'data' folder to see the saved files!" << endl;
    
    return 0;
}
