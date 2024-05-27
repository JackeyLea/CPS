#ifndef CHAPTEREXERCISESETUP_H
#define CHAPTEREXERCISESETUP_H

#include <QWidget>

namespace Ui {
class ChapterExerciseSetup;
}

class ChapterExerciseSetup : public QWidget
{
    Q_OBJECT

public:
    explicit ChapterExerciseSetup(QWidget *parent = nullptr);
    ~ChapterExerciseSetup();

private:
    Ui::ChapterExerciseSetup *ui;
};

#endif // CHAPTEREXERCISESETUP_H
