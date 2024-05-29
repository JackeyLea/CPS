#ifndef CHAPTEREXERCISESETUP_H
#define CHAPTEREXERCISESETUP_H

#include <QWidget>

class ChapterExercise;

namespace Ui {
class ChapterExerciseSetup;
}

class ChapterExerciseSetup : public QWidget
{
    Q_OBJECT

public:
    explicit ChapterExerciseSetup(int userId,QWidget *parent = nullptr);
    ~ChapterExerciseSetup();

protected:
    void initUI();

private slots:
    void on_comboBoxSubject_currentIndexChanged(QString text);

    void on_btnConfirm_clicked();

    void on_btnCancer_clicked();

private:
    Ui::ChapterExerciseSetup *ui;

    ChapterExercise *ce;

    int m_iUser;
};

#endif // CHAPTEREXERCISESETUP_H
