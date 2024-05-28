#include "chapterexercise.h"
#include "ui_chapterexercise.h"

#include "dbhandler.h"

#include <QDebug>
#include <QButtonGroup>
#include <QResizeEvent>
#include <QDesktopWidget>

ChapterExercise::ChapterExercise(int subject, int chapter, bool status, int qnt, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChapterExercise)
    ,m_iSubject(subject)
    ,m_iChapter(chapter)
    ,m_iQuestionID(0)
    ,m_iDoneCnt(0)
    ,m_iChapterQCnt(qnt)
    ,m_bIsContinue(status)
{
    ui->setupUi(this);
    qDebug()<<QString("ChapterExercies->subject id %1,chapter id %2,status %3")
                    .arg(subject).arg(chapter).arg(status);
}

ChapterExercise::~ChapterExercise()
{
    delete ui;
}

void ChapterExercise::setIsContinue(bool status)
{
    m_bIsContinue = status;
}

void ChapterExercise::setSubject(int newSubject)
{
    if(newSubject != m_iSubject){
        m_iSubject = newSubject;
    }
}

void ChapterExercise::setChapter(int newChapter)
{
    if(newChapter != m_iChapter){
        m_iChapter = newChapter;
    }
}

void ChapterExercise::setQCnt(int newCnt)
{
    m_iChapterQCnt = newCnt;
}

void ChapterExercise::initUI()
{
    if(m_bIsContinue){
        // TODO 继续刷题
    }else{
        m_iQuestionID = 0;
    }
    //获取数据库中最小有效id
    m_iMinQuestionID = DBHandler::instance()->getMinQIDSubjectChapter(m_iSubject,m_iChapter);
    if(m_iMinQuestionID==-1){
        qDebug()<<"[ERROR] [ChapterExercise::initUI] Cannot get start question id.";
    }
    m_iQuestionID = m_iMinQuestionID;

    //获取当前章节最大ID
    m_iMaxQuestionID = DBHandler::instance()->getMaxQIDSubjectChapter(m_iSubject,m_iChapter);
    if(m_iMaxQuestionID==-1){
        qDebug()<<"[ERROR] [ChapterExercise::initUI] Cannot get end question id.";
    }

    //位于左侧的题目状态显示界面
    QButtonGroup btnGrp(ui->frameNav);
    for(int i=0;i<m_iChapterQCnt;i++){
        QPushButton *btn=new QPushButton(ui->frameNav);
        btn->setText(QString("%1").arg(i+1));
        btn->setGeometry(10+(i%5)*35,10+(i/5)*35,25,25);
        btn->setStyleSheet(QString("border:1px solid gray;background-color:gray;"));
        btnGrp.addButton(btn);
    }

    //完成计数
    if(m_iChapterQCnt!=0){
        ui->progressBar->setValue(m_iDoneCnt / m_iChapterQCnt);
    }

    //显示问题信息
    showQuestionWithSCID(m_iSubject,m_iChapter,m_iQuestionID);
    show();
    //设置窗口居中显示，主要是实现手动刷新一次窗口
    setGeometry(QApplication::desktop()->width() / 2 - width()/2,
                QApplication::desktop()->height()/2-height()/2,
                width(),height());
    checkPreviouseNext();//检测上一题下一题
}

void ChapterExercise::checkPreviouseNext()
{
    //上一题下一题按钮
    if(m_iQuestionID == m_iMinQuestionID){
        ui->btnPrevious->setEnabled(false);
    }else{
        ui->btnPrevious->setEnabled(true);
    }
    if(m_iQuestionID == m_iMaxQuestionID){
        ui->btnNext->setEnabled(false);
    }else{
        ui->btnNext->setEnabled(true);
    }
    // TODO这里一个问题，只有一道题的时候
}

void ChapterExercise::clearOptionStatus()
{
    ui->radioBtnA->setChecked(false);
    ui->radioBtnB->setChecked(false);
    ui->radioBtnC->setChecked(false);
    ui->radioBtnD->setChecked(false);
    // TODO 下一题后无法清除之前的选中状态
}

void ChapterExercise::showQuestionWithSCID(int subject, int chapter, int id)
{
    Question q = DBHandler::instance()->getQuestionInfo(subject,chapter,id);

    ui->labelQuestion->setText(q.desc);
    ui->labelA->setText(q.a);
    ui->labelB->setText(q.b);
    ui->labelC->setText(q.c);
    ui->labelD->setText(q.d);
}

void ChapterExercise::on_btnPrevious_clicked()
{
    clearOptionStatus();//清除选项状态
    m_iQuestionID -=1;
    showQuestionWithSCID(m_iSubject,m_iChapter,m_iQuestionID);
    checkPreviouseNext();
}

void ChapterExercise::on_btnNext_clicked()
{
    clearOptionStatus();//清除选项状态
    m_iQuestionID +=1;
    showQuestionWithSCID(m_iSubject,m_iChapter,m_iQuestionID);
    checkPreviouseNext();
}

