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

    ///
    /// \brief setMode 设置模式
    /// \param mode 模式 0知识点 1章节 2错题
    ///
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
