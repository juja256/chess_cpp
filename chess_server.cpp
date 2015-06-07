#include "chess_server.h"

ChessServer::ChessServer(QObject *parent) :
    QTcpServer(parent) {
    chessBoard = new chess(os);
}

chess* ChessServer::getChessBoard() {
    return chessBoard;
}

stringstream& ChessServer::getStream() {
    return os;
}

void ChessServer::startServer(qint32 port) {
    if(!this->listen(QHostAddress::Any,port)) {
        qDebug() << "Could not start server";
    }
    else {
        qDebug() << "Listening to port " << port << "...";
    }
}

void ChessServer::incomingConnection(qintptr socketDescriptor) {
    qDebug() << socketDescriptor << "Connecting...";

    PlayerThread *thread = new PlayerThread(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(this, SIGNAL(moved()), thread, SLOT(reRender()));

    thread->start();
}


