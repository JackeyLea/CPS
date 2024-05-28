#include "chapterexercise.h"
#include "ui_chapterexercise.h"

#include <QDebug>

ChapterExercise::ChapterExercise(int subject, int chapter, bool status, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChapterExercise)
    ,m_iSubject(subject)
    ,m_iChapter(chapter)
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

void ChapterExercise::initUI()
{
    show();
}
