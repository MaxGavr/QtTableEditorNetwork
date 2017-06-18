#include "table.h"
#include "../manager/manager.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

MultipageTable::MultipageTable(DatabaseManager *manager, QWidget *parent)
    : QWidget(parent), currentPage(0), incomingPage(0)
{
    setManager(manager);

    initTable();

    createPageControl();
    manageLayouts();

    setStudentsPerPage(DEFAULT_STUDENTS_PER_PAGE);
    //goToFirstPage();

    enforceEmpty(false);
    //requestPage();
//    connect(&database, SIGNAL(studentAdded()), this, SLOT(getPage()));
//    connect(&database, SIGNAL(studentDeleted()), this, SLOT(getPage()));
//    connect(&database, SIGNAL(studentsDeleted(int)), this, SLOT(getPage()));

//    connect(&database, SIGNAL(studentAdded()), this, SLOT(updatePageLabel()));
//    connect(&database, SIGNAL(studentDeleted()), this, SLOT(updatePageLabel()));
//    connect(&database, SIGNAL(studentsDeleted(int)), this, SLOT(updatePageLabel()));
}

void MultipageTable::requestPage()
{
    connect(m_manager, SIGNAL(pageRetrieved(Student::StudentSet)),
            this, SLOT(receivePage(Student::StudentSet)));
    getManager()->getPage(getCurrentPage(), getStudentsPerPage());
}

void MultipageTable::receivePage(Student::StudentSet page)
{
    disconnect(m_manager, SIGNAL(pageRetrieved(Student::StudentSet)),
               this, SLOT(receivePage(Student::StudentSet)));
    if (!isEnforcedEmpty())
    {
        clearTable();
        m_students = page;
        foreach (Student::const_ref student, m_students)
        {
            writeStudentInTable(student, m_students.indexOf(student));
        }
    }
}

void MultipageTable::requestPageLabelUpdate()
{
    connect(m_manager, SIGNAL(pageCounted(int)), this, SLOT(updatePageLabel(int)));
    getManager()->countPages(getStudentsPerPage());
}

void MultipageTable::updatePageLabel(int pageCount)
{
    disconnect(m_manager, SIGNAL(pageCounted(int)), this, SLOT(updatePageLabel(int)));
    if (!isEmpty())
    {
        QString text = QString::number(getCurrentPage() + 1) + "/" + QString::number(pageCount);
        currentPageLabel->setText(text);
    }
    else
        currentPageLabel->setText("/");
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

DatabaseManager *MultipageTable::getManager() const
{
    return m_manager;
}

void MultipageTable::setManager(DatabaseManager *manager)
{
    m_manager = manager;
    if (m_manager)
    {
        connect(m_manager, SIGNAL(databaseUpdated()), this, SLOT(requestPage()));
        connect(m_manager, SIGNAL(pageRetrieved(Student::StudentSet)), this, SLOT(requestPageLabelUpdate()));
    }
}

void MultipageTable::requestPageChange(int pageIndex)
{
    incomingPage = pageIndex;
    connect(m_manager, SIGNAL(pageValidated(bool)), this, SLOT(setCurrentPage(bool)));
    getManager()->validatePageBounds(pageIndex, getStudentsPerPage());
}

void MultipageTable::setCurrentPage(bool isPageValid)
{
    disconnect(m_manager, SIGNAL(pageValidated(bool)), this, SLOT(setCurrentPage(bool)));
    disconnect(m_manager, SIGNAL(pageCounted(int)), this, SLOT(requestPageChange(int)));
    if (isPageValid)
    {
        currentPage = incomingPage;
        requestPage();
    }
    requestPageLabelUpdate();
}

void MultipageTable::updateStudentsPerPage()
{
    setStudentsPerPage(pageSizeInput->text().toInt());
}

void MultipageTable::goToFirstPage()
{
    requestPageChange(0);
}

void MultipageTable::goToLastPage()
{
    connect(m_manager, SIGNAL(pageCounted(int)), this, SLOT(requestPageChange(int)));
    getManager()->countPages(getStudentsPerPage());
    //requestPageChange(maxPages() - 1);
}

void MultipageTable::goToPreviousPage()
{
    if (getCurrentPage() - 1 >= 0)
        requestPageChange(getCurrentPage() - 1);
}

void MultipageTable::goToNextPage()
{
    requestPageChange(getCurrentPage() + 1);
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
    m_students.clear();
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
    return m_students.count();
}
