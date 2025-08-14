#include "Storage.h"
#include <algorithm>
#include <filesystem>

Storage::Storage(const std::string& tasksFile, const std::string& journalFile) 
    : tasksFile(tasksFile), journalFile(journalFile), nextTaskId(1), nextMoodId(1) {
    initializeFiles();
}

void Storage::initializeFiles() {
    // Create data directory if it doesn't exist
    std::filesystem::create_directories("data");
    
    // Initialize files if they don't exist
    std::ofstream taskFile(tasksFile, std::ios::app);
    std::ofstream journalFileStream(journalFile, std::ios::app);
    
    if (taskFile.is_open()) taskFile.close();
    if (journalFileStream.is_open()) journalFileStream.close();
}

// Helper methods for converting enums to strings and back
std::string Storage::priorityToString(Priority priority) {
    switch (priority) {
        case Priority::LOW: return "1";
        case Priority::MEDIUM: return "2";
        case Priority::HIGH: return "3";
        default: return "2";
    }
}

Priority Storage::stringToPriority(const std::string& str) {
    if (str == "1") return Priority::LOW;
    if (str == "3") return Priority::HIGH;
    return Priority::MEDIUM; // default
}

std::string Storage::difficultyToString(TaskDifficulty difficulty) {
    switch (difficulty) {
        case TaskDifficulty::EASY: return "1";
        case TaskDifficulty::MEDIUM: return "2";
        case TaskDifficulty::HARD: return "3";
        default: return "2";
    }
}

TaskDifficulty Storage::stringToDifficulty(const std::string& str) {
    if (str == "1") return TaskDifficulty::EASY;
    if (str == "3") return TaskDifficulty::HARD;
    return TaskDifficulty::MEDIUM; // default
}

std::string Storage::moodToString(MoodLevel mood) {
    switch (mood) {
        case MoodLevel::VERY_LOW: return "1";
        case MoodLevel::LOW: return "2";
        case MoodLevel::NEUTRAL: return "3";
        case MoodLevel::GOOD: return "4";
        case MoodLevel::EXCELLENT: return "5";
        default: return "3";
    }
}

MoodLevel Storage::stringToMood(const std::string& str) {
    if (str == "1") return MoodLevel::VERY_LOW;
    if (str == "2") return MoodLevel::LOW;
    if (str == "4") return MoodLevel::GOOD;
    if (str == "5") return MoodLevel::EXCELLENT;
    return MoodLevel::NEUTRAL; // default
}

std::string Storage::timeToString(time_t time) {
    return std::to_string(time);
}

time_t Storage::stringToTime(const std::string& str) {
    try {
        return std::stol(str);
    } catch (...) {
        return time(nullptr);
    }
}

// Task operations
bool Storage::saveTask(const Task& task) {
    std::ofstream file(tasksFile, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open tasks file for writing" << std::endl;
        return false;
    }
    
    file << task.id << "|"
         << task.title << "|"
         << task.description << "|"
         << priorityToString(task.priority) << "|"
         << difficultyToString(task.difficulty) << "|"
         << (task.completed ? "1" : "0") << "|"
         << timeToString(task.created) << "|"
         << timeToString(task.completed_time) << std::endl;
    
    file.close();
    nextTaskId = std::max(nextTaskId, task.id + 1);
    return true;
}

bool Storage::loadTasks(std::vector<Task>& tasks) {
    tasks.clear();
    std::ifstream file(tasksFile);
    if (!file.is_open()) {
        return true; // File doesn't exist yet, that's okay
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        std::string token;
        Task task;
        
        // Parse: id|title|description|priority|difficulty|completed|created|completed_time
        if (std::getline(ss, token, '|')) task.id = std::stoi(token);
        if (std::getline(ss, task.title, '|')) {}
        if (std::getline(ss, task.description, '|')) {}
        if (std::getline(ss, token, '|')) task.priority = stringToPriority(token);
        if (std::getline(ss, token, '|')) task.difficulty = stringToDifficulty(token);
        if (std::getline(ss, token, '|')) task.completed = (token == "1");
        if (std::getline(ss, token, '|')) task.created = stringToTime(token);
        if (std::getline(ss, token, '|')) task.completed_time = stringToTime(token);
        
        tasks.push_back(task);
        nextTaskId = std::max(nextTaskId, task.id + 1);
    }
    
    file.close();
    return true;
}

// Journal operations
bool Storage::saveMoodEntry(const MoodEntry& entry) {
    std::ofstream file(journalFile, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open journal file for writing" << std::endl;
        return false;
    }
    
    // Convert keywords vector to comma-separated string
    std::string keywordsStr;
    for (size_t i = 0; i < entry.keywords.size(); ++i) {
        if (i > 0) keywordsStr += ",";
        keywordsStr += entry.keywords[i];
    }
    
    file << entry.id << "|"
         << entry.content << "|"
         << moodToString(entry.mood) << "|"
         << timeToString(entry.timestamp) << "|"
         << keywordsStr << "|"
         << entry.sentimentScore << std::endl;
    
    file.close();
    nextMoodId = std::max(nextMoodId, entry.id + 1);
    return true;
}

bool Storage::loadMoodEntries(std::vector<MoodEntry>& entries) {
    entries.clear();
    std::ifstream file(journalFile);
    if (!file.is_open()) {
        return true; // File doesn't exist yet, that's okay
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        std::string token;
        MoodEntry entry;
        
        // Parse: id|content|mood|timestamp|keywords|sentimentScore
        if (std::getline(ss, token, '|')) entry.id = std::stoi(token);
        if (std::getline(ss, entry.content, '|')) {}
        if (std::getline(ss, token, '|')) entry.mood = stringToMood(token);
        if (std::getline(ss, token, '|')) entry.timestamp = stringToTime(token);
        if (std::getline(ss, token, '|')) {
            // Parse keywords
            std::stringstream keywordStream(token);
            std::string keyword;
            while (std::getline(keywordStream, keyword, ',')) {
                if (!keyword.empty()) {
                    entry.keywords.push_back(keyword);
                }
            }
        }
        if (std::getline(ss, token, '|')) {
            try {
                entry.sentimentScore = std::stod(token);
            } catch (...) {
                entry.sentimentScore = 0.0;
            }
        }
        
        entries.push_back(entry);
        nextMoodId = std::max(nextMoodId, entry.id + 1);
    }
    
    file.close();
    return true;
}

// Utility methods
int Storage::getNextTaskId() {
    return nextTaskId++;
}

int Storage::getNextMoodId() {
    return nextMoodId++;
}

// Placeholder implementations for future features
bool Storage::updateTask(const Task& updatedTask) {
    // Load all tasks
    std::vector<Task> tasks;
    if (!loadTasks(tasks)) {
        return false;
    }
    
    // Find and update the specific task
    for (auto& task : tasks) {
        if (task.id == updatedTask.id) {
            task = updatedTask;
            break;
        }
    }
    
    // Rewrite the entire file with updated data
    std::ofstream file(tasksFile, std::ios::trunc); // Truncate file
    if (!file.is_open()) {
        std::cerr << "Error: Could not open tasks file for updating" << std::endl;
        return false;
    }
    
    for (const auto& task : tasks) {
        file << task.id << "|"
             << task.title << "|"
             << task.description << "|"
             << priorityToString(task.priority) << "|"
             << difficultyToString(task.difficulty) << "|"
             << (task.completed ? "1" : "0") << "|"
             << timeToString(task.created) << "|"
             << timeToString(task.completed_time) << std::endl;
    }
    
    file.close();
    return true;
}

bool Storage::deleteTask(int taskId) {
    // Load all tasks
    std::vector<Task> tasks;
    if (!loadTasks(tasks)) {
        return false;
    }
    
    // Find and remove the task
    auto it = std::find_if(tasks.begin(), tasks.end(), 
                          [taskId](const Task& task) { return task.id == taskId; });
    
    if (it == tasks.end()) {
        return false; // Task not found
    }
    
    tasks.erase(it);
    
    // Rewrite file without the deleted task
    std::ofstream file(tasksFile, std::ios::trunc);
    if (!file.is_open()) {
        return false;
    }
    
    for (const auto& task : tasks) {
        file << task.id << "|"
             << task.title << "|"
             << task.description << "|"
             << priorityToString(task.priority) << "|"
             << difficultyToString(task.difficulty) << "|"
             << (task.completed ? "1" : "0") << "|"
             << timeToString(task.created) << "|"
             << timeToString(task.completed_time) << std::endl;
    }
    
    file.close();
    return true;
}

bool Storage::updateMoodEntry(const MoodEntry& entry) {
    // Load all mood entries
    std::vector<MoodEntry> entries;
    if (!loadMoodEntries(entries)) {
        return false;
    }
    
    // Find and update the entry
    for (auto& moodEntry : entries) {
        if (moodEntry.id == entry.id) {
            moodEntry = entry;
            break;
        }
    }
    
    // Rewrite file with updated data
    std::ofstream file(journalFile, std::ios::trunc);
    if (!file.is_open()) {
        return false;
    }
    
    for (const auto& moodEntry : entries) {
        // Convert keywords to comma-separated string
        std::string keywordsStr;
        for (size_t i = 0; i < moodEntry.keywords.size(); ++i) {
            if (i > 0) keywordsStr += ",";
            keywordsStr += moodEntry.keywords[i];
        }
        
        file << moodEntry.id << "|"
             << moodEntry.content << "|"
             << moodToString(moodEntry.mood) << "|"
             << timeToString(moodEntry.timestamp) << "|"
             << keywordsStr << "|"
             << moodEntry.sentimentScore << std::endl;
    }
    
    file.close();
    return true;
}

bool Storage::deleteMoodEntry(int entryId) {
    // Load all mood entries
    std::vector<MoodEntry> entries;
    if (!loadMoodEntries(entries)) {
        return false;
    }
    
    // Find and remove the entry
    auto it = std::find_if(entries.begin(), entries.end(), 
                          [entryId](const MoodEntry& entry) { return entry.id == entryId; });
    
    if (it == entries.end()) {
        return false; // Entry not found
    }
    
    entries.erase(it);
    
    // Rewrite file without the deleted entry
    std::ofstream file(journalFile, std::ios::trunc);
    if (!file.is_open()) {
        return false;
    }
    
    for (const auto& entry : entries) {
        // Convert keywords to comma-separated string
        std::string keywordsStr;
        for (size_t i = 0; i < entry.keywords.size(); ++i) {
            if (i > 0) keywordsStr += ",";
            keywordsStr += entry.keywords[i];
        }
        
        file << entry.id << "|"
             << entry.content << "|"
             << moodToString(entry.mood) << "|"
             << timeToString(entry.timestamp) << "|"
             << keywordsStr << "|"
             << entry.sentimentScore << std::endl;
    }
    
    file.close();
    return true;
}

bool Storage::backupData() {
    // Create backup directory
    std::filesystem::create_directories("data/backup");
    
    // Get current timestamp for backup filename
    time_t now = time(nullptr);
    std::string timestamp = std::to_string(now);
    
    // Backup tasks file
    std::string tasksBackup = "data/backup/tasks_" + timestamp + ".txt";
    if (!std::filesystem::copy_file(tasksFile, tasksBackup)) {
        return false;
    }
    
    // Backup journal file
    std::string journalBackup = "data/backup/journal_" + timestamp + ".txt";
    if (!std::filesystem::copy_file(journalFile, journalBackup)) {
        return false;
    }
    
    return true;
}

bool Storage::restoreData() {
    // List available backups
    std::cout << "Available backups:" << std::endl;
    std::vector<std::string> backups;
    
    for (const auto& entry : std::filesystem::directory_iterator("data/backup")) {
        if (entry.is_regular_file()) {
            backups.push_back(entry.path().filename().string());
            std::cout << "  " << entry.path().filename().string() << std::endl;
        }
    }
    
    if (backups.empty()) {
        std::cout << "No backups found." << std::endl;
        return false;
    }
    
    // For now, restore the most recent backup
    // In a real app, you'd ask user which backup to restore
    std::string latestBackup = backups.back();
    
    // Restore tasks
    std::string tasksBackup = "data/backup/" + latestBackup;
    if (latestBackup.find("tasks_") == 0) {
        if (!std::filesystem::copy_file(tasksBackup, tasksFile, std::filesystem::copy_options::overwrite_existing)) {
            return false;
        }
    }
    
    // Restore journal
    std::string journalBackup = "data/backup/" + latestBackup;
    if (latestBackup.find("journal_") == 0) {
        if (!std::filesystem::copy_file(journalBackup, journalFile, std::filesystem::copy_options::overwrite_existing)) {
            return false;
        }
    }
    
    return true;
}
