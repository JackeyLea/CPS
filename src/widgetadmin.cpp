#include "widgetadmin.h"
#include "ui_widgetadmin.h"

#include "dbhandler.h"
#include "addquestion.h"

WidgetAdmin::WidgetAdmin(int userID, int right, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetAdmin)
    ,m_pAddQ(NULL)
    ,m_iUserID(userID)
    ,m_bIsAdmin(right)
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

    //TODO 不同权限编辑内容不同
    if(m_bIsAdmin){
        //如果是管理员状态，用户界面可以用
        ui->btnUserEdit->setEnabled(true);
        ui->btnUserDelete->setEnabled(true);
        ui->btnQEdit->setEnabled(true);
        ui->btnAddQ->setEnabled(true);
    }else{
        ui->btnUserEdit->setEnabled(false);
        ui->btnUserDelete->setEnabled(false);
        ui->btnQEdit->setEnabled(false);
        ui->btnAddQ->setEnabled(false);
    }

    show();
}

void WidgetAdmin::setUserID(int userid)
{
    m_iUserID = userid;
}

void WidgetAdmin::setRight(int right)
{
    m_bIsAdmin = right;
}

void WidgetAdmin::on_comboBoxSubject_currentTextChanged(const QString &text)
{
    if(text.isEmpty()) return;
    int subjectID = DBHandler::instance()->getSubjectID(text);
    QStringList chapters = DBHandler::instance()->getChapterList(subjectID);
    ui->comboBoxChapter->clear();
    if(chapters.count()>0){
        ui->comboBoxChapter->addItems(chapters);
    }
}

void WidgetAdmin::on_btnAddQ_clicked()
{
    if(!m_pAddQ){
        m_pAddQ = new AddQuestion();
    }
    m_pAddQ->show();
}

