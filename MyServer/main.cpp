#include <QCoreApplication>
#include <QUaServer>
#include <iostream>
#include <QList>





struct User {
    QString username;
    QString password;
};

QList<User> users = {
    {"user1", "password1"},
    {"user2", "password2"},
    // Add more users as needed
};

bool isValidUser(const QString& username, const QString& password) {
    for (const User& user : users) {
        if (user.username == username && user.password == password) {
            return true;
        }
    }
    return false;
}




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Create a new QUaServer instance
    QUaServer server;


    // Logging
    QObject::connect(&server, &QUaServer::logMessage,
                     [](const QUaLog &log) {
                         qDebug() << "[" << log.level << "] :" << log.message;
                     });

    // Setting port
    server.setPort(4841);
    qDebug() << "Set port to: " << server.port() << "\n";




    server.setApplicationName("Lars test server");
    server.setAnonymousLoginAllowed(false);


    // Start the server
    server.start();



    // Keep the application running until manually stopped
    return a.exec();
}
