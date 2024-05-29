#include "widgettype.h"
#include "ui_widgettype.h"

WidgetType::WidgetType(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetType)
{
    ui->setupUi(this);
}

WidgetType::~WidgetType()
{
    delete ui;
}
