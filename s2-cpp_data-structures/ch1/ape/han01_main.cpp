//
// Created by Seonghwan Ju on 2024. 10. 16..
//

#include <QApplication>
#include "hand01.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MusicPlayer player;
    player.setWindowTitle("Simple Music Player");
    player.resize(400, 300);
    player.show();
    return app.exec();
}
