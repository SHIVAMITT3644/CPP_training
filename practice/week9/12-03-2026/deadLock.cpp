#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex m1;
std::mutex m2;

void thread1() {
    m1.lock();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    m2.lock();

    std::cout << "Critical Section Of Thread One\n";

    m2.unlock();
    m1.unlock();
}

void thread2() {
    m2.lock();
    // std::this_thread::sleep_for(std::chrono::seconds(2));
    m1.lock();

    std::cout << "Critical Section Of Thread Two\n";

    m1.unlock();
    m2.unlock();
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();

    return 0;
}