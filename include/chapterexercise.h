#ifndef CHAPTEREXERCISE_H
#define CHAPTEREXERCISE_H

#include <QWidget>

namespace Ui {
class ChapterExercise;
}

class ChapterExercise : public QWidget
{
    Q_OBJECT

public:
    explicit ChapterExercise(int subject,int chapter,bool status,QWidget *parent = nullptr);
    ~ChapterExercise();

    void setIsContinue(bool status);
    void setSubject(int newSubject);
    void setChapter(int newChapter);

    void initUI();

private:
    Ui::ChapterExercise *ui;

    int m_iSubject;
    int m_iChapter;
    bool m_bIsContinue;
};

#endif // CHAPTEREXERCISE_H
