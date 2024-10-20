#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Database driver has" << QSqlDatabase::drivers();

#if 1
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

    if (ok) {
        double base = 7.5;
        double accuracy = 1.0;
        QString result = "NOK";

        QSqlQuery query(db);
        query.prepare("INSERT INTO recheck (基准值, 合格精度, 复检结果) "
                      "VALUES (:base, :accuracy, :result)");
        query.bindValue(":base", base);
        query.bindValue(":accuracy", accuracy);
        query.bindValue(":result", result);

         if (query.exec()) {
             qInfo() << "recheck:" << base << accuracy << result;
         }
         else {
             qInfo() << query.lastError().text();
         }
         query.clear(); // 清空查询结果并释放系统资源
         db.close();
         qDebug() << "sql close";
    }
    else {
        qCritical() << db.lastError().text();
    }

    if (db.open()) {
        QSqlQuery query(db);
        // 查询表
        if (query.exec("SELECT * FROM recheck")) {
            // 遍历查询结果
            while (query.next()) {
                int id = query.value("ID").toInt();
                QString dateTime = query.value("日期时间").toString();
                double base = query.value("基准值").toDouble();
                double accuracy = query.value("合格精度").toDouble();
                QString result = query.value("复检结果").toString();
                QString timestamp = query.value("时戳").toString();

                // 打印查询结果
                qInfo() << "cartype:" << id << dateTime << base << accuracy << result << timestamp;
            }
        }
        else {
            // 查询失败
            qCritical() << query.lastError().text();
        }
        query.clear(); // 清空查询结果并释放系统资源
        db.close();
    }
    else {
        qCritical() << db.lastError().text();
    }
#endif

#if 0
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
