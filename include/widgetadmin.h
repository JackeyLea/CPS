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

    void initUI();

private slots:
    void on_comboBoxSubject_currentTextChanged(const QString &text);

private:
    Ui::WidgetAdmin *ui;
};

#endif // WIDGETADMIN_H
