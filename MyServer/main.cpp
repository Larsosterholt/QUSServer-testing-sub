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

QUaAccessLevel user1CanWrite(const QString &strUserName)
{
    QUaAccessLevel access;
    // Read Access to all
    access.bits.bRead = true;
    // Write Access only to juan
    if (strUserName.compare("user1", Qt::CaseSensitive) == 0)
    {
        access.bits.bWrite = true;
    }
    else
    {
        access.bits.bWrite = false;
    }
    return access;
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

    objsFolder->addChild<TemperatureSensor>("Temperature_sensor_1");
    objsFolder->addChild<TemperatureSensor>("Temperature_sensor_2");
    objsFolder->addChild<TemperatureSensor>("Temperature_sensor_3");

    // Creating a varible user1 can write
    auto writeble_var = objsFolder->addProperty("Writeble_var");
    writeble_var->setWriteAccess(true);
    writeble_var->setValue(123);
    writeble_var->setUserAccessLevelCallback(&user1CanWrite);

    qDebug() << "Added temperature sensors\n";

    // Start the server
    server.start();

    // Keep the application running until manually stopped
    return a.exec();
}
