#include "widgetqa.h"
#include "ui_widgetqa.h"

WidgetQA::WidgetQA(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetQA)
{
    ui->setupUi(this);
}

WidgetQA::~WidgetQA()
{
    delete ui;
}

void WidgetQA::initUI()
{

}
