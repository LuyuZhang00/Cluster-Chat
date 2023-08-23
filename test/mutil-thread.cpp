#include <iostream>
#include <semaphore.h>
#include <functional>
#include <thread>

using namespace std;

class Foo {
    sem_t sem_1, sem_2;
public:
    Foo() {
        sem_init(&sem_1, 0, 0);
        sem_init(&sem_2, 0, 0);
    }

    void first(function<void()> printFirst) {
        printFirst();
        sem_post(&sem_1);
    }

    void second(function<void()> printSecond) {
        sem_wait(&sem_1);
        printSecond();
        sem_post(&sem_2);
    }

    void third(function<void()> printThird) {
        sem_wait(&sem_2);
        printThird();
    }
};

int main() {
    Foo foo;

    auto printFirst = []() { cout << "first"<<endl; };
    auto printSecond = []() { cout << "second"<<endl; };
    auto printThird = []() { cout << "third"<<endl; };

    thread t1(&Foo::first, &foo, printFirst);
    thread t2(&Foo::second, &foo, printSecond);
    thread t3(&Foo::third, &foo, printThird);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}


