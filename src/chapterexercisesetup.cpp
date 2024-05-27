#include "chapterexercisesetup.h"
#include "ui_chapterexercisesetup.h"

ChapterExerciseSetup::ChapterExerciseSetup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChapterExerciseSetup)
{
    ui->setupUi(this);
}

ChapterExerciseSetup::~ChapterExerciseSetup()
{
    delete ui;
}
