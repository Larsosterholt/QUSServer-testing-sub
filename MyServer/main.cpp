#include <QCoreApplication>
#include <QUaServer>
#include <iostream>
#include <QList>

#include "UserModel.h"
#include "temperaturesensor.h"


// User database for testing
QList<User> users = {
    {"user1", "password1"},
    {"user2", "password2"},
    // Add more users as needed
};

// Login method
bool isValidUser(const QString& username, const QString& password) {
    for (const User& user : users) {
        if (user.username == username && user.password == password) {
            return true;
        }
    }
    qDebug() << "Failed login attempt...\n";
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

    // Set the user validation callback
    server.setAnonymousLoginAllowed(false);
    server.setUserValidationCallback([](const QString& username, const QString& password) -> bool {
        return isValidUser(username, password);
    });



    // register new type

    server.registerType<TemperatureSensor>();

    // create new type instances
    QUaFolderObject * objsFolder = server.objectsFolder();

    objsFolder->addChild<TemperatureSensor>("Sensor1");
    objsFolder->addChild<TemperatureSensor>("Sensor2");
    objsFolder->addChild<TemperatureSensor>("Sensor3");
    qDebug() << "Added temperature sensors\n";

    // Start the server
    server.start();

    // Keep the application running until manually stopped
    return a.exec();
}
