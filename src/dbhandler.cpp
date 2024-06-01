#include "dbhandler.h"
#include "icd.h"

#include <QMessageBox>
#include <QDebug>

DBHandler* DBHandler::s_instance = nullptr;

DBHandler::DBHandler() {
    connect2db();
}

DBHandler::~DBHandler()
{
    m_query.clear();
    if(m_db.isOpen()){
        m_db.close();
    }
}

DBHandler *DBHandler::instance()
{
    if(!s_instance){
        s_instance = new DBHandler;
    }

    return s_instance;
}

int DBHandler::login(QString name, QString pwd)
{
    int userID = -1;

    //检测表
    if(!isTableExists("users")) return userID;
    if(name.isEmpty() || pwd.isEmpty()) return userID;

    if(m_db.isOpen()){
        QString sql = QString("select id from users where name='%1' and pwd='%2';")
                          .arg(name,pwd);
        if(m_query.exec(sql)){
            while(m_query.next()){
                userID=m_query.value("id").toInt();
            }
        }else{
            qDebug()<<"[ERROR] [login] Cannot exec sql."<<m_query.lastError();
        }
    }else{
        qDebug()<<"[ERROR] [login] Please connect to db first."<<m_db.lastError();
    }

    return userID;
}

bool DBHandler::regis(QString name, QString pwd)
{
    bool r=false;

    //检测表
    if(!isTableExists("users")) return r;

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
    if(login(name,pwd)==-1){
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

    //检测表
    if(!isTableExists("subject")) return id;

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

    //检测表
    if(!isTableExists("chapter")) return id;

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
//获取某用户、某科目、某章节最大ID
int DBHandler::getRecordID(int user, int subject, int chapter)
{
    int id=-1;
    if(m_db.isOpen()){
        QString sql = QString("select max(id) from records where user=%1 and subject=%2 and chapter=%3").arg(user).arg(subject).arg(chapter);
        if(m_query.exec(sql)){
            while(m_query.next()){
                id = m_query.value("max(id)").toInt();
            }
        }
    }

    return id;
}

QStringList DBHandler::getSubjectList()
{
    QStringList r;

    //检测表
    if(!isTableExists("subject")) return r;

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
QStringList DBHandler::getChapterList(int subjectID)
{
    QStringList r;

    //检测表
    if(!isTableExists("chapter")) return r;

    if(subjectID==-1) return r;

    if(m_db.isOpen()){
        QString sql = QString("select name from chapter where subject=%1").arg(subjectID);
        if(m_query.exec(sql)){
            while(m_query.next()){
                r.append(m_query.value("name").toString());
            }
        }
    }

    return r;
}
//获取指定科目所有章节的题目
int DBHandler::getQCntSubject(int subjectID)
{
    int cnt = -1;

    //检测表
    if(!isTableExists("questions")) return cnt;

    if(m_db.isOpen()){
        QString sql = QString("select count(id) from questions where subject=%1;").arg(subjectID);
        if(m_query.exec(sql)){
            while(m_query.next()){
                cnt = m_query.value("count(id)").toInt();
            }
        }
    }

    return cnt;
}
//获取当前科目当前章节题目数量
int DBHandler::getQCntSubjectChapter(int subjectID, int chapterID)
{
    int cnt = -1;

    //检测表
    if(!isTableExists("questions")) return cnt;

    if(m_db.isOpen()){
        QString sql = QString("select count(id) from questions where subject=%1 and chapter=%2").arg(subjectID).arg(chapterID);
        if(m_query.exec(sql)){
            while(m_query.next()){
                cnt = m_query.value("count(id)").toInt();
            }
        }
    }

    return cnt;
}

QList<int> DBHandler::getIDListSubjectChapter(int subjectID, int chapterID)
{
    QList<int> r;

    if(subjectID==-1 || chapterID==-1) return r;

    //检测表
    if(!isTableExists("questions")) return r;

    if(m_db.isOpen()){
        QString sql = QString("select id from questions where subject=%1 and chapter=%2").arg(subjectID).arg(chapterID);
        if(m_query.exec(sql)){
            while(m_query.next()){
                r.append(m_query.value("id").toInt());
            }
        }
    }

    return r;
}

bool DBHandler::insertQuestion(int subjectID,int chapterID,
                               QString desc,QString a,QString b,QString c,QString d,
                               int answer,QString detail)
{
    bool r=false;

    //检测表
    if(!isTableExists("questions")) return r;

    if(m_db.isOpen()){
        // TODO 重复判断 描述权重占比45% abcd各占10% 答案占5% 答案解析占5%
        //获取最大id
        int id = -1;
        QString sql = QString("select max(id) from questions;");
        if(m_query.exec(sql)){
            while(m_query.next()){
                id = m_query.value("max(id)").toInt();
            }
        }
        sql = QString("insert into questions (id,subject,chapter,desc,a,b,c,d,answer,explain) "
                              "VALUES (:id,:subject,:chapter,:desc,:a,:b,:c,:d,:answer,:explain);");
        m_query.prepare(sql);
        m_query.bindValue(":id",id+1);
        m_query.bindValue(":subject",subjectID);
        m_query.bindValue(":chapter",chapterID);
        m_query.bindValue(":desc",desc);
        m_query.bindValue(":a",a);
        m_query.bindValue(":b",b);
        m_query.bindValue(":c",c);
        m_query.bindValue(":d",d);
        m_query.bindValue(":answer",answer);
        m_query.bindValue(":explain",detail);
        if(!m_query.exec()){
            qDebug()<<"[ERROR] DBHandler::insertQuestion: Cannot insert new data into db."<<m_query.lastError();
        }else{
            r=true;
        }
    }

    return r;
}

Question DBHandler::getQuestionInfo(int subjectID, int chapterID, int id)
{
    Question q;

    //检测表
    if(!isTableExists("questions")) return q;

    if(m_db.isOpen()){
        QString sql = QString("select desc,a,b,c,d,answer,explain from questions where id=%1 and subject=%2 and chapter=%3").arg(id).arg(subjectID).arg(chapterID);
        if(m_query.exec(sql)){
            while(m_query.next()){
                q.desc    = m_query.value("desc").toString();
                q.a       = m_query.value("a").toString();
                q.b       = m_query.value("b").toString();
                q.c       = m_query.value("c").toString();
                q.d       = m_query.value("d").toString();
                q.answer  = m_query.value("answer").toInt();
                q.explain = m_query.value("explain").toString();
            }
        }
    }

    return q;
}

bool DBHandler::saveQuestionRecord(int user, int subject, int chapter, int question, int answer)
{
    bool r=false;

    if(user==-1 || subject==-1 || chapter==-1 || question==-1 ) return r;

    if(m_db.isOpen()){
        //先检测是否存在，如果存在就更新答案
        int id=-1;
        QString sql = QString("select id from records where user=%1 and subject=%2 and chapter=%3 and question=%4;").arg(user).arg(subject).arg(chapter).arg(question);
        if(m_query.exec(sql)){
            while(m_query.next()){
                id = m_query.value("id").toInt();
            }
        }
        //更新数据
        if(id!=-1){
            sql = QString("update records set answer=%1 where id=%2 and subject=%3 and chapter=%4 and question=%5;").arg(answer).arg(id).arg(subject).arg(chapter).arg(question);
            if(m_query.exec(sql)){
                r=true;
            }else{
                qDebug()<<"[ERROR] Cannot update record."<<m_query.lastError();
            }
        }else{
            //如果数据库中没有老数据，就先获取最大id
            int maxid = getRecordID(user,subject,chapter);
            if(maxid != -1){
                sql = QString("insert into records (id,user,subject,chapter,question,answer) VALUES (%1,%2,%3,%4,%5,%6);").arg(maxid+1).arg(user).arg(subject).arg(chapter).arg(question).arg(answer);
                if(!m_query.exec(sql)){
                    r=false;
                    qDebug()<<"[ERROR] Cannot add new data into db."<<m_query.lastError();
                }else{
                    r=true;
                }
            }else{
                qDebug()<<"[ERROR] Cannot get max id with user/subject/chapter."<<m_query.lastError();
            }
        }
    }

    return r;
}
//通过科目和章节获取用户的做题记录
QMap<int, int> DBHandler::getQRecord(int user, int subject, int chapter)
{
    QMap<int,int> r;

    //检测表
    if(!isTableExists("records")) return r;

    if(user==-1 || subject==-1 || chapter==-1 ) return r;

    if(m_db.isOpen()){
        QString sql=QString("select question,answer from records where user=%1 and subject=%2 and chapter=%3;").arg(user).arg(subject).arg(chapter);
        if(m_query.exec(sql)){
            while(m_query.next()){
                int id= m_query.value("question").toInt();
                int answer= m_query.value("answer").toInt();
                r.insert(id,answer);
            }
        }
    }

    return r;
}
//清空指定用户 指定科目 指定章节的历史做题记录
void DBHandler::clearQRecord(int user, int subject, int chapter)
{
    //检测表
    if(!isTableExists("records")) return;

    if(user==-1 || subject==-1 || chapter==-1 ) return;

    if(m_db.isOpen()){
        QString sql=QString("delete from records where user=%1 and subject=%2 and chapter=%3;").arg(user).arg(subject).arg(chapter);
        if(!m_query.exec(sql)){
            qDebug()<<"[ERROR] Cannot clear history records."<<m_query.lastError();
        }
    }
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
//判断某个表是否存在
bool DBHandler::isTableExists(QString tableName)
{
    bool r=false;
    if(m_db.isOpen()){
        QString sql = QString("select count(*) from sqlite_master where type='table' and name='%1';")
                          .arg(tableName);
        if(m_query.exec(sql)){
            while(m_query.next()){
                r = m_query.value("count(*)").toBool() ==0 ? false : 1;
            }
        }
    }

    if(!r){
        qDebug()<<"[ERROR] Specific table does not existed.";
    }

    return r;
}
