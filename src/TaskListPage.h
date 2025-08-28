#ifndef TASKLISTPAGE_H
#define TASKLISTPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QComboBox>
#include <QLineEdit>
#include "Storage.h"

class TaskListPage : public QWidget
{
    Q_OBJECT

public:
    TaskListPage(Storage* storage, QWidget *parent = nullptr);
    ~TaskListPage();

public slots:
    void onBackClicked();
    void onRefreshClicked();
    void refreshTaskList();
    void onPriorityFilterChanged(int index);
    void onSearchTextChanged(const QString& text);

private:
    void setupUI();
    
    // UI elements
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QListWidget *taskListWidget;
    QPushButton *refreshButton;
    QPushButton *backButton;
    
    // Storage connection
    Storage *storage;
};

#endif // TASKLISTPAGE_H 