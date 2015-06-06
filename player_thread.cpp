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
        // something's wrong, we just emit a signal
        emit error(socket->error());
        return;
    }

    // connect socket and signal
    // note - Qt::DirectConnection is used because it's multithreaded
    //        This makes the slot to be invoked immediately, when the signal is emitted.

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    if (PlayerThread::numberConnections >=2) {
        QByteArray err = "Sorry. Game has already started.";
        socket->write(err);
        socket->flush();
        socket->abort();
    }
    qDebug() << socketDescriptor << "Client connected";
    PlayerThread::numberConnections++;
    this->chessBoard->start();
    os << "Your figures are " << ((player == black) ? "blue" : "purple") <<"\n";
    socket->write(os.str().c_str(), os.str().length());
    os.str("");

    exec();
}

void PlayerThread::readyRead() {
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

void PlayerThread::disconnected() {
    qDebug() << socketDescriptor << "Disconnected";
    socket->deleteLater();
    exit(0);
}

void PlayerThread::reRender() {
    chessBoard->render();
    socket->write(os.str().c_str(), os.str().length());
    os.str("");
}
