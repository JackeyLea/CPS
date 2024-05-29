#include "widgetadmin.h"
#include "ui_widgetadmin.h"

WidgetAdmin::WidgetAdmin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetAdmin)
{
    ui->setupUi(this);
}

WidgetAdmin::~WidgetAdmin()
{
    delete ui;
}
