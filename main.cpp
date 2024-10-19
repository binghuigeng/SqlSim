#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Database driver has" << QSqlDatabase::drivers();

#if 0
    // MySQL 数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL"); // 添加数据库驱动
    qDebug() << "driver valid?" << db.isValid();
//    db.setHostName("192.168.1.13"); // 或者是MySQL服务器的IP地址，如果MySQL服务器不是在本地运行
//    db.setHostName("127.0.0.1"); // 或者是MySQL服务器的IP地址，如果MySQL服务器不是在本地运行
    db.setHostName("localhost"); // 或者是MySQL服务器的IP地址，如果MySQL服务器不是在本地运行
    db.setDatabaseName("dataplatform");
    db.setUserName("admin");
    db.setPassword("123456");
    bool ok = db.open();
    qDebug() << "sql open?" << ok;

    // 若数据库打开则关闭
    if (db.isOpen()) {
        db.close();
        qDebug() << "sql close";
    }
#endif

#if 1
    // SQL Server 数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC"); // 添加数据库驱动
    qDebug() << "driver valid?" << db.isValid();
    db.setHostName("LAPTOP-FQCS913Q\\SQLEXPRESS"); // 或者是 SQL Server 服务器的IP地址，如果 SQL Server 服务器不是在本地运行
    db.setDatabaseName("custmdb");
    db.setUserName("admin");
    db.setPassword("123456");
    bool ok = db.open();
    qDebug() << "sql open?" << ok;

    // 若数据库打开则关闭
    if (db.isOpen()) {
        db.close();
        qDebug() << "sql close";
    }
#endif

    return a.exec();
}
