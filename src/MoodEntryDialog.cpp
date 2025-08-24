#include "MoodEntryDialog.h"
#include <QMessageBox>
#include <QDateTime>

MoodEntryDialog::MoodEntryDialog(Storage* storage, QWidget* parent)
    : QDialog(parent), storage(storage)
{
    setWindowTitle("Log Mood Entry");
    setFixedSize(500, 400);
    setModal(true);
    
    setupUI();
}

void MoodEntryDialog::setupUI()
{
    mainLayout = new QVBoxLayout(this);
    
    // Title
    titleLabel = new QLabel("💭 How are you feeling?", this);
    titleLabel->setStyleSheet(
        "QLabel { "
        "   font-size: 20px; "
        "   font-weight: bold; "
        "   color: #2196F3; "
        "   margin-bottom: 20px; "
        "   text-align: center;"
        "}"
    );
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);
    
    // Mood level selection
    moodLabel = new QLabel("Mood Level:", this);
    moodLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: #333;");
    mainLayout->addWidget(moodLabel);
    
    moodComboBox = new QComboBox(this);
    moodComboBox->addItem("😢 Very Low", static_cast<int>(MoodLevel::VERY_LOW));
    moodComboBox->addItem("😕 Low", static_cast<int>(MoodLevel::LOW));
    moodComboBox->addItem("😐 Neutral", static_cast<int>(MoodLevel::NEUTRAL));
    moodComboBox->addItem("😊 Good", static_cast<int>(MoodLevel::GOOD));
    moodComboBox->addItem("😄 Excellent", static_cast<int>(MoodLevel::EXCELLENT));
    moodComboBox->setStyleSheet(
        "QComboBox { "
        "   padding: 8px; "
        "   border: 2px solid #ddd; "
        "   border-radius: 6px; "
        "   font-size: 14px; "
        "   background-color: white; "
        "}"
    );
    mainLayout->addWidget(moodComboBox);
    
    // Content entry
    contentLabel = new QLabel("What's on your mind?", this);
    contentLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: #333; margin-top: 15px;");
    mainLayout->addWidget(contentLabel);
    
    contentTextEdit = new QTextEdit(this);
    contentTextEdit->setPlaceholderText("Describe your thoughts, feelings, or what happened today...");
    contentTextEdit->setStyleSheet(
        "QTextEdit { "
        "   border: 2px solid #ddd; "
        "   border-radius: 6px; "
        "   padding: 10px; "
        "   font-size: 14px; "
        "   background-color: white; "
        "}"
    );
    mainLayout->addWidget(contentTextEdit);
    
    // Buttons
    buttonLayout = new QHBoxLayout();
    
    saveButton = new QPushButton("💾 Save Mood Entry", this);
    saveButton->setStyleSheet(
        "QPushButton { "
        "   background-color: #4CAF50; "
        "   color: white; "
        "   border: none; "
        "   padding: 12px 20px; "
        "   font-size: 14px; "
        "   border-radius: 6px; "
        "   min-width: 120px; "
        "} "
        "QPushButton:hover { "
        "   background-color: #45a049; "
        "}"
    );
    buttonLayout->addWidget(saveButton);
    
    buttonLayout->addStretch();
    
    cancelButton = new QPushButton("❌ Cancel", this);
    cancelButton->setStyleSheet(
        "QPushButton { "
        "   background-color: #f44336; "
        "   color: white; "
        "   border: none; "
        "   padding: 12px 20px; "
        "   font-size: 14px; "
        "   border-radius: 6px; "
        "   min-width: 100px; "
        "} "
        "QPushButton:hover { "
        "   background-color: #da190b; "
        "}"
    );
    buttonLayout->addWidget(cancelButton);
    
    mainLayout->addLayout(buttonLayout);
    
    // Connect signals
    connect(saveButton, &QPushButton::clicked, this, &MoodEntryDialog::onSaveMoodClicked);
    connect(cancelButton, &QPushButton::clicked, this, &MoodEntryDialog::onCancelClicked);
}

void MoodEntryDialog::onSaveMoodClicked()
{
    QString content = contentTextEdit->toPlainText().trimmed();
    
    if (content.isEmpty()) {
        QMessageBox::warning(this, "Missing Content", "Please describe how you're feeling!");
        return;
    }
    
    // Create mood entry
    MoodEntry entry;
    entry.content = content.toStdString();
    entry.mood = static_cast<MoodLevel>(moodComboBox->currentData().toInt());
    entry.timestamp = time(nullptr);
    
    // Save to storage
    if (storage->saveMoodEntry(entry)) {
        QMessageBox::information(this, "Success", "Mood entry saved successfully! 💚");
        accept();
    } else {
        QMessageBox::critical(this, "Error", "Failed to save mood entry. Please try again.");
    }
}

void MoodEntryDialog::onCancelClicked()
{
    reject();
}
