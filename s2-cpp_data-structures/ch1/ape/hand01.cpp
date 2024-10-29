/*
실습 문제 1: 음악 재생 목록 구현하기
- 마지막 노드의 다음은 다시 첫 번째 노드가 되어야 하는 원형 연결 리스트를 구현할 것임

[요구사항]
- 재생 목록에 음악 추가 가능
- 재생 목록에서 음악 제거 가능
- 음악을 순차적으로 출력할 수 있어야 함

[아이디어]
원형 연결 리스트라면 Node에 prev, next가 있으면 될 것 같음
배열의 길이는 동적이여야 함 -> 이건 linked list로 구현하면 해결 되는 것임

내부 동작 예시
처음
    head -> null
음악 추가
    head -> m1(prev=m1,next=m1)
음악 추가
    head -> m1(prev=m2,next=m2)-m2(prev=m1,next=m1)
음악 추가
    head -> m1(prev=m3,next=m2)-m2(prev=m1,next=m3)-m3(prev=m2,next=m1)
if 마지막 제거
    head -> m1(prev=m2,next=m2)-m2(prev=m1,next=m1)
else if 중간 제거
    head -> m1(prev=m3,next=m3)-m3(prev=m1,next=m1)
else if 처음 제거
    head -> m2(prev=m3,next=m3)-m3(prev=m2,next=m2)

잠깐? 문제가 이상한데? 요구사항만 보면 원형 리스트일 필요가 없지 않나... 어디서 원형 리스트를 활용하게 되는 거임?
출력할 때 index를 받아서 index 부터 n개 출력하기? 이런식으로 구현해 볼까?
만약 리스트에 음악 m1 한 개가 있는데 출력 10개 하면 m1, m1, m1 ..., m1 10개 나오는 거임

또 index 검색 할 때 만약 리스트에 5개 요소가 있다 이때 get(6)을 하면 첫 번째 요소가 나오게 하는 거임!

Created by Seonghwan Ju on 2024. 10. 10.
*/

#include "hand01.h"
#include <QDebug>

MusicPlayer::MusicPlayer(QWidget *parent) : QMainWindow(parent) {
    // 메인 위젯 및 레이아웃 설정
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // 음악 목록 위젯
    musicList = new QListWidget(this);
    layout->addWidget(musicList);

    // 음악 추가 입력
    QLineEdit *musicInput = new QLineEdit(this);
    layout->addWidget(musicInput);

    // 버튼 레이아웃
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    // 재생 버튼
    QPushButton *playButton = new QPushButton("Play", this);
    buttonLayout->addWidget(playButton);

    // 일시 정지 버튼
    QPushButton *pauseButton = new QPushButton("Pause", this);
    buttonLayout->addWidget(pauseButton);

    // 음악 추가 버튼
    QPushButton *addButton = new QPushButton("Add", this);
    buttonLayout->addWidget(addButton);

    // 음악 제거 버튼
    QPushButton *removeButton = new QPushButton("Remove", this);
    buttonLayout->addWidget(removeButton);

    layout->addLayout(buttonLayout);

    // 추가 버튼 연결
    connect(addButton, &QPushButton::clicked, [=]() {
        QString musicTitle = musicInput->text();
        if (!musicTitle.isEmpty()) {
            musicList->addItem(musicTitle);
            musicInput->clear();

            hand01List.add(musicTitle.toStdString());
            hand01List.printForward();
        }
    });

    // 삭제 버튼 연결
    connect(removeButton, &QPushButton::clicked, [=]() {
        if (musicList->currentItem()) {
            const int currentIndex = musicList->currentRow();  // 현재 선택된 아이템의 인덱스를 얻음
            hand01List.remove(currentIndex);
            hand01List.printForward();

            delete musicList->takeItem(musicList->currentRow());
        } else {
            qDebug() << "No music selected to remove.";
        }
    });

    // 재생 버튼 연결
    connect(playButton, &QPushButton::clicked, [=]() {
        if (musicList->currentItem()) {
            qDebug() << "Playing from here:" << musicList->currentItem()->text();

            const int currentIndex = musicList->currentRow();
            hand01List.print(currentIndex, 10);
        } else {
            qDebug() << "No music selected to play.";
        }
    });

    // 일시 정지 버튼 연결
    connect(pauseButton, &QPushButton::clicked, [=]() {
        qDebug() << "Paused";
    });
}
