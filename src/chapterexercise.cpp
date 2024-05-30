#include "chapterexercise.h"
#include "ui_chapterexercise.h"

#include "dbhandler.h"

#include <QDebug>
#include <QButtonGroup>
#include <QResizeEvent>
#include <QDesktopWidget>
#include <QMessageBox>

ChapterExercise::ChapterExercise(int mode, int userID, int subject, int chapter, bool status, int qnt, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChapterExercise)
    ,m_iUser(userID)
    ,m_iSubject(subject)
    ,m_iChapter(chapter)
    ,m_iQuestionID(0)
    ,m_iDoneCnt(0)
    ,m_iChapterQCnt(qnt)
    ,m_iMode(mode)
    ,m_bIsContinue(status)
{
    ui->setupUi(this);
    qDebug()<<QString("[Info] [ChapterExercies::ChapterExercise] subject id %1,chapter id %2,status %3")
                    .arg(subject).arg(chapter).arg(status);
}

ChapterExercise::~ChapterExercise()
{
    if(m_bgBtns){
        for(int i=0;i<m_iChapterQCnt;i++){
            QPushButton *btn = (QPushButton*)m_bgBtns->button(i);
            if(btn){
                btn->disconnect(SIGNAL(clicked()),this,SLOT(sltBtnStatusClicked()));
                btn->deleteLater();
                btn=NULL;
            }
        }
        m_bgBtns->deleteLater();
        m_bgBtns = NULL;
    }
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

void ChapterExercise::setMode(int newMode)
{
    m_iMode = newMode;
}

void ChapterExercise::initUI()
{
    if(m_bIsContinue){
        //TODO 继续刷题 从数据库中将之前的做题记录导入至内容
        //从数据库中获取当前科目当前章节的题目数据
    }

    //清理之前的数据
    m_iQuestionID = 0;
    m_mQDoneMap.clear();
    m_iQuestionID = -1;
    m_iMinQuestionID=-1;
    m_iMaxQuestionID = -1;
    m_iDoneCnt=0;

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

    //检测继续刷题状态 TODO 无法继续刷题
    // TODO使用那个记录

    //////////////////////////界面显示部分////////////////////////////
    if(m_iMode==-1){
        QMessageBox::warning(this,QString("警告"),QString("模式错误"));
        return;
    }
    if(m_iMode ==0){//知识点
        ui->labelAnswer->setVisible(true);
        ui->labelAnswer2->setVisible(true);
        ui->comboBoxAnswer->setVisible(true);
        ui->comboBoxAnswer->setEnabled(false);
        ui->textDetail->setVisible(true);
    }else if(m_iMode==1){
        ui->labelAnswer->setVisible(false);
        ui->labelAnswer2->setVisible(false);
        ui->comboBoxAnswer->setVisible(false);
        ui->textDetail->setVisible(false);
    }
    //位于左侧的题目状态显示界面
    m_bgBtns = new QButtonGroup(ui->frameNav);
    for(int i=0;i<m_iChapterQCnt;i++){
        QPushButton *btn=new QPushButton(ui->frameNav);
        btn->setText(QString("%1").arg(i+1));
        btn->setGeometry(10+(i%5)*35,10+(i/5)*35,25,25);
        btn->setStyleSheet(QString("border:1px solid gray;background-color:gray;"));
        m_bgBtns->addButton(btn,i);
        connect(btn,&QPushButton::clicked,this,&ChapterExercise::sltBtnStatusClicked);
    }

    updateProcessBar();//进度条

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
    //下一题后清空选项状态
    ui->radioBtnA->setChecked(false);
    ui->radioBtnB->setChecked(false);
    ui->radioBtnC->setChecked(false);
    ui->radioBtnD->setChecked(false);
}

void ChapterExercise::showQuestionWithSCID(int subject, int chapter, int id)
{
    Question q = DBHandler::instance()->getQuestionInfo(subject,chapter,id);

    ui->labelQuestion->setText(q.desc);
    ui->labelA->setText(q.a);
    ui->labelB->setText(q.b);
    ui->labelC->setText(q.c);
    ui->labelD->setText(q.d);

    if(m_iMode==0){
        //知识点学习模式
        ui->comboBoxAnswer->setCurrentIndex(q.answer-1);
        ui->textDetail->setText(q.explain);
    }

    //显示当前题目的状态，是否是已完成
    setExistedOption();
    setCurQStatus();
}
//更新进度条
void ChapterExercise::updateProcessBar()
{
    //完成计数
    if(m_iChapterQCnt!=0){
        ui->progressBar->setValue((m_iDoneCnt*1.0 / m_iChapterQCnt)*100);
    }
}

void ChapterExercise::optionChoosed(int option)
{
    //如果某一题的答案中的任意一个选项被点击了
    if(!m_mQDoneMap.contains(m_iQuestionID)){
        m_mQDoneMap.insert(m_iQuestionID,option);
        m_iDoneCnt++;
        setCurQStatus();
    }
    updateProcessBar();
}
//如果当前题目已经做了，显示做的结果
void ChapterExercise::setExistedOption()
{
    if(m_mQDoneMap.contains(m_iQuestionID)){
        int option = m_mQDoneMap.value(m_iQuestionID);
        setCurQStatus();
        //设置四个按钮状态
        switch(option){
        case 1://选择A
            ui->radioBtnA->setChecked(true);
            ui->radioBtnB->setChecked(false);
            ui->radioBtnC->setChecked(false);
            ui->radioBtnD->setChecked(false);
            break;
        case 2:
            ui->radioBtnA->setChecked(false);
            ui->radioBtnB->setChecked(true);
            ui->radioBtnC->setChecked(false);
            ui->radioBtnD->setChecked(false);
            break;
        case 3:
            ui->radioBtnA->setChecked(false);
            ui->radioBtnB->setChecked(false);
            ui->radioBtnC->setChecked(true);
            ui->radioBtnD->setChecked(false);
            break;
        case 4:
            ui->radioBtnA->setChecked(false);
            ui->radioBtnB->setChecked(false);
            ui->radioBtnC->setChecked(false);
            ui->radioBtnD->setChecked(true);
            break;
        }
    }
}
//设置当前题的状态：已完成 当前题 未完成
void ChapterExercise::setCurQStatus()
{
    for(int i=0;i<m_iChapterQCnt;i++){
        bool isDone=m_mQDoneMap.contains(m_iMinQuestionID+i);//完成
        bool isCur=(m_iQuestionID==i+m_iMinQuestionID);//当前
        if(isDone){
            if(isCur){//当前已完成
                m_bgBtns->button(i)->setStyleSheet(QString("border:1px solid red;\nbackground-color: green;"));
            }else{//非当前已完成
                m_bgBtns->button(i)->setStyleSheet(QString("border:1px solid gray;\nbackground-color: green;"));
            }
        }else{
            if(isCur){//当前未完成
                m_bgBtns->button(i)->setStyleSheet(QString("border:1px solid red;\nbackground-color: gray;"));
            }else{//非当前未完成
                m_bgBtns->button(i)->setStyleSheet(QString("border:1px solid gray;background-color:gray;"));
            }
        }
    }
    //设置
}
//左侧状态按钮点击后
void ChapterExercise::sltBtnStatusClicked()
{
    QPushButton *btn = (QPushButton*)sender();
    m_iQuestionID = m_bgBtns->id(btn)+1;
    showQuestionWithSCID(m_iSubject,m_iChapter,m_iQuestionID);
    checkPreviouseNext();//点击新按钮后检查下一题按钮状态
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
    setCurQStatus();
}

void ChapterExercise::on_radioBtnA_clicked()
{
    ui->radioBtnA->setChecked(true);
    ui->radioBtnB->setChecked(false);
    ui->radioBtnC->setChecked(false);
    ui->radioBtnD->setChecked(false);
    optionChoosed(1);
}

void ChapterExercise::on_radioBtnB_clicked()
{
    ui->radioBtnA->setChecked(false);
    ui->radioBtnB->setChecked(true);
    ui->radioBtnC->setChecked(false);
    ui->radioBtnD->setChecked(false);
    optionChoosed(2);
}

void ChapterExercise::on_radioBtnC_clicked()
{
    ui->radioBtnA->setChecked(false);
    ui->radioBtnB->setChecked(false);
    ui->radioBtnC->setChecked(true);
    ui->radioBtnD->setChecked(false);
    optionChoosed(3);
}

void ChapterExercise::on_radioBtnD_clicked()
{
    ui->radioBtnA->setChecked(false);
    ui->radioBtnB->setChecked(false);
    ui->radioBtnC->setChecked(false);
    ui->radioBtnD->setChecked(true);
    optionChoosed(4);
}

//结束刷题
void ChapterExercise::on_btnEnd_clicked()
{
    QMessageBox::StandardButton btn = QMessageBox::information(this,QString("警告"),QString("是否保存刷题记录"),QMessageBox::Yes | QMessageBox::No);
    if(btn==QMessageBox::Yes){
        //保存记录
        for(int i=0;i<m_mQDoneMap.count();i++){
            bool status = DBHandler::instance()->saveQuestionRecord(m_iUser,m_iSubject,m_iChapter,m_iMinQuestionID+i,m_mQDoneMap.value(m_iMinQuestionID+i));
            if(!status){
                qDebug()<<"save record failed: "<<m_iMinQuestionID+i;
            }
        }
    }

    close();
}

