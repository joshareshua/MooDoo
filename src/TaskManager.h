#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <string>
#include <vector>
#include <ctime>

// Task priority levels
enum class Priority {
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3,
    URGENT = 4
};

// Task status
enum class TaskStatus {
    PENDING,
    IN_PROGRESS,
    COMPLETED,
    CANCELLED
};

// Task data structure
struct Task {
    int id;
    std::string title;
    std::string description;
    Priority priority;
    TaskStatus status;
    time_t created;
    time_t completed;
    time_t due_date;
    
    Task() : id(0), priority(Priority::MEDIUM), status(TaskStatus::PENDING), 
             created(0), completed(0), due_date(0) {}
};

class TaskManager {
private:
    std::vector<Task> tasks;
    int next_id;
    
    // Helper methods
    std::string priorityToString(Priority priority) const;
    std::string statusToString(TaskStatus status) const;
    std::string formatTimestamp(time_t timestamp) const;

public:
    TaskManager();
    
    // CRUD operations
    int createTask(const std::string& title, const std::string& description = "", 
                   Priority priority = Priority::MEDIUM, time_t due_date = 0);
    bool updateTask(int id, const std::string& title = "", const std::string& description = "", 
                   Priority priority = Priority::MEDIUM, TaskStatus status = TaskStatus::PENDING);
    bool deleteTask(int id);
    Task* getTask(int id);
    
    // Task operations
    bool completeTask(int id);
    bool startTask(int id);
    bool cancelTask(int id);
    
    // Query methods
    std::vector<Task> getAllTasks() const;
    std::vector<Task> getTasksByStatus(TaskStatus status) const;
    std::vector<Task> getTasksByPriority(Priority priority) const;
    std::vector<Task> getOverdueTasks() const;
    std::vector<Task> getTodayTasks() const;
    
    // Statistics
    int getTotalTasks() const;
    int getCompletedTasks() const;
    int getPendingTasks() const;
    double getCompletionRate() const;
    
    // Display methods
    void displayAllTasks() const;
    void displayTask(const Task& task) const;
    void displayTasksByStatus(TaskStatus status) const;
    void displayTasksByPriority(Priority priority) const;
    
    // Mood-aware suggestions
    std::vector<Task> getSuggestedTasks(const std::string& mood) const;
    void adjustTaskPriorities(const std::string& mood);
};

#endif // TASK_MANAGER_H
