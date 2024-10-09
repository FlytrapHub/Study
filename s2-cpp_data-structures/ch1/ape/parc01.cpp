//
// 연습 문제 1: 동적 크기 배열 구하기
// Created by Seonghwan Ju on 2024. 10. 9..
//
#include <iostream>
#include <sstream>

using namespace std;

template<typename T>
class dynamic_array {
    T *data;
    size_t n;

public:
    dynamic_array(int n) {
        this->n = n;
        data = new T[n];
    }

    dynamic_array(const dynamic_array<T> &other) {
        n = other.n;
        data = new T[n];

        for (int i = 0; i < n; i++)
            data[i] = other[i];
    }

    // 대괄호 []의 역할: 배열이나 리스트처럼 인덱스를 통해 특정 위치의 값에 접근할 때 사용
    // arr[2]라고 하면, arr 배열의 세 번째 요소에 접근하는 것이죠. 이를 객체에도 동일하게 적용할 수 있도록 operator[]를 오버로딩하는 겁니다.
    // 앞에 & : 함수가 값을 반환할 때 해당 값의 참조(주소)를 반환한다는 뜻
    T &operator[](int index) {
        return data[index];
    }

    // 앞 const : 이 함수는 data[index]에 대한 참조를 반환하지만, 그 참조된 값을 수정할 수 없도록 보장합니다. 값을 읽기 전용으로 반환하는 것입니다.
    // 뒤 const: 멤버 함수가 const 함수라는 것을 의미합니다. 이는 함수 내부에서 객체의 멤버 변수를 변경할 수 없다는 것을 보장합니다.
    const T &operator[](int index) const {
        return data[index];
    }

    T &at(int index) {
        if (index < n)
            return data[index];
        throw "Index out of range";
    }

    size_t size() const {
        return n;
    }

    ~dynamic_array() {
        delete[] data; // 메모리 릭 방지
    }

    // 연산자 오버로딩, 클래스의 반복자(iterator)를 직접 구현함
    T *begin() { return data; }
    const T *begin() const { return data; }
    T *end() { return data + n; }
    const T *end() const { return data + n; }

    // 연산자 오버로딩, 두 배열을 + 연산할 수 있는 기능을 만든 것
    // friend: 특정 클래스나 함수가 다른 클래스의 private 또는 protected 멤버에 접근할 수 있도록 허용하는 데 사용됩니다.
    //         ?? private을 무시? 아무 조건 없이?
    friend dynamic_array<T> operator+(const dynamic_array<T>& arr1, dynamic_array<T>& arr2)
    {
        dynamic_array<T> result(arr1.size() + arr2.size());
        copy(arr1.begin(), arr1.end(), result.begin());
        copy(arr2.begin(), arr2.end(), result.begin() + arr1.size());

        return result;
    }

    // 매개변수에 기본값 줄 수 있네, Kotlin에서도 본 적 있음
    string to_string(const string& sep = ", ")
    {
        if (n == 0)
            return "";

        ostringstream oss;
        oss << data[0];

        for (int i = 1; i < n; i++)
            oss << sep << data[i];

        return oss.str();
    }
};

struct Student
{
    string name;
    int standard;
};

// 후.. 이건 또 뭐야? 알고 싶지 않아....
ostream& operator<<(ostream& os, const Student& s)
{
    return (os << "[" << s.name << ", " << s.standard << "]");
}


int main()
{
    int nStudents;
    cout << "1반 학생 수를 입력하세요: ";
    cin >> nStudents;

    dynamic_array<Student> class1(nStudents);
    for (int i = 0; i < nStudents; i++)
    {
        string name;
        int standard;
        cout << i + 1 << "번째 학생 이름과 나이를 입력하세요: ";
        cin >> name >> standard;
        class1[i] = Student{name, standard};
    }

    // 배열 크기보다 큰 인덱스의 학생에 접근
    try
    {
        // 아래 주석을 해제하면 프로그램이 비정상 종료합니다.
        // class1[nStudents] = student {"John", 8}; // 예상할 수 없는 동작

        class1.at(nStudents) = Student{"John", 8}; // 예외 발생
    }
    catch (...)
    {
        cout << "예외 발생!" << endl;
    }

    // 깊은 복사
    auto class2 = class1;
    cout << "1반을 복사하여 2반 생성: " << class2.to_string() << endl;

    // 두 학급을 합쳐서 새로운 큰 학급을 생성
    auto class3 = class1 + class2;
    cout << "1반과 2반을 합쳐 3반 생성 : " << class3.to_string() << endl;

    return 0;
}