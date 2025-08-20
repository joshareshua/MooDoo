#include "AddTaskDialog.h"
#include <QMessageBox>

AddTaskDialog::AddTaskDialog(Storage* storage, QWidget *parent)
    : QDialog(parent), storage(storage)
{
    setWindowTitle("Add New Task");
    setFixedSize(400, 300);
    setModal(true);
    
    setupUI();
}

AddTaskDialog::~AddTaskDialog()
{
}

void AddTaskDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    
    // Title input
    QLabel *titleLabel = new QLabel("Task Title:", this);
    titleLabel->setStyleSheet("font-weight: bold; font-size: 14px;");
    mainLayout->addWidget(titleLabel);
    
    titleEdit = new QLineEdit(this);
    titleEdit->setPlaceholderText("Enter task title...");
    titleEdit->setStyleSheet(
        "QLineEdit { "
        "   padding: 8px; "
        "   border: 2px solid #ddd; "
        "   border-radius: 6px; "
        "   font-size: 14px; "
        "} "
        "QLineEdit:focus { "
        "   border-color: #4A90E2; "
        "}"
    );
    mainLayout->addWidget(titleEdit);
    
    // Description input
    QLabel *descLabel = new QLabel("Description:", this);
    descLabel->setStyleSheet("font-weight: bold; font-size: 14px;");
    mainLayout->addWidget(descLabel);
    
    descriptionEdit = new QTextEdit(this);
    descriptionEdit->setPlaceholderText("Enter task description (optional)...");
    descriptionEdit->setMaximumHeight(80);
    descriptionEdit->setStyleSheet(
        "QTextEdit { "
        "   padding: 8px; "
        "   border: 2px solid #ddd; "
        "   border-radius: 6px; "
        "   font-size: 14px; "
        "} "
        "QTextEdit:focus { "
        "   border-color: #4A90E2; "
        "}"
    );
    mainLayout->addWidget(descriptionEdit);
    
    // Priority and Difficulty row
    QHBoxLayout *optionsLayout = new QHBoxLayout();
    
    // Priority
    QVBoxLayout *priorityLayout = new QVBoxLayout();
    QLabel *priorityLabel = new QLabel("Priority:", this);
    priorityLabel->setStyleSheet("font-weight: bold; font-size: 14px;");
    priorityLayout->addWidget(priorityLabel);
    
    priorityCombo = new QComboBox(this);
    priorityCombo->addItem("🟢 Low", 1);
    priorityCombo->addItem("🟡 Medium", 2);
    priorityCombo->addItem("🔴 High", 3);
    priorityCombo->setCurrentIndex(1); // Default to Medium
    priorityCombo->setStyleSheet(
        "QComboBox { "
        "   padding: 8px; "
        "   border: 2px solid #ddd; "
        "   border-radius: 6px; "
        "   font-size: 14px; "
        "   min-width: 120px; "
        "}"
    );
    priorityLayout->addWidget(priorityCombo);
    optionsLayout->addLayout(priorityLayout);
    
    // Difficulty
    QVBoxLayout *difficultyLayout = new QVBoxLayout();
    QLabel *difficultyLabel = new QLabel("Difficulty:", this);
    difficultyLabel->setStyleSheet("font-weight: bold; font-size: 14px;");
    difficultyLayout->addWidget(difficultyLabel);
    
    difficultyCombo = new QComboBox(this);
    difficultyCombo->addItem("📚 Easy", 1);
    difficultyCombo->addItem("📝 Medium", 2);
    difficultyCombo->addItem("💪 Hard", 3);
    difficultyCombo->setCurrentIndex(1); // Default to Medium
    difficultyCombo->setStyleSheet(
        "QComboBox { "
        "   padding: 8px; "
        "   border: 2px solid #ddd; "
        "   border-radius: 6px; "
        "   font-size: 14px; "
        "   min-width: 120px; "
        "}"
    );
    difficultyLayout->addWidget(difficultyCombo);
    optionsLayout->addLayout(difficultyLayout);
    
    mainLayout->addLayout(optionsLayout);
    
    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    
    cancelButton = new QPushButton("Cancel", this);
    cancelButton->setStyleSheet(
        "QPushButton { "
        "   background-color: #666; "
        "   color: white; "
        "   border: none; "
        "   padding: 10px 20px; "
        "   font-size: 14px; "
        "   border-radius: 6px; "
        "   min-width: 80px; "
        "} "
        "QPushButton:hover { "
        "   background-color: #555; "
        "}"
    );
    buttonLayout->addWidget(cancelButton);
    
    addButton = new QPushButton("Add Task", this);
    addButton->setStyleSheet(
        "QPushButton { "
        "   background-color: #4CAF50; "
        "   color: white; "
        "   border: none; "
        "   padding: 10px 20px; "
        "   font-size: 14px; "
        "   border-radius: 6px; "
        "   min-width: 100px; "
        "} "
        "QPushButton:hover { "
        "   background-color: #45a049; "
        "}"
    );
    buttonLayout->addWidget(addButton);
    
    mainLayout->addLayout(buttonLayout);
    
    // Connect signals
    connect(addButton, &QPushButton::clicked, this, &AddTaskDialog::onAddTaskClicked);
    connect(cancelButton, &QPushButton::clicked, this, &AddTaskDialog::onCancelClicked);
    
    // Set focus to title field
    titleEdit->setFocus();
}

void AddTaskDialog::onAddTaskClicked()
{
    // Get input values
    QString title = titleEdit->text().trimmed();
    QString description = descriptionEdit->toPlainText().trimmed();
    
    // Validate title
    if (title.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Please enter a task title.");
        titleEdit->setFocus();
        return;
    }
    
    // Create task object
    Task task;
    task.id = storage->getNextTaskId();
    task.title = title.toStdString();
    task.description = description.toStdString();
    task.priority = static_cast<Priority>(priorityCombo->currentData().toInt());
    task.difficulty = static_cast<TaskDifficulty>(difficultyCombo->currentData().toInt());
    task.completed = false;
    task.created = time(nullptr);
    task.completed_time = 0;
    
    // Save task using existing backend
    if (storage->saveTask(task)) {
        QMessageBox::information(this, "Success", "Task added successfully! 🎉");
        accept(); // Close dialog
    } else {
        QMessageBox::critical(this, "Error", "Failed to save task. Please try again.");
    }
}

void AddTaskDialog::onCancelClicked()
{
    reject(); // Close dialog
} 