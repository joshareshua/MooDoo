#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iostream>

// Data structures
enum class Priority {
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3
};

enum class MoodLevel {
    VERY_LOW = 1,
    LOW = 2,
    NEUTRAL = 3,
    GOOD = 4,
    EXCELLENT = 5
};

struct Task {
    int id;
    std::string title;
    std::string description;
    Priority priority;
    bool completed;
    time_t created;
    time_t completed_time;
    
    Task() : id(0), priority(Priority::MEDIUM), completed(false), 
             created(time(nullptr)), completed_time(0) {}
};

struct MoodEntry {
    int id;
    std::string content;
    MoodLevel mood;
    time_t timestamp;
    std::vector<std::string> keywords;
    
    MoodEntry() : id(0), mood(MoodLevel::NEUTRAL), timestamp(time(nullptr)) {}
};

class Storage {
private:
    std::string tasksFile;
    std::string journalFile;
    int nextTaskId;
    int nextMoodId;
    
    // Helper methods
    std::string priorityToString(Priority priority);
    Priority stringToPriority(const std::string& str);
    std::string moodToString(MoodLevel mood);
    MoodLevel stringToMood(const std::string& str);
    std::string timeToString(time_t time);
    time_t stringToTime(const std::string& str);

public:
    Storage(const std::string& tasksFile = "data/tasks.txt", 
            const std::string& journalFile = "data/journal.txt");
    
    // Task operations
    bool saveTask(const Task& task);
    bool loadTasks(std::vector<Task>& tasks);
    bool updateTask(const Task& task);
    bool deleteTask(int taskId);
    
    // Journal operations
    bool saveMoodEntry(const MoodEntry& entry);
    bool loadMoodEntries(std::vector<MoodEntry>& entries);
    bool updateMoodEntry(const MoodEntry& entry);
    bool deleteMoodEntry(int entryId);
    
    // Utility methods
    int getNextTaskId();
    int getNextMoodId();
    void initializeFiles();
    bool backupData();
    bool restoreData();
    
    // Getter methods for file paths
    std::string getTasksFile() const { return tasksFile; }
    std::string getJournalFile() const { return journalFile; }
};

#endif // STORAGE_H
