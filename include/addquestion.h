#ifndef ADDQUESTION_H
#define ADDQUESTION_H

#include <QWidget>

namespace Ui {
class AddQuestion;
}

class AddQuestion : public QWidget
{
    Q_OBJECT

public:
    explicit AddQuestion(QWidget *parent = nullptr);
    ~AddQuestion();

    ///
    /// \brief initUI 初始化界面
    ///
    void initUI();

private slots:
    void on_comboBoxSubject_currentTextChanged(const QString &text);

    void on_btnAdd_clicked();

    void on_btnClear_clicked();

    void on_btnCancer_clicked();

private:
    Ui::AddQuestion *ui;
};

#endif // ADDQUESTION_H
