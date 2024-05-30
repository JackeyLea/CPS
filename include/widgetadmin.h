#ifndef WIDGETADMIN_H
#define WIDGETADMIN_H

#include <QWidget>

class AddQuestion;
class QStandardItemModel;

namespace Ui {
class WidgetAdmin;
}

class WidgetAdmin : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetAdmin(int userID,int right,QWidget *parent = nullptr);
    ~WidgetAdmin();

    void initUI();

    void setUserID(int userid);
    void setRight(int right);

private slots:
    void on_comboBoxSubject_currentTextChanged(const QString &text);

    void on_btnAddQ_clicked();

    void on_comboBoxChapter_currentTextChanged(const QString &text);

private:
    Ui::WidgetAdmin *ui;

    AddQuestion *m_pAddQ;

    QStandardItemModel *m_mUserModel;
    QStandardItemModel *m_mItemModel;

    int m_iUserID;
    bool m_bIsAdmin;//是否是管理员权限
};

#endif // WIDGETADMIN_H
