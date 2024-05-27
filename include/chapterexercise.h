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
    explicit ChapterExercise(int subject,int chapter,QWidget *parent = nullptr);
    ~ChapterExercise();

    void setSubject(int newSubject);
    void setChapter(int newChapter);

    void initUI();

private:
    Ui::ChapterExercise *ui;

    int m_iSubject;
    int m_iChapter;
};

#endif // CHAPTEREXERCISE_H
