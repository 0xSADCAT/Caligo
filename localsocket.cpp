/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "localsocket.h"

static constexpr int datastream_version = QDataStream::Qt_5_12;

Application::Application(QObject *parent)
    : QObject(parent),
      _client(new QTcpSocket(this))
{
    _client->connectToHost(_HOST, _PORT);
    connect(_client, &QTcpSocket::connected, this, &Application::clientConnected);
    connect(_client, &QTcpSocket::errorOccurred, this, &Application::clientError);
}

void Application::clientError(QAbstractSocket::SocketError)
{
    _server = new QTcpServer(this);
    if (not _server->listen(QHostAddress::Any, _PORT))
        qWarning() << "Unable to start server";
    else
        connect(_server, &QTcpServer::newConnection, this, &Application::serverNewConnection);

    QFile file(qApp->applicationDirPath() + QDir::separator() + "style.qss");
    if (file.open(QIODevice::ReadOnly)) {
        QString qss = file.readAll();
        qApp->setStyleSheet(qss);
        file.close();
    } else {
        qWarning() << "Failed to open stylesheet file:" << file.errorString();
    }

    _main_window = new MainWindow;
    _main_window->show();
}

void Application::clientConnected()
{
    for (auto& arg : qApp->arguments())
        sendToServerFromClient(arg);

    qApp->quit();
}

void Application::serverNewConnection()
{
    QTcpSocket* socket = _server->nextPendingConnection();
    connect(socket, &QTcpSocket::disconnected, this, &Application::socketDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &Application::serverReadClient);
}

void Application::serverReadClient()
{
    QTcpSocket *socket = (QTcpSocket*) sender();
    QDataStream in(socket);
    in.setVersion(datastream_version);

    QString str;
    in >> str;

    if (str.isEmpty())
        return;

    _main_window->addToPlaylist(str);
}

void Application::socketDisconnected()
{
    _main_window->forceUpdatePlaylistMetadata();
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (socket != nullptr)
        socket->deleteLater();
}

void Application::sendToServerFromClient(const QString &str)
{
    QByteArray array;
    QDataStream out(&array, QIODevice::WriteOnly);
    out.setVersion(datastream_version);
    out << str;

    out.device()->seek(0);
    _client->write(array);
    _client->flush();
}
