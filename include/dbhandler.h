///////////////////
/// JackeyLea
/// 2024.05.26
/// 数据库处理类
///////////////////

#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>

#include "icd.h"

class DBHandler
{
public:
    DBHandler();
    ~DBHandler();

    static DBHandler* instance();

    int login(QString name, QString pwd);

    bool regis(QString name,QString pwd);

    int getSubjectID(QString subject);
    int getChapterID(int subjectID,QString chapter);
    int getRecordID(int user,int subject,int chapter);

    QStringList getSubjectList();
    QStringList getChapterList(int subjectID);

    int getQCntSubject(int subjectID);
    int getQCntSubjectChapter(int subjectID,int chapterID);
    QList<int> getIDListSubjectChapter(int subjectID,int chapterID);

    bool insertQuestion(int subjectID, int chapterID, QString desc, QString a, QString b, QString c, QString d, int answer, QString detail);

    Question getQuestionInfo(int subjectID,int chapterID,int id);

    bool saveQuestionRecord(int user,int subject,int chapter,int question,int answer);

    QMap<int,int> getQRecord(int user,int subject,int chapter);

protected:
    void connect2db();
    bool isTableExists(QString tableName);

private:
    static DBHandler* s_instance;

    QSqlDatabase m_db;
    QSqlQuery m_query;
};

#endif // DBHANDLER_H
