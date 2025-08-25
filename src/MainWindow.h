#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QPushButton>
#include "Storage.h"
#include "AddTaskDialog.h"
#include "MoodEntryDialog.h"
#include "MoodHistoryPage.h"
#include "TaskListPage.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddTaskClicked();
    void onAddMoodClicked();
    void onViewMoodHistoryClicked();
    void onViewTasksClicked();
private:
    void setupUI();
    void createMenuBar();
    
    // UI elements
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QLabel *subtitleLabel;
    QPushButton *addTaskButton;
    QPushButton *addMoodButton;
    QPushButton *viewTasksButton;
    
    // Storage
    Storage *storage;
    
    // Pages
    TaskListPage *taskListPage;
    MoodHistoryPage *moodHistoryPage;
};

#endif // MAINWINDOW_H 