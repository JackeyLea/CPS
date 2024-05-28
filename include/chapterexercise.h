#ifndef CHAPTEREXERCISE_H
#define CHAPTEREXERCISE_H

#include <QWidget>
#include <QMap>

class QButtonGroup;

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
    void updateProcessBar();

    void optionChoosed(QString option);
private slots:
    void on_btnPrevious_clicked();

    void on_btnNext_clicked();

    void on_radioBtnA_clicked();

    void on_radioBtnB_clicked();

    void on_radioBtnC_clicked();

    void on_radioBtnD_clicked();

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
    QButtonGroup *m_bgBtns;//用于显示状态的按钮
    QMap<int,QString> m_mQDoneMap;//统计已答题数据
};

#endif // CHAPTEREXERCISE_H
