#ifndef WIDGETLOGIN_H
#define WIDGETLOGIN_H

#include <QWidget>

namespace Ui {
class WidgetLogin;
}

class WidgetLogin : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetLogin(QWidget *parent = nullptr);
    ~WidgetLogin();

private slots:
    void on_btnCancer_clicked();

    void on_btnLogin_clicked();

    void on_btnRegister_clicked();

private:
    Ui::WidgetLogin *ui;
};

#endif // WIDGETLOGIN_H
