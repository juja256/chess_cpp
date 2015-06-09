#ifndef CHESS_SERVER_H
#define CHESS_SERVER_H

#include <QTcpServer>
#include "player_thread.h"
#include "chess.h"

class ChessServer : public QTcpServer {
    Q_OBJECT
public:
    explicit ChessServer(QObject *parent = 0);
    void startServer(qint32);
    chess* getChessBoard();
    stringstream& getStream();
signals:
    void moved();
    void ready();

public slots:

protected:
    void incomingConnection(qintptr socketDescriptor);
    chess* chessBoard;
    stringstream os;
};

#endif // CHESS_SERVER_H
