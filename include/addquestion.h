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

private:
    Ui::AddQuestion *ui;
};

#endif // ADDQUESTION_H
