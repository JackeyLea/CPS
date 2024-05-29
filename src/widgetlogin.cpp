#include "widgetlogin.h"
#include "ui_widgetlogin.h"

#include "sha512.h"
#include "dbhandler.h"
#include "widgettype.h"

#include <QMessageBox>

WidgetLogin::WidgetLogin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetLogin)
    ,m_pType(NULL)
{
    ui->setupUi(this);
}

WidgetLogin::~WidgetLogin()
{
    delete ui;
}

void WidgetLogin::on_btnCancer_clicked()
{
    this->close();
}

void WidgetLogin::on_btnLogin_clicked()
{
    QString pwd = ui->linePWD->text();
    //将输入的密码使用sha512进行加密
    //这里使用摘要算法而不是对称加密，是为了防止逆向出密码
    std::string enPWD = sha512(pwd.toStdString());

    QString name = ui->lineName->text();

    bool isAdmin = false;
    if(name=="admin") isAdmin=true;

    int userID = DBHandler::instance()->login(name,QString::fromStdString(enPWD));
    if(userID!=-1){
        QMessageBox::information(this,QString("提示"),QString("登录成功"));
        if(!m_pType){
            m_pType = new WidgetType(userID,isAdmin);
        }
        m_pType->setUserID(userID);
        m_pType->setRight(isAdmin);
        m_pType->show();
    }else{
        QMessageBox::information(this,QString("提示"),QString("用户不存在"));
    }
}

void WidgetLogin::on_btnRegister_clicked()
{
    QString pwd = ui->linePWD->text();
    //将输入的密码使用sha512进行加密
    //这里使用摘要算法而不是对称加密，是为了防止逆向出密码
    std::string enPWD = sha512(pwd.toStdString());

    QString name = ui->lineName->text();

    bool status = DBHandler::instance()->regis(name,QString::fromStdString(enPWD));
    if(status){
        QMessageBox::information(this,QString("提示"),QString("注册成功"));
    }else{
        QMessageBox::information(this,QString("提示"),QString("用户已存在"));
    }
}
