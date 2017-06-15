#pragma once

#include <QDialog>

#include "../manager/manager.h"

class QLineEdit;
class QGroupBox;
class QStackedWidget;
class QCalendarWidget;

class AddStudentDialog : public QDialog
{
    Q_OBJECT
public:
    AddStudentDialog(const StudentDatabase &db, DatabaseManager *mng, QWidget *parent);

    void setManager(DatabaseManager *value);

public slots:
    void addStudentToDatabase();
    void notifyInvalidInput();
    void notifyDuplication();

private:
    void manageButtons();
    void manageLayouts();
    void manageDateSwitcher();

    QLineEdit *firstNameInput;
    QLineEdit *secondNameInput;
    QLineEdit *middleNameInput;

    QGroupBox *dateSwitcher;
    QStackedWidget *dates;
    QCalendarWidget *birthDateInput;
    QCalendarWidget *enrollDateInput;
    QCalendarWidget *graduateDateInput;

    QPushButton *ok;
    QPushButton *cancel;

    DatabaseManager *manager;
    const StudentDatabase &database;
};
