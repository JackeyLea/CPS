#include "chapterexercisesetup.h"
#include "ui_chapterexercisesetup.h"

#include "dbhandler.h"
#include "chapterexercise.h"

#include <QDebug>
#include <QMessageBox>

ChapterExerciseSetup::ChapterExerciseSetup(int userId, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChapterExerciseSetup)
    ,ce(NULL)
    ,m_pQA(NULL)
    ,m_iUser(userId)
{
    ui->setupUi(this);
}

ChapterExerciseSetup::~ChapterExerciseSetup()
{
    if(ce){
        ce->deleteLater();
        ce = NULL;
    }
    delete ui;
}

void ChapterExerciseSetup::setMode(int mode)
{
    m_iMode = mode;
}
//从数据库获取数据并填充界面
void ChapterExerciseSetup::initUI()
{
    QStringList subjects= DBHandler::instance()->getSubjectList();
    ui->comboBoxSubject->clear();
    ui->comboBoxSubject->addItem(QString());
    ui->comboBoxSubject->addItems(subjects);

    switch(m_iMode){
    case 0:
        setWindowTitle(QString("知识点学习"));
        break;
    case 1:
        setWindowTitle(QString("章节练习"));
        break;
    }

    show();
}
//根据选择的不同科目显示不同的章节
void ChapterExerciseSetup::on_comboBoxSubject_currentIndexChanged(QString text)
{
    int subjectID = DBHandler::instance()->getSubjectID(text);
    QStringList chapters = DBHandler::instance()->getChapterList(subjectID);
    ui->comboBoxChapter->clear();
    ui->comboBoxChapter->addItems(chapters);
}
//选中后加载对应题目
void ChapterExerciseSetup::on_btnConfirm_clicked()
{
    QString subject = ui->comboBoxSubject->currentText();
    QString chapter = ui->comboBoxChapter->currentText();

    if(subject.isEmpty() || chapter.isEmpty()) {
        QMessageBox::information(this,QString("警告"),QString("请选择需要刷题的科目和章节"));
        return;
    }

    int subjectID = DBHandler::instance()->getSubjectID(subject);
    int chapterID = DBHandler::instance()->getChapterID(subjectID,chapter);

    bool isContinue = ui->radioBtnContinue->isChecked();

    //先判断当前选择的章节是否有题目
    int qcnt = DBHandler::instance()->getQCntSubjectChapter(subjectID,chapterID);
    if(qcnt<=0){
        QMessageBox::information(this,QString("警告"),QString("当前项目的当前章节没有题目可以刷"));
        return;
    }

    //////显示界面部分 不同模式显示的界面不同////////////////
    //显示题目界面
    if(!ce){
        ce = new ChapterExercise(0,m_iUser,subjectID,chapterID,isContinue,qcnt);
    }
    if(m_iMode==0){//此模式对应知识点学习界面
        ce->setMode(0);
    }else if(m_iMode==1){//此模式对应刷题
        ce->setMode(1);
    }
    ce->setSubject(subjectID);
    ce->setChapter(chapterID);
    ce->setQCnt(qcnt);
    ce->initUI();
}

void ChapterExerciseSetup::on_btnCancer_clicked()
{
    this->close();
}
