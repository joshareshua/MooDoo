#ifndef MOODENTRYDIALOG_H
#define MOODENTRYDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include "Storage.h"

class MoodEntryDialog : public QDialog
{
    Q_OBJECT

public:
    MoodEntryDialog(Storage* storage, QWidget* parent = nullptr);

private slots:
    void onSaveMoodClicked();
    void onCancelClicked();

private:
    void setupUI();
    
    // UI elements
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QLabel *moodLabel;
    QComboBox *moodComboBox;
    QLabel *contentLabel;
    QTextEdit *contentTextEdit;
    QHBoxLayout *buttonLayout;
    QPushButton *saveButton;
    QPushButton *cancelButton;
    
    // Storage
    Storage *storage;
};

#endif // MOODENTRYDIALOG_H
