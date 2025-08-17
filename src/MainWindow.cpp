#include "MainWindow.h"
#include <QApplication>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("MooDoo - Your Mood-Aware Planner");
    setMinimumSize(800, 600);
    
    setupUI();
    createMenuBar();
    
    // Set status bar
    statusBar()->showMessage("Ready");
}

MainWindow::~MainWindow()
{
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
    
    // Add some spacing at the bottom
    mainLayout->addStretch();
    
    // Connect button signals
    connect(addTaskButton, &QPushButton::clicked, this, &MainWindow::onAddTaskClicked);
    connect(addMoodButton, &QPushButton::clicked, this, &MainWindow::onAddMoodClicked);
    connect(viewTasksButton, &QPushButton::clicked, this, &MainWindow::onViewTasksClicked);
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
    QMessageBox::information(this, "Add Task", "Add Task functionality coming soon!");
}

void MainWindow::onAddMoodClicked()
{
    QMessageBox::information(this, "Log Mood", "Mood logging functionality coming soon!");
}

void MainWindow::onViewTasksClicked()
{
    QMessageBox::information(this, "View Tasks", "Task viewing functionality coming soon!");
} 