#include "player_thread.h"
#include "chess.h"
#include "chess_server.h"

qint32 PlayerThread::numberConnections = 0;

PlayerThread::PlayerThread(qintptr ID, QObject *parent) :
    QThread(parent), os(((ChessServer*)parent)->getStream()) {
    this->socketDescriptor = ID;
    this->chessBoard = ((ChessServer*)parent)->getChessBoard();
    if (PlayerThread::numberConnections == 0)
        this->player = white;
    else
        this->player = black;
}

void PlayerThread::run() {

    qDebug() << "Thread started";
    socket = new QTcpSocket();
    if(!socket->setSocketDescriptor(this->socketDescriptor)) {
        emit error(socket->error());
        return;
    }

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    PlayerThread::numberConnections++;
    if (PlayerThread::numberConnections >2) {
        QByteArray err = "Sorry. Game has already started.";
        socket->write(err);
        socket->flush();
        socket->abort();
    }
    qDebug() << socketDescriptor << "Client connected";

    this->chessBoard->start();
    os << "Your figures are " << ((player == black) ? "blue" : "purple") <<"\n";
    if (PlayerThread::numberConnections <2) {
        os << "Opponent has not connected yet. Wait..\n";
    }
    else {
        emit ((ChessServer*)this->parent())->ready();
    }
    socket->write(os.str().c_str(), os.str().length());
    os.str("");

    exec();
}

void PlayerThread::readyRead() {
    if (PlayerThread::numberConnections<2) {
        QByteArray err = "Opponent hasn't connected yet. Wait.";
        socket->write(err);
    }
    else {
        QByteArray Data = socket->readAll();
        string move(Data.constData(), Data.length());
        qDebug() << socketDescriptor << "Data in: " << Data;
        int s = this->chessBoard->move(move, this->player);
        if (!s) // succesful move
            emit ((ChessServer*)this->parent())->moved();
        else { // error during moving
            socket->write(os.str().c_str(), os.str().length());
            os.str("");
        }
    }
}

void PlayerThread::disconnected() {
    qDebug() << socketDescriptor << "Disconnected";
    socket->deleteLater();
    PlayerThread::numberConnections--;
    exit(0);
}

void PlayerThread::reRender() {
    chessBoard->render();
    socket->write(os.str().c_str(), os.str().length());
    os.str("");
}

void PlayerThread::readyConnection() {
    os << "Ready! Start the game!\n";
    socket->write(os.str().c_str(), os.str().length());
    os.str("");
}
