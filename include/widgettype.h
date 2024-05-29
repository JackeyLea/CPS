#ifndef WIDGETTYPE_H
#define WIDGETTYPE_H

#include <QWidget>

namespace Ui {
class WidgetType;
}

class WidgetType : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetType(QWidget *parent = nullptr);
    ~WidgetType();

private:
    Ui::WidgetType *ui;
};

#endif // WIDGETTYPE_H
