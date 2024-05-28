#include "addquestion.h"
#include "ui_addquestion.h"

AddQuestion::AddQuestion(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddQuestion)
{
    ui->setupUi(this);
}

AddQuestion::~AddQuestion()
{
    delete ui;
}
