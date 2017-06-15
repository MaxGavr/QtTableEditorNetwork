#include "table.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

MultipageTable::MultipageTable(QWidget *parent)
    : QWidget(parent)
{
    initTable();

    createPageControl();
    manageLayouts();

    setStudentsPerPage(DEFAULT_STUDENTS_PER_PAGE);
    goToFirstPage();

    enforceEmpty(false);
    getPage();
//    connect(&database, SIGNAL(studentAdded()), this, SLOT(getPage()));
//    connect(&database, SIGNAL(studentDeleted()), this, SLOT(getPage()));
//    connect(&database, SIGNAL(studentsDeleted(int)), this, SLOT(getPage()));

//    connect(&database, SIGNAL(studentAdded()), this, SLOT(updatePageLabel()));
//    connect(&database, SIGNAL(studentDeleted()), this, SLOT(updatePageLabel()));
//    connect(&database, SIGNAL(studentsDeleted(int)), this, SLOT(updatePageLabel()));
}

void MultipageTable::getPage()
{
//    if (!isEnforcedEmpty())
//    {
//        clearTable();
//        students = database.getSetOfStudents(getCurrentPage(), getStudentsPerPage());
//        foreach (Student::const_ref student, students)
//        {
//            writeStudentInTable(student, students.indexOf(student));
//        }
//    }
}

void MultipageTable::initTable()
{
    table = new QTableWidget(this);

    table->setColumnCount(TOTAL_COLUMNS);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QTableWidgetItem *firstColumnTitle = new QTableWidgetItem(tr("ФИО"));
    QTableWidgetItem *secondColumnTitle = new QTableWidgetItem(tr("Дата рождения"));
    QTableWidgetItem *thirdColumnTitle = new QTableWidgetItem(tr("Дата поступления"));
    QTableWidgetItem *fourthColumnTitle = new QTableWidgetItem(tr("Дата окончания"));
    table->setHorizontalHeaderItem(0, firstColumnTitle);
    table->setHorizontalHeaderItem(1, secondColumnTitle);
    table->setHorizontalHeaderItem(2, thirdColumnTitle);
    table->setHorizontalHeaderItem(3, fourthColumnTitle);

    fitTableToContents();
}

void MultipageTable::manageLayouts()
{
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch(12);
    buttonLayout->addWidget(firstPageButton, 1);
    buttonLayout->addWidget(prevPageButton, 1);
    buttonLayout->addWidget(pageSizeInput, 1);
    buttonLayout->addWidget(currentPageLabel, 1);
    buttonLayout->addWidget(nextPageButton, 1);
    buttonLayout->addWidget(lastPageButton, 1);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(table);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
}

void MultipageTable::createPageControl()
{
    nextPageButton = new QPushButton(QIcon(":/icons/icon_next_page.png"), QString(), this);
    connect(nextPageButton, SIGNAL(clicked(bool)), this, SLOT(goToNextPage()));
    prevPageButton = new QPushButton(QIcon(":/icons/icon_previous_page.png"), QString(), this);
    connect(prevPageButton, SIGNAL(clicked(bool)), this, SLOT(goToPreviousPage()));
    lastPageButton = new QPushButton(QIcon(":/icons/icon_last_page.png"), QString(), this);
    connect(lastPageButton, SIGNAL(clicked(bool)), this, SLOT(goToLastPage()));
    firstPageButton = new QPushButton(QIcon(":/icons/icon_first_page.png"), QString(), this);
    connect(firstPageButton, SIGNAL(clicked(bool)), this, SLOT(goToFirstPage()));

    pageSizeInput = new QLineEdit(tr("Кол-во записей:"), this);
    QFont font = QFont();
    font.setBold(true);
    pageSizeInput->setFont(font);
    pageSizeInput->setAlignment(Qt::AlignCenter);
    pageSizeInput->setValidator(new QIntValidator(1, 100));
    connect(pageSizeInput, SIGNAL(editingFinished()), this, SLOT(updateStudentsPerPage()));
    currentPageLabel = new QLabel(tr("/"), this);
    currentPageLabel->setFont(font);
    currentPageLabel->setAlignment(Qt::AlignCenter);
}

void MultipageTable::updatePageLabel()
{
    if (!isEmpty())
    {
        QString text = QString::number(getCurrentPage() + 1) + "/" + QString::number(maxPages());
        currentPageLabel->setText(text);
    }
    else
        currentPageLabel->setText("/");
}

void MultipageTable::updateStudentsPerPage()
{
    setStudentsPerPage(pageSizeInput->text().toInt());
}

void MultipageTable::goToFirstPage()
{
    setCurrentPage(0);
}

void MultipageTable::goToLastPage()
{
    setCurrentPage(maxPages() - 1);
}

void MultipageTable::goToPreviousPage()
{
    if (getCurrentPage() - 1 >= 0)
        setCurrentPage(getCurrentPage() - 1);
}

void MultipageTable::goToNextPage()
{
    if (getCurrentPage() + 1 < maxPages())
        setCurrentPage(getCurrentPage() + 1);
}

void MultipageTable::fitTableToContents()
{
    table->resizeColumnsToContents();
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

int MultipageTable::getCurrentPage() const
{
    return currentPage;
}

void MultipageTable::setCurrentPage(int value)
{
//    if (database.validatePageBounds(value, getStudentsPerPage()))
//    {
//        currentPage = value;
//        getPage();
//    }
//    updatePageLabel();
}

int MultipageTable::getStudentsPerPage() const
{
    return studentsPerPage;
}

void MultipageTable::setStudentsPerPage(int value)
{
    studentsPerPage = value;
    pageSizeInput->setText(QString::number(getStudentsPerPage()));
    goToFirstPage();
}

void MultipageTable::writeStudentInTable(Student::const_ref student, int row)
{
    if (table->rowCount() <= row)
        table->insertRow(row);

    QTableWidgetItem *name = new QTableWidgetItem(student.getFullName());
    QTableWidgetItem *birth = new QTableWidgetItem(student.getBirthDateString());
    QTableWidgetItem *enroll = new QTableWidgetItem(student.getEnrollmentDateString());
    QTableWidgetItem *graduate = new QTableWidgetItem(student.getGraduationDateString());

    table->setItem(row, Name, name);
    table->setItem(row, BirthDate, birth);
    table->setItem(row, EnrollmentDate, enroll);
    table->setItem(row, GraduationDate, graduate);

    fitTableToContents();
}

void MultipageTable::clearTable()
{
    students.clear();
    table->clearContents();
    table->setRowCount(0);
}

void MultipageTable::enforceEmpty(bool empty)
{
    enforcedEmpty = empty;
    if (empty)
        clearTable();
}

bool MultipageTable::isEnforcedEmpty() const
{
    return enforcedEmpty;
}

bool MultipageTable::isEmpty() const
{
    return countStudents() == 0;
}

int MultipageTable::countStudents() const
{
    return students.count();
}

int MultipageTable::maxPages() const
{
    //return database.countPages(studentsPerPage);
}
