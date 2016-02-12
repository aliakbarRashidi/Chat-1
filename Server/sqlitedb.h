#ifndef SQLITEDB_H
#define SQLITEDB_H

#include <QObject>
#include <QtSql>
#include <QPair>

typedef QList <QPair <QString, QList<QPair <QString, QString> > > > ChatListVector;

class SQLiteDB : public QObject
{
    Q_OBJECT
public:
    explicit SQLiteDB(QObject *parent = 0);
    ~SQLiteDB();

private:
    QSqlDatabase myDB;

public slots:
    void AddContact(QString, QString, int, QString, QString, QString, QString);
    void addMessInChat(QString, QString, QString, QString);
    QList <QPair <QString, QString> > FriendList(QString, ChatListVector&);
    QList <QPair <QString, QString> > FriendKeys(QString);
    void LoadChatList(QString, QString, ChatListVector&);
    void addChatTable(QString, QString);
    QString FindInDB(QString, QString);
    QString CorrectInput(QString, QString);  //Возвращаю закрытый ключ(тест), в дальнейшем убрать.

};

#endif // SQLITEDB_H
