#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

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
};

#endif // MAINWINDOW_H 