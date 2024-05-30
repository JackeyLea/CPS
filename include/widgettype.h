#ifndef WIDGETTYPE_H
#define WIDGETTYPE_H

#include <QWidget>

class ChapterExerciseSetup;
class WidgetAdmin;
class WidgetQA;

namespace Ui {
class WidgetType;
}

class WidgetType : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetType(int userID,int right,QWidget *parent = nullptr);
    ~WidgetType();

    void setUserID(int userid);
    void setRight(int right);

private slots:
    void on_btnChapter_clicked();

    void on_btnAdmin_clicked();

    void on_btnKN_clicked();

private:
    Ui::WidgetType *ui;

    ChapterExerciseSetup *ceSetup;
    WidgetAdmin *m_pAdmin;
    WidgetQA *m_pQA;

    int m_iUserID;
    bool m_bIsAdmin;//是否是管理员权限
};

#endif // WIDGETTYPE_H
