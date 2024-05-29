#include "widgetadmin.h"
#include "ui_widgetadmin.h"

#include "dbhandler.h"

WidgetAdmin::WidgetAdmin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetAdmin)
{
    ui->setupUi(this);
}

WidgetAdmin::~WidgetAdmin()
{
    delete ui;
}

void WidgetAdmin::initUI()
{
    //从数据库获取科目列表
    QStringList subjects= DBHandler::instance()->getSubjectList();
    ui->comboBoxSubject->clear();
    ui->comboBoxSubject->addItem(QString());
    ui->comboBoxSubject->addItems(subjects);

    show();
}

void WidgetAdmin::on_comboBoxSubject_currentTextChanged(const QString &text)
{
    int subjectID = DBHandler::instance()->getSubjectID(text);
    QStringList chapters = DBHandler::instance()->getChapterList(subjectID);
    ui->comboBoxChapter->clear();
    ui->comboBoxChapter->addItems(chapters);
}

