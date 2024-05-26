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

private:
    Ui::WidgetLogin *ui;
};

#endif // WIDGETLOGIN_H
