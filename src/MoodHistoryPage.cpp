#include "MoodHistoryPage.h"
#include <QDateTime>

MoodHistoryPage::MoodHistoryPage(Storage* storage, QWidget *parent)
    : QWidget(parent), storage(storage)
{
    setWindowTitle("Mood History");
    setFixedSize(600, 500);
    setWindowFlags(Qt::Window);
    
    setupUI();
}

MoodHistoryPage::~MoodHistoryPage()
{
}

void MoodHistoryPage::setupUI()
{
    mainLayout = new QVBoxLayout(this);
    
    // Title
    titleLabel = new QLabel("💭 Your Mood History", this);
    titleLabel->setStyleSheet(
        "QLabel { "
        "   font-size: 24px; "
        "   font-weight: bold; "
        "   color: #2196F3; "
        "   margin-bottom: 20px; "
        "   text-align: center;"
        "}"
    );
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);
    
    // Mood list
    moodListWidget = new QListWidget(this);
    moodListWidget->setStyleSheet(
        "QListWidget { "
        "   border: 2px solid #ddd; "
        "   border-radius: 8px; "
        "   padding: 10px; "
        "   background-color: #fafafa; "
        "   color: #333; "
        "   font-size: 14px; "
        "   min-height: 300px; "
        "}"
        "QListWidget::item { "
        "   color: #333; "
        "   padding: 8px; "
        "   border-bottom: 1px solid #eee; "
        "}"
        "QListWidget::item:selected { "
        "   background-color: #e3f2fd; "
        "   color: #1976d2; "
        "}"
    );
    mainLayout->addWidget(moodListWidget);
    
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
    refreshButton = new QPushButton("🔄 Refresh Moods", this);
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
    connect(backButton, &QPushButton::clicked, this, &MoodHistoryPage::onBackClicked);
    connect(refreshButton, &QPushButton::clicked, this, &MoodHistoryPage::onRefreshClicked);
    
    // Load initial data
    refreshMoodList();
}

void MoodHistoryPage::refreshMoodList()
{
    moodListWidget->clear();
    
    std::vector<MoodEntry> moods;
    if (storage->loadMoodEntries(moods)) {
        if (moods.empty()) {
            moodListWidget->addItem("No mood entries found. Start logging your moods!");
            return;
        }
        
        for (const auto& mood : moods) {
            QString moodText;
            
            // Add mood emoji
            switch(mood.mood) {
                case MoodLevel::VERY_LOW: moodText += "😢 "; break;
                case MoodLevel::LOW: moodText += "😕 "; break;
                case MoodLevel::NEUTRAL: moodText += "😐 "; break;
                case MoodLevel::GOOD: moodText += "😊 "; break;
                case MoodLevel::EXCELLENT: moodText += "😄 "; break;
            }
            
            // Add mood level text
            switch(mood.mood) {
                case MoodLevel::VERY_LOW: moodText += "Very Low"; break;
                case MoodLevel::LOW: moodText += "Low"; break;
                case MoodLevel::NEUTRAL: moodText += "Neutral"; break;
                case MoodLevel::GOOD: moodText += "Good"; break;
                case MoodLevel::EXCELLENT: moodText += "Excellent"; break;
            }
            
            // Add timestamp
            QDateTime dateTime = QDateTime::fromSecsSinceEpoch(mood.timestamp);
            moodText += " - " + dateTime.toString("MMM dd, h:mm AP");
            
            // Add content preview (first 50 chars)
            QString content = QString::fromStdString(mood.content);
            if (content.length() > 50) {
                content = content.left(50) + "...";
            }
            moodText += "\n   " + content;
            
            moodListWidget->addItem(moodText);
        }
    } else {
        moodListWidget->addItem("Error loading mood entries");
    }
}

void MoodHistoryPage::onBackClicked()
{
    close();
}

void MoodHistoryPage::onRefreshClicked()
{
    refreshMoodList();
}
