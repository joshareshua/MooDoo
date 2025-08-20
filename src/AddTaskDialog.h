#ifndef ADDTASKDIALOG_H
#define ADDTASKDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include "Storage.h"

class AddTaskDialog : public QDialog
{
    Q_OBJECT

public:
    AddTaskDialog(Storage* storage, QWidget *parent = nullptr);
    ~AddTaskDialog();

private slots:
    void onAddTaskClicked();
    void onCancelClicked();

private:
    void setupUI();
    
    // UI elements
    QLineEdit *titleEdit;
    QTextEdit *descriptionEdit;
    QComboBox *priorityCombo;
    QComboBox *difficultyCombo;
    QPushButton *addButton;
    QPushButton *cancelButton;
    
    // Storage connection
    Storage *storage;
};

#endif // ADDTASKDIALOG_H 