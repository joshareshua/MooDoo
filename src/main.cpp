#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "Storage.h"
#include "MoodAnalyzer.h"
using namespace std;

void clearScreen() {
    cout << "\033[2J\033[1;1H"; // Clear screen
}

void showMenu() {
    cout << "\n=== MooDoo: Your Mood-Aware Planner ===" << endl;
    cout << "1. Add a new task" << endl;
    cout << "2. Add a mood entry" << endl;
    cout << "3. View all tasks" << endl;
    cout << "4. Mark task complete/incomplete" << endl;
    cout << "5. Edit a task" << endl;
    cout << "6. Delete a task" << endl;
    cout << "7. View mood history" << endl;
    cout << "8. Get mood insights" << endl;
    cout << "9. Daily summary" << endl;
    cout << "10. Weekly patterns" << endl;
    cout << "11. Exit" << endl;
    cout << "Choose an option (1-11): ";
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
    
    cout << "Difficulty (1=Easy, 2=Medium, 3=Hard): ";
    int difficultyChoice;
    cin >> difficultyChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    switch(difficultyChoice) {
        case 1: task.difficulty = TaskDifficulty::EASY; break;
        case 3: task.difficulty = TaskDifficulty::HARD; break;
        default: task.difficulty = TaskDifficulty::MEDIUM; break;
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
    
    // Analyze the mood entry before saving
    MoodAnalyzer analyzer;
    analyzer.analyzeMoodEntry(entry);
    
    if (storage.saveMoodEntry(entry)) {
        cout << "✓ Mood entry saved successfully!" << endl;
        
        // Generate and show supportive message
        cout << analyzer.generateSupportiveMessage(entry);
        
        // Show detailed insights
        cout << analyzer.generateDetailedInsights(entry);
        
        // Show task suggestion based on mood
        vector<Task> tasks;
        storage.loadTasks(tasks);
        int completedTasks = 0;
        for (const auto& task : tasks) {
            if (task.completed) completedTasks++;
        }
        
        cout << analyzer.generateTaskSuggestion(entry.mood, completedTasks, tasks.size()) << endl;
        
    } else {
        cout << "✗ Error saving mood entry" << endl;
    }
}

void markTaskComplete(Storage& storage) {
    clearScreen();
    cout << "=== Mark Task Complete/Incomplete ===" << endl;
    
    // First, show all tasks
    vector<Task> tasks;
    if (!storage.loadTasks(tasks)) {
        cout << "Error loading tasks" << endl;
        return;
    }
    
    if (tasks.empty()) {
        cout << "No tasks found. Add some tasks first!" << endl;
        return;
    }
    
    // Display tasks with numbers
    for (size_t i = 0; i < tasks.size(); i++) {
        string status = tasks[i].completed ? "✓ Done" : "○ Pending";
        string priorityStr;
        switch(tasks[i].priority) {
            case Priority::LOW: priorityStr = "Low"; break;
            case Priority::HIGH: priorityStr = "High"; break;
            default: priorityStr = "Medium"; break;
        }
        
        cout << "[" << (i + 1) << "] " << status << " | " << priorityStr << " | " << tasks[i].title << endl;
    }
    
    cout << "\nEnter task number to toggle (1-" << tasks.size() << "): ";
    int taskChoice;
    cin >> taskChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (taskChoice < 1 || taskChoice > static_cast<int>(tasks.size())) {
        cout << "Invalid task number!" << endl;
        return;
    }
    
    // Toggle completion status
    Task& selectedTask = tasks[taskChoice - 1];
    selectedTask.completed = !selectedTask.completed;
    
    if (selectedTask.completed) {
        selectedTask.completed_time = time(nullptr);
        cout << "✓ Marked '" << selectedTask.title << "' as complete!" << endl;
    } else {
        selectedTask.completed_time = 0;
        cout << "○ Marked '" << selectedTask.title << "' as incomplete" << endl;
    }
    
    // Save the updated task
    if (storage.updateTask(selectedTask)) {
        cout << "✓ Task status saved!" << endl;
    } else {
        cout << "✗ Error saving task status" << endl;
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
            int completedCount = 0;
            for (const auto& task : tasks) {
                string priorityStr;
                switch(task.priority) {
                    case Priority::LOW: priorityStr = "Low"; break;
                    case Priority::HIGH: priorityStr = "High"; break;
                    default: priorityStr = "Medium"; break;
                }
                
                string difficultyStr;
                switch(task.difficulty) {
                    case TaskDifficulty::EASY: difficultyStr = "Easy"; break;
                    case TaskDifficulty::HARD: difficultyStr = "Hard"; break;
                    default: difficultyStr = "Medium"; break;
                }
                
                string status = task.completed ? "✓ Done" : "○ Pending";
                if (task.completed) completedCount++;
                
                cout << "[" << task.id << "] " << status << " | " << priorityStr << " | " << difficultyStr << " | " << task.title << endl;
                cout << "    " << task.description << endl << endl;
            }
            
            // Show completion summary
            cout << "--- Progress: " << completedCount << "/" << tasks.size() << " tasks completed ---" << endl;
            
            // Show mood-based recommendations if we have recent mood data
            vector<MoodEntry> recentMoods;
            if (storage.loadMoodEntries(recentMoods) && !recentMoods.empty()) {
                MoodAnalyzer analyzer;
                MoodEntry latestMood = recentMoods.back(); // Get most recent mood
                cout << analyzer.generateMoodBasedTaskRecommendations(latestMood.mood, tasks) << endl;
            }
        }
    } else {
        cout << "Error loading tasks" << endl;
    }
}

void editTask(Storage& storage) {
    clearScreen();
    cout << "=== Edit Task ===" << endl;
    
    // First, show all tasks
    vector<Task> tasks;
    if (!storage.loadTasks(tasks)) {
        cout << "Error loading tasks" << endl;
        return;
    }
    
    if (tasks.empty()) {
        cout << "No tasks found. Add some tasks first!" << endl;
        return;
    }
    
    // Display tasks with numbers
    for (size_t i = 0; i < tasks.size(); i++) {
        string status = tasks[i].completed ? "✓ Done" : "○ Pending";
        string priorityStr;
        switch(tasks[i].priority) {
            case Priority::LOW: priorityStr = "Low"; break;
            case Priority::HIGH: priorityStr = "High"; break;
            default: priorityStr = "Medium"; break;
        }
        
        cout << "[" << (i + 1) << "] " << status << " | " << priorityStr << " | " << tasks[i].title << endl;
    }
    
    cout << "\nEnter task number to edit (1-" << tasks.size() << "): ";
    int taskChoice;
    cin >> taskChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (taskChoice < 1 || taskChoice > static_cast<int>(tasks.size())) {
        cout << "Invalid task number!" << endl;
        return;
    }
    
    Task& selectedTask = tasks[taskChoice - 1];
    
    cout << "\nCurrent task: " << selectedTask.title << endl;
    cout << "Current description: " << selectedTask.description << endl;
    
    cout << "\nEnter new title (or press Enter to keep current): ";
    string newTitle;
    getline(cin, newTitle);
    if (!newTitle.empty()) {
        selectedTask.title = newTitle;
    }
    
    cout << "Enter new description (or press Enter to keep current): ";
    string newDescription;
    getline(cin, newDescription);
    if (!newDescription.empty()) {
        selectedTask.description = newDescription;
    }
    
    cout << "Change priority? (1=Low, 2=Medium, 3=High, 0=keep current): ";
    int priorityChoice;
    cin >> priorityChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (priorityChoice > 0) {
        switch(priorityChoice) {
            case 1: selectedTask.priority = Priority::LOW; break;
            case 3: selectedTask.priority = Priority::HIGH; break;
            case 2: selectedTask.priority = Priority::MEDIUM; break;
        }
    }
    
    cout << "Change difficulty? (1=Easy, 2=Medium, 3=Hard, 0=keep current): ";
    int difficultyChoice;
    cin >> difficultyChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (difficultyChoice > 0) {
        switch(difficultyChoice) {
            case 1: selectedTask.difficulty = TaskDifficulty::EASY; break;
            case 3: selectedTask.difficulty = TaskDifficulty::HARD; break;
            case 2: selectedTask.difficulty = TaskDifficulty::MEDIUM; break;
        }
    }
    
    if (storage.updateTask(selectedTask)) {
        cout << "✓ Task updated successfully!" << endl;
    } else {
        cout << "✗ Error updating task" << endl;
    }
}

void deleteTask(Storage& storage) {
    clearScreen();
    cout << "=== Delete Task ===" << endl;
    
    // First, show all tasks
    vector<Task> tasks;
    if (!storage.loadTasks(tasks)) {
        cout << "Error loading tasks" << endl;
        return;
    }
    
    if (tasks.empty()) {
        cout << "No tasks found. Add some tasks first!" << endl;
        return;
    }
    
    // Display tasks with numbers
    for (size_t i = 0; i < tasks.size(); i++) {
        string status = tasks[i].completed ? "✓ Done" : "○ Pending";
        string priorityStr;
        switch(tasks[i].priority) {
            case Priority::LOW: priorityStr = "Low"; break;
            case Priority::HIGH: priorityStr = "High"; break;
            default: priorityStr = "Medium"; break;
        }
        
        cout << "[" << (i + 1) << "] " << status << " | " << priorityStr << " | " << tasks[i].title << endl;
    }
    
    cout << "\nEnter task number to delete (1-" << tasks.size() << "): ";
    int taskChoice;
    cin >> taskChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (taskChoice < 1 || taskChoice > static_cast<int>(tasks.size())) {
        cout << "Invalid task number!" << endl;
        return;
    }
    
    Task& selectedTask = tasks[taskChoice - 1];
    
    cout << "\nAre you sure you want to delete: '" << selectedTask.title << "'? (y/n): ";
    char confirm;
    cin >> confirm;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (confirm == 'y' || confirm == 'Y') {
        // Remove the task from the vector
        tasks.erase(tasks.begin() + taskChoice - 1);
        
        // Rewrite the entire file without the deleted task
        ofstream file(storage.getTasksFile(), ios::trunc);
        if (file.is_open()) {
            for (const auto& task : tasks) {
                file << task.id << "|"
                     << task.title << "|"
                     << task.description << "|"
                     << (task.priority == Priority::LOW ? "1" : 
                         task.priority == Priority::HIGH ? "3" : "2") << "|"
                     << (task.difficulty == TaskDifficulty::EASY ? "1" : 
                         task.difficulty == TaskDifficulty::HARD ? "3" : "2") << "|"
                     << (task.completed ? "1" : "0") << "|"
                     << task.created << "|"
                     << task.completed_time << endl;
            }
            file.close();
            cout << "✓ Task deleted successfully!" << endl;
        } else {
            cout << "✗ Error deleting task" << endl;
        }
    } else {
        cout << "Task deletion cancelled." << endl;
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

void getMoodInsights(Storage& storage) {
    clearScreen();
    cout << "=== Mood Insights ===" << endl;
    
    vector<MoodEntry> entries;
    if (storage.loadMoodEntries(entries)) {
        if (entries.size() < 2) {
            cout << "Add more mood entries to get insights about your patterns!" << endl;
        } else {
            MoodAnalyzer analyzer;
            cout << analyzer.analyzeMoodTrend(entries) << endl;
            
            // Show some basic statistics
            int totalEntries = entries.size();
            int lowMoodCount = 0, highMoodCount = 0, neutralCount = 0;
            
            for (const auto& entry : entries) {
                if (entry.mood == MoodLevel::VERY_LOW || entry.mood == MoodLevel::LOW) {
                    lowMoodCount++;
                } else if (entry.mood == MoodLevel::GOOD || entry.mood == MoodLevel::EXCELLENT) {
                    highMoodCount++;
                } else {
                    neutralCount++;
                }
            }
            
            cout << "\n📈 Your Mood Summary:" << endl;
            cout << "Total entries: " << totalEntries << endl;
            cout << "Low mood days: " << lowMoodCount << " (" << (lowMoodCount * 100 / totalEntries) << "%)" << endl;
            cout << "High mood days: " << highMoodCount << " (" << (highMoodCount * 100 / totalEntries) << "%)" << endl;
            cout << "Neutral days: " << neutralCount << " (" << (neutralCount * 100 / totalEntries) << "%)" << endl;
        }
    } else {
        cout << "Error loading mood entries" << endl;
    }
}

void showDailySummary(Storage& storage) {
    clearScreen();
    cout << "=== Daily Summary ===" << endl;
    
    // Get today's date
    time_t now = time(nullptr);
    tm* today = localtime(&now);
    int todayDay = today->tm_mday;
    int todayMonth = today->tm_mon + 1;
    int todayYear = today->tm_year + 1900;
    
    cout << "📅 Date: " << todayMonth << "/" << todayDay << "/" << todayYear << endl << endl;
    
    // Load today's mood entries
    vector<MoodEntry> allMoods;
    vector<MoodEntry> todayMoods;
    if (storage.loadMoodEntries(allMoods)) {
        for (const auto& mood : allMoods) {
            tm* moodTime = localtime(&mood.timestamp);
            if (moodTime->tm_mday == todayDay && 
                moodTime->tm_mon == today->tm_mon && 
                moodTime->tm_year == today->tm_year) {
                todayMoods.push_back(mood);
            }
        }
    }
    
    // Show mood summary
    if (todayMoods.empty()) {
        cout << "💭 No mood entries today. How are you feeling?" << endl;
    } else if (todayMoods.size() == 1) {
        string moodStr;
        switch(todayMoods[0].mood) {
            case MoodLevel::VERY_LOW: moodStr = "😞 Very Low"; break;
            case MoodLevel::LOW: moodStr = "😔 Low"; break;
            case MoodLevel::NEUTRAL: moodStr = "😐 Neutral"; break;
            case MoodLevel::GOOD: moodStr = "😊 Good"; break;
            case MoodLevel::EXCELLENT: moodStr = "😄 Excellent"; break;
        }
        cout << "💭 Today's Mood: " << moodStr << endl;
    } else {
        cout << "💭 Mood Trend: ";
        string firstMood, lastMood;
        switch(todayMoods.front().mood) {
            case MoodLevel::VERY_LOW: firstMood = "😞"; break;
            case MoodLevel::LOW: firstMood = "😔"; break;
            case MoodLevel::NEUTRAL: firstMood = "😐"; break;
            case MoodLevel::GOOD: firstMood = "😊"; break;
            case MoodLevel::EXCELLENT: firstMood = "😄"; break;
        }
        switch(todayMoods.back().mood) {
            case MoodLevel::VERY_LOW: lastMood = "😞"; break;
            case MoodLevel::LOW: lastMood = "😔"; break;
            case MoodLevel::NEUTRAL: lastMood = "😐"; break;
            case MoodLevel::GOOD: lastMood = "😊"; break;
            case MoodLevel::EXCELLENT: lastMood = "😄"; break;
        }
        cout << firstMood << " → " << lastMood << endl;
    }
    
    // Load today's tasks
    vector<Task> allTasks;
    int completedToday = 0, totalToday = 0;
    if (storage.loadTasks(allTasks)) {
        for (const auto& task : allTasks) {
            tm* taskTime = localtime(&task.created);
            if (taskTime->tm_mday == todayDay && 
                taskTime->tm_mon == today->tm_mon && 
                taskTime->tm_year == today->tm_year) {
                totalToday++;
                if (task.completed) completedToday++;
            }
        }
    }
    
    // Show task summary
    cout << "✅ Tasks: " << completedToday << "/" << totalToday << " completed";
    if (totalToday > 0) {
        int percent = (completedToday * 100) / totalToday;
        cout << " (" << percent << "%)";
    }
    cout << endl;
    
    // Show encouraging message
    cout << "\n💪 ";
    if (completedToday == 0 && totalToday == 0) {
        cout << "No tasks today. Ready to start fresh tomorrow!";
    } else if (completedToday == 0) {
        cout << "Every journey starts with one step. You've got this!";
    } else if (completedToday == totalToday) {
        cout << "Amazing! You completed everything today!";
    } else if (completedToday > totalToday / 2) {
        cout << "Great progress! You're building momentum!";
    } else {
        cout << "You're making progress. Every task counts!";
    }
    cout << endl;
}

void showWeeklyPatterns(Storage& storage) {
    clearScreen();
    cout << "=== Weekly Mood & Productivity Patterns ===" << endl;
    
    vector<MoodEntry> moods;
    vector<Task> tasks;
    
    if (storage.loadMoodEntries(moods) && storage.loadTasks(tasks)) {
        MoodAnalyzer analyzer;
        cout << analyzer.analyzeWeeklyPatterns(moods, tasks) << endl;
    } else {
        cout << "Error loading data for pattern analysis." << endl;
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
                markTaskComplete(storage);
                break;
            case 5:
                editTask(storage);
                break;
            case 6:
                deleteTask(storage);
                break;
            case 7:
                viewMoodHistory(storage);
                break;
            case 8:
                getMoodInsights(storage);
                break;
            case 9:
                showDailySummary(storage);
                break;
            case 10:
                showWeeklyPatterns(storage);
                break;
            case 11:
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
