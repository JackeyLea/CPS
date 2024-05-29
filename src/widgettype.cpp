#include "widgettype.h"
#include "ui_widgettype.h"
#include "chapterexercisesetup.h"
#include "widgetadmin.h"
#include "widgettype.h"

WidgetType::WidgetType(int userID, int right, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetType)
    ,ceSetup(NULL)
    ,m_pAdmin(NULL)
    ,m_iUserID(userID)
    ,m_bIsAdmin(right)
{
    ui->setupUi(this);
}

WidgetType::~WidgetType()
{
    if(ceSetup){
        ceSetup->deleteLater();
        ceSetup = NULL;
    }
    if(m_pAdmin){
        m_pAdmin->deleteLater();
        m_pAdmin = NULL;
    }
    delete ui;
}

void WidgetType::on_btnChapter_clicked()
{
    if(!ceSetup){
        ceSetup = new ChapterExerciseSetup(m_iUserID);
    }
    ceSetup->show();
}

void WidgetType::on_btnAdmin_clicked()
{
    if(!m_pAdmin){
        m_pAdmin = new WidgetAdmin();
    }
    m_pAdmin->initUI();
}

