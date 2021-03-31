/* This file is path of the Caligo multimedia player
 * https://github.com/Alex13kyky/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef LOCALSOCKET_H
#define LOCALSOCKET_H

#include <widget.h>

#include <QTcpServer>
#include <QTcpSocket>

class LocalSocket : public QObject
{
  Q_OBJECT
public:
  explicit LocalSocket(QObject *parent = nullptr);

private:
  Widget *widget;

  QTcpServer *server;
  QTcpSocket *client;

  quint16 serverBlockSize;

  QString host;
  int port = 9999;

  void clientSendToServer(const QString &str);

private slots:
  void clientError(QAbstractSocket::SocketError);
  void clientConnected();

  virtual void serverNewConnection();
  void serverReadClient();

  void socketDisconnected();
};

#endif // LOCALSOCKET_H
