#include "addquestion.h"
#include "ui_addquestion.h"
#include "dbhandler.h"

#include <QMessageBox>
#include <QDebug>

AddQuestion::AddQuestion(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddQuestion)
{
    ui->setupUi(this);

    initUI();
}

AddQuestion::~AddQuestion()
{
    delete ui;
}

void AddQuestion::initUI()
{
    QStringList subjectList = DBHandler::instance()->getSubjectList();
    ui->comboBoxSubject->clear();
    ui->comboBoxSubject->addItem(QString());
    ui->comboBoxSubject->addItems(subjectList);
}

void AddQuestion::on_comboBoxSubject_currentTextChanged(const QString &text)
{
    int subjectID = DBHandler::instance()->getSubjectID(text);
    QStringList chapterList = DBHandler::instance()->getChapterList(subjectID);
    ui->comboBoxChapter->clear();
    ui->comboBoxChapter->addItems(chapterList);
}

void AddQuestion::on_btnAdd_clicked()
{
    //先判断数据有效性
    int subjectID = DBHandler::instance()->getSubjectID(ui->comboBoxSubject->currentText());
    int chapterID = DBHandler::instance()->getChapterID(subjectID,ui->comboBoxChapter->currentText());
    if((subjectID==-1) || (chapterID==-1)) {
        QMessageBox::information(this,QString("警告"),QString("科目或章节无效"));
        return;
    }
    qDebug()<<"AddQuestion::on_btnAdd_clicked()"<<subjectID<<chapterID;

    //获取数据
    QString desc = ui->textDesc->toPlainText();
    QString a    = ui->textA->toPlainText();
    QString b    = ui->textB->toPlainText();
    QString c    = ui->textC->toPlainText();
    QString d    = ui->textD->toPlainText();
    QString detail = ui->textDetail->toPlainText();
    int answer = ui->comboBoxAnswer->currentIndex()+1;
    if(ui->textDesc->toPlainText().isEmpty()){
        QMessageBox::information(this,QString("警告"),QString("至少应该要有个问题描述吧"));
        return;
    }

    //插入数据库
    bool status = DBHandler::instance()->insertQuestion(subjectID,chapterID,desc,a,b,c,d,answer,detail);
    if(status){
        //插入成功
        QMessageBox::information(this,QString("警告"),QString("新问题添加成功"));
        on_btnClear_clicked();//清空界面已有数据
    }else{//插入失败
        QMessageBox::information(this,QString("警告"),QString("新问题添加失败"));
    }
}
//清空界面数据
void AddQuestion::on_btnClear_clicked()
{
    ui->textDesc->clear();
    ui->textDetail->clear();
    ui->textA->clear();
    ui->textB->clear();
    ui->textC->clear();
    ui->textD->clear();
}

void AddQuestion::on_btnCancer_clicked()
{
    //先清空界面
    on_btnClear_clicked();

    this->close();
}

