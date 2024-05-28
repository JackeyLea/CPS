#include "chapterexercisesetup.h"
#include "ui_chapterexercisesetup.h"

#include "dbhandler.h"
#include "chapterexercise.h"

#include <QDebug>

ChapterExerciseSetup::ChapterExerciseSetup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChapterExerciseSetup)
    ,ce(NULL)
{
    ui->setupUi(this);

    initUI();
}

ChapterExerciseSetup::~ChapterExerciseSetup()
{
    delete ui;
}
//从数据库获取数据并填充界面
void ChapterExerciseSetup::initUI()
{
    QStringList subjects= DBHandler::instance()->getSubjectList();
    ui->comboBoxSubject->clear();
    ui->comboBoxSubject->addItem(QString());
    ui->comboBoxSubject->addItems(subjects);
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

    if(subject.isEmpty() || chapter.isEmpty()) return;

    int subjectID = DBHandler::instance()->getSubjectID(subject);
    int chapterID = DBHandler::instance()->getChapterID(subjectID,chapter);

    bool isContinue = ui->radioBtnContinue->isChecked();

    //显示题目界面
    if(!ce){
        ce = new ChapterExercise(subjectID,chapterID,isContinue);
    }
    ce->setSubject(subjectID);
    ce->setChapter(chapterID);
    ce->show();
}

void ChapterExerciseSetup::on_btnCancer_clicked()
{
    this->close();
}
