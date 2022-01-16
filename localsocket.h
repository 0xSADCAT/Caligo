/* This file is part of the Caligo multimedia player
 * https://github.com/0xSADCAT/Caligo
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
*/

#ifndef LOCALSOCKET_H
#define LOCALSOCKET_H

#include <mainwindow.h>

#include <QTcpServer>
#include <QTcpSocket>

/**
 * @brief The Application class connects to main window or creates window on error
 *
 * Just create it in main
 */
class Application : public QObject
{
  Q_OBJECT
public:
  explicit Application(QObject *parent = nullptr);

private:
  MainWindow* _main_window;

  QTcpServer* _server;
  QTcpSocket* _client;

  quint16 _serverBlockSize = 0;

  const QString _HOST = "localhost";
  const int _PORT = 9999;

  void sendToServerFromClient(const QString &str);

private slots:
  void clientError(QAbstractSocket::SocketError);
  void clientConnected();

  void serverNewConnection();
  void serverReadClient();

  void socketDisconnected();
};

#endif // LOCALSOCKET_H
