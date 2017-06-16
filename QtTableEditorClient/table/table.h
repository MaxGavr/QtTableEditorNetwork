#pragma once

#include <QObject>
#include <QTableWidget>
#include <QPushButton>
#include <QHeaderView>
#include <QLineEdit>
#include <QLabel>

#include "../model/student.h"

class DatabaseManager;

class MultipageTable : public QWidget
{
    Q_OBJECT
public:
    MultipageTable(DatabaseManager* manager, QWidget *parent = 0);

    enum TableField { Name = 0, BirthDate, EnrollmentDate, GraduationDate };

    void writeStudentInTable(Student::const_ref student, int row);
    void clearTable();

    void enforceEmpty(bool empty = false);
    bool isEnforcedEmpty() const;
    bool isEmpty() const;

    int countStudents() const;

    int getStudentsPerPage() const;
    void setStudentsPerPage(int value);

    int getCurrentPage() const;

    DatabaseManager *getManager() const;
    void setManager(DatabaseManager *manager);

public slots:
    void requestPage();
    void receivePage(Student::StudentSet page);

    void requestPageLabelUpdate();
    void updatePageLabel(int pageCount);

    void requestPageChange(int pageIndex);
    void setCurrentPage(bool isPageValid);

    void updateStudentsPerPage();

    void goToFirstPage();
    void goToLastPage();
    void goToPreviousPage();
    void goToNextPage();

private:
    void initTable();
    void fitTableToContents();

    void manageLayouts();

    void createPageControl();

    DatabaseManager* m_manager;

    QTableWidget *table;
    QPushButton *nextPageButton;
    QPushButton *prevPageButton;
    QPushButton *lastPageButton;
    QPushButton *firstPageButton;
    QLineEdit *pageSizeInput;
    QLabel *currentPageLabel;

    Student::StudentSet m_students;

    bool enforcedEmpty;
    int currentPage;
    int incomingPage;
    int studentsPerPage;
    const int DEFAULT_STUDENTS_PER_PAGE = 10;
    const int TOTAL_COLUMNS = 4;
};
