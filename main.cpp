#include <QCoreApplication>
#include "chess_server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // Make a server and starts it
    ChessServer server;
    server.startServer();

    return a.exec();
}
