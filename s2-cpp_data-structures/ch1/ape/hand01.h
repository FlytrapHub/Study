//
// Created by Seonghwan Ju on 2024. 10. 16..
//

#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include "hand01_list.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QHBoxLayout>

class MusicPlayer : public QMainWindow {
    Q_OBJECT

public:
    MusicPlayer(QWidget *parent = nullptr);

private:
    QListWidget *musicList;
    Hand01List hand01List;
    /* 질문: 여기서 Hand01List 이건 어디서 생성되는 거지?
     *
     * 자바에서는 멤버 변수 만들면 생성자에서 new Hand01List 해줘야 하잖아 cpp에서는?
     *
     * C++에서는 클래스 멤버 변수로 객체를 선언할 때, 그 객체는 자동으로 생성됩니다.
     * 즉, Hand01List hand01List;와 같이 멤버 변수를 선언하면,
     * C++의 경우 해당 객체는 클래스가 생성될 때 자동으로 생성자 호출을 통해 초기화됩니다.
     * 자바와 달리 C++에서는 new를 사용하지 않아도 됩니다.
     *
     * Answer provided by ChatGPT. */

    /* 질문: 자바처럼 class 쓸 수 있는데 포인터 변수 쓰는 이유는?
     *
     * 내가 원할 때 메모리를 해제할 수 있기 때문. 객체의 생명주기를 내가 관리한다!
     * class의 멤버 변수는 객체가 소멸될 때 같이 사라진다고 함
     * Answer provided by ChatGPT. */
};

#endif // MUSICPLAYER_H

