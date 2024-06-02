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
    ,m_pQA(NULL)
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

void WidgetType::setUserID(int userid)
{
    m_iUserID = userid;
}

void WidgetType::setRight(int right)
{
    m_bIsAdmin = right;
}

void WidgetType::on_btnChapter_clicked()
{
    if(!ceSetup){
        ceSetup = new ChapterExerciseSetup(m_iUserID);
    }
    ceSetup->setMode(1);
    ceSetup->initUI();
}

void WidgetType::on_btnAdmin_clicked()
{
    if(!m_pAdmin){
        m_pAdmin = new WidgetAdmin(m_iUserID,m_bIsAdmin);
    }
    m_pAdmin->setUserID(m_iUserID);
    m_pAdmin->setRight(m_bIsAdmin);
    m_pAdmin->initUI();
}

void WidgetType::on_btnKN_clicked()
{
    if(!ceSetup){
        ceSetup = new ChapterExerciseSetup(m_iUserID);
    }
    ceSetup->setMode(0);
    ceSetup->initUI();
}

void WidgetType::on_btnWrong_clicked()
{
    if(!ceSetup){
        ceSetup = new ChapterExerciseSetup(m_iUserID);
    }
    ceSetup->setMode(2);
    ceSetup->initUI();
}

