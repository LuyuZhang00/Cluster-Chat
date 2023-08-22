#include <iostream>
#include <thread>
#include <string>
#include <mutex>

using namespace std;

std::mutex mtx;  // 创建一个互斥锁

void thread_one()
{
    mtx.lock();  // 获取锁
    puts("hello");
    mtx.unlock();  // 释放锁
}

void thread_two(int num, string& str)
{
    mtx.lock();  // 获取锁
    cout << "num:" << num << ",name:" << str << endl;
    mtx.unlock();  // 释放锁
}

int main(int argc, char* argv[])
{
    thread tt(thread_one);
    string str = "luckin";
    thread yy(thread_two, 88, ref(str));

    tt.join();  // 等待 tt 线程完成
    yy.join();  // 等待 yy 线程完成

    return 0;
}
