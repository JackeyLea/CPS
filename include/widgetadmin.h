#ifndef WIDGETADMIN_H
#define WIDGETADMIN_H

#include <QWidget>

namespace Ui {
class WidgetAdmin;
}

class WidgetAdmin : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetAdmin(QWidget *parent = nullptr);
    ~WidgetAdmin();

private:
    Ui::WidgetAdmin *ui;
};

#endif // WIDGETADMIN_H
