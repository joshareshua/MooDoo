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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddTaskClicked();
    void onAddMoodClicked();
    void onViewTasksClicked();
    void onRefreshTasksClicked();
    void onTaskItemClicked(QListWidgetItem* item);

private:
    void setupUI();
    void createMenuBar();
    void refreshTaskList();
    
    // UI elements
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QLabel *subtitleLabel;
    QPushButton *addTaskButton;
    QPushButton *addMoodButton;
    QPushButton *viewTasksButton;
    
    // Task display
    QListWidget *taskListWidget;
    QPushButton *refreshTasksButton;
    
    // Storage
    Storage *storage;
    
    // Helper methods
    void connectTaskSignals();
    void updateTaskCompletion(int taskId, bool completed);
};

#endif // MAINWINDOW_H 