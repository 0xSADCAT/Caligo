/* This file is path of the Caligo multimedia player
 * https://github.com/Alex13kyky/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "localsocket.h"

LocalSocket::LocalSocket(QObject *parent) : QObject(parent)
{
  serverBlockSize = 0;
  host = "localhost";

  client = new QTcpSocket(this);
  client->connectToHost(host, port);
  connect(client, &QTcpSocket::connected, this, &LocalSocket::clientConnected);
  connect(client, &QTcpSocket::errorOccurred, this, &LocalSocket::clientError);
}

void LocalSocket::clientError(QAbstractSocket::SocketError)
{
  server = new QTcpServer(this);
  if (not server->listen(QHostAddress::Any, port)) {
      qWarning() << "Unable to start server";
    }
  else {
      connect(server, &QTcpServer::newConnection, this, &LocalSocket::serverNewConnection);
    }

  widget = new Widget;
  widget->show();
}

void LocalSocket::clientConnected()
{
  for (int i = 1; i < qApp->arguments().count(); ++i) {
      clientSendToServer(qApp->arguments()[i]);
    }

  qApp->quit();
}

void LocalSocket::serverNewConnection()
{
  QTcpSocket *socket = server->nextPendingConnection();
  connect(socket, &QTcpSocket::disconnected, this, &LocalSocket::socketDisconnected);
  connect(socket, &QTcpSocket::readyRead, this, &LocalSocket::serverReadClient);
}

void LocalSocket::serverReadClient()
{
  QTcpSocket *socket = (QTcpSocket*) sender();
  QDataStream in(socket);
  in.setVersion(QDataStream::Qt_5_3);

  QString str;
  in >> str;

  if (str.isEmpty())
    return;

  widget->addToPlaylist(str);
}

void LocalSocket::socketDisconnected()
{
  widget->forceUpdatePlaylistMetadata();
  static_cast<QTcpSocket*>(sender())->deleteLater();
}

void LocalSocket::clientSendToServer(const QString &str)
{
  QByteArray arrBlock;
  QDataStream out(&arrBlock, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_5_2);
  out << str;

  out.device()->seek(0);
  client->write(arrBlock);

  client->flush();
}
