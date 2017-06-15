#pragma once

#include <QObject>
#include <QTableWidget>
#include <QPushButton>
#include <QHeaderView>
#include <QLineEdit>
#include <QLabel>

#include "../model/student.h"

class MultipageTable : public QWidget
{
    Q_OBJECT
public:
    MultipageTable(QWidget *parent = 0);

    enum TableField { Name = 0, BirthDate, EnrollmentDate, GraduationDate };

    void writeStudentInTable(Student::const_ref student, int row);
    void clearTable();

    void enforceEmpty(bool empty = false);
    bool isEnforcedEmpty() const;
    bool isEmpty() const;

    int countStudents() const;
    int maxPages() const;

    int getStudentsPerPage() const;
    void setStudentsPerPage(int value);

    int getCurrentPage() const;
    void setCurrentPage(int value);

public slots:
    void getPage();
    void updatePageLabel();
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

    QTableWidget *table;
    QPushButton *nextPageButton;
    QPushButton *prevPageButton;
    QPushButton *lastPageButton;
    QPushButton *firstPageButton;
    QLineEdit *pageSizeInput;
    QLabel *currentPageLabel;

    Student::StudentSet students;

    bool enforcedEmpty;
    int currentPage;
    int studentsPerPage;
    const int DEFAULT_STUDENTS_PER_PAGE = 10;
    const int TOTAL_COLUMNS = 4;
};
