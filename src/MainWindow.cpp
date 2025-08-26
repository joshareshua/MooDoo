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
    
    // Task list page will load tasks when needed
    
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
    
    // Statistics section
    QLabel *statsLabel = new QLabel("📊 Your Progress", this);
    statsLabel->setStyleSheet(
        "QLabel { "
        "   font-size: 18px; "
        "   font-weight: bold; "
        "   color: #666; "
        "   margin-bottom: 15px; "
        "   text-align: center;"
        "}"
    );
    statsLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(statsLabel);
    
    // Stats display
    QLabel *statsDisplay = new QLabel("Loading statistics...", this);
    statsDisplay->setObjectName("statsDisplay");
    statsDisplay->setStyleSheet(
        "QLabel { "
        "   background-color: #f8f9fa; "
        "   border: 2px solid #e9ecef; "
        "   border-radius: 8px; "
        "   padding: 15px; "
        "   font-size: 14px; "
        "   color: #495057; "
        "   text-align: center; "
        "   margin-bottom: 20px;"
        "}"
    );
    statsDisplay->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(statsDisplay);
    
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
    
    // Add mood history button
    QPushButton *viewMoodHistoryButton = new QPushButton("📊 View Mood History", this);
    viewMoodHistoryButton->setStyleSheet(
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
    mainLayout->addWidget(viewMoodHistoryButton);
    
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
    
    // Create pages (hidden initially)
    taskListPage = new TaskListPage(storage, this);
    taskListPage->hide();
    moodHistoryPage = new MoodHistoryPage(storage, this);
    moodHistoryPage->hide();
    
    // Add some spacing at the bottom
    mainLayout->addStretch();
    
    // Connect button signals
    connect(addTaskButton, &QPushButton::clicked, this, &MainWindow::onAddTaskClicked);
    connect(addMoodButton, &QPushButton::clicked, this, &MainWindow::onAddMoodClicked);
    connect(viewMoodHistoryButton, &QPushButton::clicked, this, &MainWindow::onViewMoodHistoryClicked);
    connect(viewTasksButton, &QPushButton::clicked, this, &MainWindow::onViewTasksClicked);
    
    // Update statistics initially
    updateStatistics();
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
    
    // If user added a task successfully, show success message and update stats
    if (dialog.exec() == QDialog::Accepted) {
        statusBar()->showMessage("Task added successfully! 🎉", 3000);
        updateStatistics();
    }
}

void MainWindow::onAddMoodClicked()
{
    // Create and show the mood entry dialog
    MoodEntryDialog dialog(storage, this);
    
    // If user added a mood entry successfully, show success message and update stats
    if (dialog.exec() == QDialog::Accepted) {
        statusBar()->showMessage("Mood entry logged successfully! 💚", 3000);
        updateStatistics();
    }
}

void MainWindow::onViewTasksClicked()
{
    // Show task list page as a separate window
    taskListPage->show();
    taskListPage->raise();
    taskListPage->refreshTaskList();
}

void MainWindow::onViewMoodHistoryClicked()
{
    // Show mood history page as a separate window
    moodHistoryPage->show();
    moodHistoryPage->raise();
    moodHistoryPage->refreshMoodList();
}

void MainWindow::updateStatistics()
{
    // Get task statistics
    std::vector<Task> tasks;
    int totalTasks = 0, completedTasks = 0, pendingTasks = 0;
    if (storage->loadTasks(tasks)) {
        totalTasks = tasks.size();
        for (const auto& task : tasks) {
            if (task.completed) {
                completedTasks++;
            } else {
                pendingTasks++;
            }
        }
    }
    
    // Get mood statistics
    std::vector<MoodEntry> moods;
    int totalMoods = 0;
    if (storage->loadMoodEntries(moods)) {
        totalMoods = moods.size();
    }
    
    // Create statistics text
    QString statsText = QString("📋 Tasks: %1 total (%2 pending, %3 completed)\n"
                               "💭 Moods: %4 entries logged")
                               .arg(totalTasks)
                               .arg(pendingTasks)
                               .arg(completedTasks)
                               .arg(totalMoods);
    
    // Update the display
    QLabel *statsDisplay = findChild<QLabel*>("statsDisplay");
    if (statsDisplay) {
        statsDisplay->setText(statsText);
    }
} 