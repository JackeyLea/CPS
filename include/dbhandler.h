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

class DBHandler
{
public:
    DBHandler();
    ~DBHandler();

    static DBHandler* instance();

    bool login(QString name, QString pwd);

    bool regis(QString name,QString pwd);

    int getSubjectID(QString subject);
    int getChapterID(int subjectID,QString chapter);

    QStringList getSubjectList();
    QStringList getChapterList(int subjectID);

    bool insertQuestion(int subjectID, int chapterID, QString desc, QString a, QString b, QString c, QString d, QString answer, QString detail);

protected:
    void connect2db();

private:
    static DBHandler* s_instance;

    QSqlDatabase m_db;
    QSqlQuery m_query;
};

#endif // DBHANDLER_H
