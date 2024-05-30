#ifndef WIDGETQA_H
#define WIDGETQA_H

#include <QWidget>

namespace Ui {
class WidgetQA;
}

class WidgetQA : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetQA(QWidget *parent = nullptr);
    ~WidgetQA();

    void initUI();

private:
    Ui::WidgetQA *ui;
};

#endif // WIDGETQA_H
