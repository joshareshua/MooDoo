#ifndef MOODHISTORYPAGE_H
#define MOODHISTORYPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include "Storage.h"

class MoodHistoryPage : public QWidget
{
    Q_OBJECT

public:
    MoodHistoryPage(Storage* storage, QWidget *parent = nullptr);
    ~MoodHistoryPage();

public slots:
    void onBackClicked();
    void onRefreshClicked();
    void refreshMoodList();

private:
    void setupUI();
    
    // UI elements
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QListWidget *moodListWidget;
    QPushButton *refreshButton;
    QPushButton *backButton;
    
    // Storage connection
    Storage *storage;
};

#endif // MOODHISTORYPAGE_H
