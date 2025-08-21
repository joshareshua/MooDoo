#include "TaskListPage.h"
#include <QMessageBox>

TaskListPage::TaskListPage(Storage* storage, QWidget *parent)
    : QWidget(parent), storage(storage)
{
    setWindowTitle("📋 All Your Tasks - MooDoo");
    setWindowFlags(Qt::Window);
    resize(600, 500);
    
    setupUI();
    refreshTaskList();
}

TaskListPage::~TaskListPage()
{
}

void TaskListPage::setupUI()
{
    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30, 30, 30, 30);
    
    // Title
    titleLabel = new QLabel("📋 All Your Tasks", this);
    titleLabel->setStyleSheet(
        "font-size: 32px; "
        "font-weight: bold; "
        "color: #4A90E2; "
        "margin-bottom: 20px; "
        "text-align: center;"
    );
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);
    
    // Task list
    taskListWidget = new QListWidget(this);
    taskListWidget->setStyleSheet(
        "QListWidget { "
        "   border: 2px solid #ddd; "
        "   border-radius: 8px; "
        "   padding: 10px; "
        "   background-color: #fafafa; "
        "   font-size: 14px; "
        "   min-height: 400px; "
        "}"
    );
    mainLayout->addWidget(taskListWidget);
    
    // Button row
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    
    // Back button
    backButton = new QPushButton("← Back to Main Menu", this);
    backButton->setStyleSheet(
        "QPushButton { "
        "   background-color: #666; "
        "   color: white; "
        "   border: none; "
        "   padding: 12px 20px; "
        "   font-size: 14px; "
        "   border-radius: 6px; "
        "   min-width: 150px; "
        "} "
        "QPushButton:hover { "
        "   background-color: #555; "
        "}"
    );
    buttonLayout->addWidget(backButton);
    
    buttonLayout->addStretch();
    
    // Refresh button
    refreshButton = new QPushButton("🔄 Refresh Tasks", this);
    refreshButton->setStyleSheet(
        "QPushButton { "
        "   background-color: #9C27B0; "
        "   color: white; "
        "   border: none; "
        "   padding: 12px 20px; "
        "   font-size: 14px; "
        "   border-radius: 6px; "
        "   min-width: 120px; "
        "} "
        "QPushButton:hover { "
        "   background-color: #7B1FA2; "
        "}"
    );
    buttonLayout->addWidget(refreshButton);
    
    mainLayout->addLayout(buttonLayout);
    
    // Connect signals
    connect(backButton, &QPushButton::clicked, this, &TaskListPage::onBackClicked);
    connect(refreshButton, &QPushButton::clicked, this, &TaskListPage::onRefreshClicked);
}

void TaskListPage::refreshTaskList()
{
    taskListWidget->clear();
    
    std::vector<Task> tasks;
    if (storage->loadTasks(tasks)) {
        if (tasks.empty()) {
            taskListWidget->addItem("No tasks found. Add some tasks to get started!");
            return;
        }
        
        for (const auto& task : tasks) {
            QString taskText;
            
            // Add priority indicator
            switch(task.priority) {
                case Priority::LOW: taskText += "🟢 "; break;
                case Priority::HIGH: taskText += "🔴 "; break;
                default: taskText += "🟡 "; break;
            }
            
            // Add difficulty indicator
            switch(task.difficulty) {
                case TaskDifficulty::EASY: taskText += "📚 "; break;
                case TaskDifficulty::HARD: taskText += "💪 "; break;
                default: taskText += "📝 "; break;
            }
            
            // Add task title
            taskText += QString::fromStdString(task.title);
            
            // Add description if available
            if (!task.description.empty()) {
                taskText += " - " + QString::fromStdString(task.description);
            }
            
            // Create list item (no need to store task ID for viewing only)
            taskListWidget->addItem(taskText);
        }
    } else {
        taskListWidget->addItem("Error loading tasks");
    }
}

void TaskListPage::onBackClicked()
{
    // Close this window
    close();
}

void TaskListPage::onRefreshClicked()
{
    refreshTaskList();
} 