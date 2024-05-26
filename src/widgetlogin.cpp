#include "widgetlogin.h"
#include "ui_widgetlogin.h"

WidgetLogin::WidgetLogin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetLogin)
{
    ui->setupUi(this);
}

WidgetLogin::~WidgetLogin()
{
    delete ui;
}
