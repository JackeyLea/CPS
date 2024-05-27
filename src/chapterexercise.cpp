#include "chapterexercise.h"
#include "ui_chapterexercise.h"

ChapterExercise::ChapterExercise(int subject, int chapter, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChapterExercise)
    ,m_iSubject(subject)
    ,m_iChapter(chapter)
{
    ui->setupUi(this);
}

ChapterExercise::~ChapterExercise()
{
    delete ui;
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
