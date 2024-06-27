#include "widgetadmin.h"
#include "ui_widgetadmin.h"

#include <QStandardItemModel>
#include <QStandardItem>

#include "dbhandler.h"
#include "addquestion.h"

WidgetAdmin::WidgetAdmin(int userID, int right, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetAdmin)
    ,m_pAddQ(NULL)
    ,m_mUserModel(NULL)
    ,m_mItemModel(NULL)
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

    if(!m_mItemModel){
        m_mItemModel = new QStandardItemModel();
        ui->tableViewQ->setModel(m_mItemModel);
    }
    if(!m_mUserModel){
        m_mUserModel = new QStandardItemModel();
        ui->tableViewUser->setModel(m_mUserModel);
    }

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

    //设置问题表 默认情况下显示每个科目有多少题
    m_mItemModel->clear();
    m_mItemModel->setColumnCount(2);
    m_mItemModel->setHorizontalHeaderItem(0,new QStandardItem("科目"));
    m_mItemModel->setHorizontalHeaderItem(1,new QStandardItem("题数"));
    for(int i=0;i<subjects.count();i++){
        m_mItemModel->setItem(i,0,new QStandardItem(subjects.at(i)));
        int subjectID = DBHandler::instance()->getSubjectID(subjects.at(i));
        int qcnt = DBHandler::instance()->getQCntSubject(subjectID);
        m_mItemModel->setItem(i,1,new QStandardItem(QString::number(qcnt)));
    }

    //设置用户表
    m_mUserModel->clear();
    m_mUserModel->setColumnCount(2);
    m_mUserModel->setHorizontalHeaderItem(0,new QStandardItem("用户名"));
    m_mUserModel->setHorizontalHeaderItem(1,new QStandardItem("密码"));

    //填充用户表数据

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
    //显示当前科目所对应的章节列表
    if(text.isEmpty()) return;
    int subjectID = DBHandler::instance()->getSubjectID(text);
    QStringList chapters = DBHandler::instance()->getChapterList(subjectID);
    ui->comboBoxChapter->clear();
    if(chapters.count()>0){
        ui->comboBoxChapter->addItem(QString());
        ui->comboBoxChapter->addItems(chapters);
    }
    //显示当前科目所有章节的题目数
    m_mItemModel->clear();
    m_mItemModel->setColumnCount(3);
    m_mItemModel->setHorizontalHeaderItem(0,new QStandardItem("科目"));
    m_mItemModel->setHorizontalHeaderItem(1,new QStandardItem("章节"));
    m_mItemModel->setHorizontalHeaderItem(2,new QStandardItem("数据"));
    for(int i=0;i<chapters.count();i++){
        m_mItemModel->setItem(i,0,new QStandardItem(text));
        m_mItemModel->setItem(i,1,new QStandardItem(chapters.at(i)));
        //获取章节对应数据
        int chapterID = DBHandler::instance()->getChapterID(subjectID,chapters.at(i));
        int qcnt = DBHandler::instance()->getQCntSubjectChapter(subjectID,chapterID);
        m_mItemModel->setItem(i,2,new QStandardItem(QString::number(qcnt)));
    }
}

void WidgetAdmin::on_btnAddQ_clicked()
{
    if(!m_pAddQ){
        m_pAddQ = new AddQuestion();
    }
    m_pAddQ->show();
}

void WidgetAdmin::on_comboBoxChapter_currentTextChanged(const QString &text)
{
    //显示当前科目当前章节的题目
    m_mItemModel->clear();
    m_mItemModel->setColumnCount(3);
    m_mItemModel->setHorizontalHeaderItem(0,new QStandardItem("科目"));
    m_mItemModel->setHorizontalHeaderItem(1,new QStandardItem("章节"));
    m_mItemModel->setHorizontalHeaderItem(2,new QStandardItem("描述"));
    m_mItemModel->setHorizontalHeaderItem(3,new QStandardItem("A"));
    m_mItemModel->setHorizontalHeaderItem(4,new QStandardItem("B"));
    m_mItemModel->setHorizontalHeaderItem(5,new QStandardItem("C"));
    m_mItemModel->setHorizontalHeaderItem(6,new QStandardItem("D"));
    m_mItemModel->setHorizontalHeaderItem(7,new QStandardItem("参考答案"));
    m_mItemModel->setHorizontalHeaderItem(8,new QStandardItem("答案解析"));

    //获取科目ID
    int subjectID = DBHandler::instance()->getSubjectID(ui->comboBoxSubject->currentText());
    //获取章节ID
    int chapterID = DBHandler::instance()->getChapterID(subjectID,text);
    //获取起始ID
    QList<int> idList = DBHandler::instance()->getIDListSubjectChapter(subjectID,chapterID);
    for(int i=0;i<idList.count();i++){
        m_mItemModel->setItem(i,0,new QStandardItem(ui->comboBoxSubject->currentText()));
        m_mItemModel->setItem(i,1,new QStandardItem(text));
        //获取题目数据
        Question q = DBHandler::instance()->getQuestionInfo(subjectID,chapterID,idList.at(i));
        m_mItemModel->setItem(i,2,new QStandardItem(q.desc));
        m_mItemModel->setItem(i,3,new QStandardItem(q.a));
        m_mItemModel->setItem(i,4,new QStandardItem(q.b));
        m_mItemModel->setItem(i,5,new QStandardItem(q.c));
        m_mItemModel->setItem(i,6,new QStandardItem(q.d));
        m_mItemModel->setItem(i,7,new QStandardItem(QString::number(q.answer)));
        m_mItemModel->setItem(i,8,new QStandardItem(q.explain));
    }
}

