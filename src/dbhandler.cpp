#include "dbhandler.h"

#include <QMessageBox>
#include <QDebug>

DBHandler* DBHandler::s_instance = nullptr;

DBHandler::DBHandler() {
    connect2db();
}

DBHandler::~DBHandler()
{

}

DBHandler *DBHandler::instance()
{
    if(!s_instance){
        s_instance = new DBHandler;
    }

    return s_instance;
}

bool DBHandler::login(QString name, QString pwd)
{
    bool r = false;

    if(name.isEmpty() || pwd.isEmpty()) return r;

    if(m_db.isOpen()){
        QString sql = QString("select id from users where name='%1' and pwd='%2';")
                          .arg(name,pwd);
        if(m_query.exec(sql)){
            while(m_query.next()){
                r=true;
            }
        }else{
            qDebug()<<"[ERROR] [login] Cannot exec sql."<<m_query.lastError();
        }
    }else{
        qDebug()<<"[ERROR] [login] Please connect to db first."<<m_db.lastError();
    }

    return r;
}

bool DBHandler::regis(QString name, QString pwd)
{
    bool r=false;

    if(name.isEmpty() || pwd.isEmpty()) return r;

    int id = -1;
    //先查询此用户和密码是否存在
    QString sql;
    sql = QString("select max(id) from users;");
    if(m_query.exec(sql)){
        while(m_query.next()){
            id = m_query.value("max(id)").toInt();
        }
    }
    //插入数据
    if(!login(name,pwd)){
        QString sql = QString("insert into users (id,name,pwd) VALUES (%1,'%2','%3');")
                          .arg(id+1).arg(name,pwd);
        if(m_query.exec(sql)){
            qDebug()<<"[Info] Add one new user.";
            r=true;
        }else{
            qDebug()<<"[ERROR] Cannot add new user."<<m_query.lastError();
        }
    }else{
        qDebug()<<"[ERROR] User exists.";
    }

    return r;
}

int DBHandler::getSubjectID(QString subject)
{
    int id=-1;

    if(subject.isEmpty()) return id;

    if(m_db.isOpen()){
        QString sql = QString("select id from subject where name='%1'").arg(subject);
        if(m_query.exec(sql)){
            while(m_query.next()){
                id = m_query.value("id").toInt();
            }
        }
    }

    return id;
}

int DBHandler::getChapterID(int subjectID, QString chapter)
{
    int id=-1;

    if(chapter.isEmpty() || (subjectID==-1)) return id;

    if(m_db.isOpen()){
        QString sql = QString("select id from chapter where subject=%1 and name='%2'")
                          .arg(subjectID).arg(chapter);
        if(m_query.exec(sql)){
            while(m_query.next()){
                id = m_query.value("id").toInt();
            }
        }
    }

    return id;
}

QStringList DBHandler::getSubjectList()
{
    QStringList r;

    if(m_db.isOpen()){
        QString sql = "select name from subject;";
        if(m_query.exec(sql)){
            while(m_query.next()){
                r.append(m_query.value("name").toString());
            }
        }
    }

    return r;
}
//获取指定科目对应的章节
QStringList DBHandler::getChapterList(QString subject)
{
    QStringList r;

    if(subject.isEmpty()) return r;

    if(m_db.isOpen()){
        //获取科目Id
        int id = getSubjectID(subject);

        if(id==-1){
            return r;
        }

        QString sql = QString("select name from chapter where subject=%1").arg(id);
        if(m_query.exec(sql)){
            while(m_query.next()){
                r.append(m_query.value("name").toString());
            }
        }
    }

    return r;
}

void DBHandler::connect2db()
{
    if(!m_db.isValid()){
        m_db = QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName("D:\\itpmps.sqlite3");
        if(!m_db.open()){
            qDebug()<<"[ERROR] Cannot connect to db."<<m_db.lastError();
        }else{
            qDebug()<<"[Info] Connect to db.";
        }

        m_query = QSqlQuery(m_db);
    }
}
