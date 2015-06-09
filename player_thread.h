#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include "chess.h"

class PlayerThread : public QThread {
    Q_OBJECT
public:
    static qint32 numberConnections;
    explicit PlayerThread(qintptr ID, QObject *parent = 0);

    void run();

signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();
    void reRender();
    void readyConnection();
    void abortConnection();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
    chess* chessBoard;
    stringstream& os;
    colors player;
};

#endif // PLAYER_THREAD_H

