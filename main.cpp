#include <QCoreApplication>
#include "chess_server.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    ChessServer server;
    if (argc != 2) {
        qDebug() << "Specify port!";
        return -1;
    }
    server.startServer(atoi(argv[1]));
    return a.exec();
}
