#include "MainWindow.h"
#include <QApplication>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QGroupBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("MooDoo - Your Mood-Aware Planner");
    setMinimumSize(1000, 700);
    
    // Initialize storage
    storage = new Storage();
    
    setupUI();
    createMenuBar();
    
    // Load and display initial tasks
    refreshTaskList();
    
    // Set status bar
    statusBar()->showMessage("Ready");
}

MainWindow::~MainWindow()
{
    delete storage;
}

void MainWindow::setupUI()
{
    // Create central widget and main layout
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(40, 40, 40, 40);
    
    // Create title
    titleLabel = new QLabel("MooDoo", this);
    titleLabel->setStyleSheet("font-size: 48px; font-weight: bold; color: #4A90E2; margin-bottom: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);
    
    // Create subtitle
    subtitleLabel = new QLabel("Your Mood-Aware Planner", this);
    subtitleLabel->setStyleSheet("font-size: 18px; color: #666; margin-bottom: 30px;");
    subtitleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(subtitleLabel);
    
    // Create buttons
    addTaskButton = new QPushButton("➕ Add New Task", this);
    addTaskButton->setStyleSheet(
        "QPushButton { "
        "   background-color: #4CAF50; "
        "   color: white; "
        "   border: none; "
        "   padding: 15px; "
        "   font-size: 16px; "
        "   border-radius: 8px; "
        "   min-height: 50px; "
        "} "
        "QPushButton:hover { "
        "   background-color: #45a049; "
        "} "
        "QPushButton:pressed { "
        "   background-color: #3d8b40; "
        "}"
    );
    mainLayout->addWidget(addTaskButton);
    
    addMoodButton = new QPushButton("💭 Log Mood Entry", this);
    addMoodButton->setStyleSheet(
        "QPushButton { "
        "   background-color: #2196F3; "
        "   color: white; "
        "   border: none; "
        "   padding: 15px; "
        "   font-size: 16px; "
        "   border-radius: 8px; "
        "   min-height: 50px; "
        "} "
        "QPushButton:hover { "
        "   background-color: #1976D2; "
        "} "
        "QPushButton:pressed { "
        "   background-color: #1565C0; "
        "}"
    );
    mainLayout->addWidget(addMoodButton);
    
    viewTasksButton = new QPushButton("📋 View All Tasks", this);
    viewTasksButton->setStyleSheet(
        "QPushButton { "
        "   background-color: #FF9800; "
        "   color: white; "
        "   border: none; "
        "   padding: 15px; "
        "   font-size: 16px; "
        "   border-radius: 8px; "
        "   min-height: 50px; "
        "} "
        "QPushButton:hover { "
        "   background-color: #F57C00; "
        "} "
        "QPushButton:pressed { "
        "   background-color: #EF6C00; "
        "}"
    );
    mainLayout->addWidget(viewTasksButton);
    
    // Add some spacing
    mainLayout->addSpacing(20);
    
    // Create task display section
    QGroupBox *taskGroup = new QGroupBox("Current Tasks", this);
    taskGroup->setStyleSheet(
        "QGroupBox { "
        "   font-weight: bold; "
        "   font-size: 14px; "
        "   border: 2px solid #ddd; "
        "   border-radius: 8px; "
        "   margin-top: 10px; "
        "   padding-top: 10px; "
        "} "
        "QGroupBox::title { "
        "   subcontrol-origin: margin; "
        "   left: 10px; "
        "   padding: 0 5px 0 5px; "
        "   color: #4A90E2; "
        "}"
    );
    
    QVBoxLayout *taskLayout = new QVBoxLayout(taskGroup);
    
    // Add refresh button
    refreshTasksButton = new QPushButton("🔄 Refresh Tasks", this);
    refreshTasksButton->setStyleSheet(
        "QPushButton { "
        "   background-color: #9C27B0; "
        "   color: white; "
        "   border: none; "
        "   padding: 8px; "
        "   font-size: 12px; "
        "   border-radius: 6px; "
        "   max-width: 120px; "
        "} "
        "QPushButton:hover { "
        "   background-color: #7B1FA2; "
        "}"
    );
    
    QHBoxLayout *refreshLayout = new QHBoxLayout();
    refreshLayout->addWidget(refreshTasksButton);
    refreshLayout->addStretch();
    taskLayout->addLayout(refreshLayout);
    
    // Add task list widget
    taskListWidget = new QListWidget(this);
    taskListWidget->setStyleSheet(
        "QListWidget { "
        "   border: 1px solid #ccc; "
        "   border-radius: 4px; "
        "   padding: 5px; "
        "   background-color: #fafafa; "
        "   min-height: 200px; "
        "}"
    );
    taskLayout->addWidget(taskListWidget);
    
    mainLayout->addWidget(taskGroup);
    
    // Add some spacing at the bottom
    mainLayout->addStretch();
    
    // Connect button signals
    connect(addTaskButton, &QPushButton::clicked, this, &MainWindow::onAddTaskClicked);
    connect(addMoodButton, &QPushButton::clicked, this, &MainWindow::onAddMoodClicked);
    connect(viewTasksButton, &QPushButton::clicked, this, &MainWindow::onViewTasksClicked);
    connect(refreshTasksButton, &QPushButton::clicked, this, &MainWindow::onViewTasksClicked);
    
    // Connect task list signals
    connectTaskSignals();
}

void MainWindow::createMenuBar()
{
    QMenuBar *menuBar = this->menuBar();
    
    // File menu
    QMenu *fileMenu = menuBar->addMenu("&File");
    QAction *exitAction = fileMenu->addAction("E&xit");
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    
    // Help menu
    QMenu *helpMenu = menuBar->addMenu("&Help");
    QAction *aboutAction = helpMenu->addAction("&About");
    connect(aboutAction, &QAction::triggered, [this]() {
        QMessageBox::about(this, "About MooDoo", 
            "MooDoo - Your Mood-Aware Planner\n\n"
            "A mental health-aware planner that adapts to your emotional state, "
            "providing personalized support for people with ADHD and mental health considerations.\n\n"
            "Version 1.0");
    });
}

void MainWindow::onAddTaskClicked()
{
    // Create and show the add task dialog
    AddTaskDialog dialog(storage, this);
    
    // If user added a task successfully, refresh the task list
    if (dialog.exec() == QDialog::Accepted) {
        refreshTaskList();
        statusBar()->showMessage("Task added successfully! 🎉", 3000);
    }
}

void MainWindow::onAddMoodClicked()
{
    QMessageBox::information(this, "Log Mood", "Mood logging functionality coming soon!");
}

void MainWindow::onViewTasksClicked()
{
    QMessageBox::information(this, "View Tasks", "Task viewing functionality coming soon!");
}

void MainWindow::onRefreshTasksClicked()
{
    refreshTaskList();
    statusBar()->showMessage("Tasks refreshed!", 2000);
}

void MainWindow::refreshTaskList()
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
            
            // Add completion status
            if (task.completed) {
                taskText += "✅ ";
            } else {
                taskText += "○ ";
            }
            
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
            
            // Create list item and store task ID as data
            QListWidgetItem* item = new QListWidgetItem(taskText);
            item->setData(Qt::UserRole, task.id);
            taskListWidget->addItem(item);
        }
        
        statusBar()->showMessage(QString("Loaded %1 tasks").arg(tasks.size()), 3000);
    } else {
        taskListWidget->addItem("Error loading tasks");
        statusBar()->showMessage("Error loading tasks", 3000);
    }
}

void MainWindow::connectTaskSignals()
{
    // Connect task list item clicks
    connect(taskListWidget, &QListWidget::itemClicked, this, &MainWindow::onTaskItemClicked);
}

void MainWindow::onTaskItemClicked(QListWidgetItem* item)
{
    if (!item) return;
    
    // Get task ID from item data
    int taskId = item->data(Qt::UserRole).toInt();
    if (taskId == 0) return; // Skip non-task items
    
    // Load current task data
    std::vector<Task> tasks;
    if (!storage->loadTasks(tasks)) {
        statusBar()->showMessage("Error loading tasks", 3000);
        return;
    }
    
    // Find the clicked task
    Task* clickedTask = nullptr;
    for (auto& task : tasks) {
        if (task.id == taskId) {
            clickedTask = &task;
            break;
        }
    }
    
    if (!clickedTask) {
        statusBar()->showMessage("Task not found", 3000);
        return;
    }
    
    // Toggle completion status
    bool newStatus = !clickedTask->completed;
    updateTaskCompletion(taskId, newStatus);
}

void MainWindow::updateTaskCompletion(int taskId, bool completed)
{
    // Load current task data
    std::vector<Task> tasks;
    if (!storage->loadTasks(tasks)) {
        statusBar()->showMessage("Error loading tasks", 3000);
        return;
    }
    
    // Find and update the task
    for (auto& task : tasks) {
        if (task.id == taskId) {
            task.completed = completed;
            task.completed_time = completed ? time(nullptr) : 0;
            
            // Update the task in storage
            if (storage->updateTask(task)) {
                statusBar()->showMessage(
                    completed ? "Task marked as complete! 🎉" : "Task marked as incomplete",
                    3000
                );
                
                // Refresh the display to show the change
                refreshTaskList();
            } else {
                statusBar()->showMessage("Error updating task", 3000);
            }
            return;
        }
    }
    
    statusBar()->showMessage("Task not found", 3000);
} 