#pragma once

#include <QObject>
#include <QDialog>
#include <QPushButton>

#include "searchwidget.h"
#include "../manager/manager.h"

class DeleteStudentDialog : public QDialog
{
    Q_OBJECT
public:
    DeleteStudentDialog(DatabaseManager *mng, QWidget *parent);

    DatabaseManager *getManager();
    void setManager(DatabaseManager *value);

public slots:
    void deleteStudents();

private slots:
    void notifyDeletion(int amount);

private:
    void manageButtons();
    void manageLayouts();

    StudentSearchWidget *searchWidget;
    QPushButton *deleteButton;
    QPushButton *cancelButton;

    DatabaseManager *manager;
};
