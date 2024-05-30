#ifndef CHAPTEREXERCISESETUP_H
#define CHAPTEREXERCISESETUP_H

#include <QWidget>

class ChapterExercise;
class WidgetQA;

namespace Ui {
class ChapterExerciseSetup;
}

class ChapterExerciseSetup : public QWidget
{
    Q_OBJECT

public:
    explicit ChapterExerciseSetup(int userId,QWidget *parent = nullptr);
    ~ChapterExerciseSetup();

    void setMode(int mode);

    void initUI();

private slots:
    void on_comboBoxSubject_currentIndexChanged(QString text);

    void on_btnConfirm_clicked();

    void on_btnCancer_clicked();

private:
    Ui::ChapterExerciseSetup *ui;

    ChapterExercise *ce;
    WidgetQA *m_pQA;

    int m_iUser;
    int m_iMode;//当前模式
};

#endif // CHAPTEREXERCISESETUP_H
