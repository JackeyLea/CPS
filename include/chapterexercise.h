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
    explicit ChapterExercise(int subject,int chapter,bool status,int qnt,QWidget *parent = nullptr);
    ~ChapterExercise();

    void setIsContinue(bool status);
    void setSubject(int newSubject);
    void setChapter(int newChapter);
    void setQCnt(int newCnt);

    void initUI();
    void checkPreviouseNext();
    void clearOptionStatus();

    void showQuestionWithSCID(int subject,int chapter,int id);
private slots:
    void on_btnPrevious_clicked();

    void on_btnNext_clicked();

private:
    Ui::ChapterExercise *ui;

    int m_iSubject;
    int m_iChapter;
    int m_iMinQuestionID;//当前章节最小ID
    int m_iMaxQuestionID;//当前章节最大ID
    int m_iQuestionID;//当前处理的问题ID
    int m_iDoneCnt;//当前已完成题数
    int m_iChapterQCnt;//当前章节总题数
    bool m_bIsContinue;
};

#endif // CHAPTEREXERCISE_H
