// Homework13.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include<iostream>
#include<thread>
#include <Windows.h>
#include <chrono>
#include "Timer.h"
#include <atomic>
#include <mutex>

std::mutex m;

void window(std::atomic<int>& queue) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    while (queue != 0) {
        queue.store((queue - 1), std::memory_order_relaxed);
        m.lock();
        consol_parameter::SetColor(15, 0);
        std::cout << "One client served! Queue is: " << queue.load() << std::endl;
        m.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

}
void peoples(std::atomic<int>& queue, const std::atomic<int>& maxqueine) {
    int queinecounts = 0;
    while (queinecounts < maxqueine) {
        queue.store((queue + 1), std::memory_order_relaxed);
        queinecounts++;
        m.lock();
        consol_parameter::SetColor(10, 0);
        std::cout << "One more clients! Queue is: " << queue.load() << std::endl;
        m.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    queue.store((queue + 1), std::memory_order_relaxed);
    queinecounts++;
    consol_parameter::SetColor(11, 0);
    std::cout << "Lastone client is here! Queue is: " << queue.load() << std::endl;
}

int main()
{
    std::atomic<int> queue = 0;
    const std::atomic<int> maxqueue = 25;
    std::thread t1(window, std::ref(queue));
    std::thread t2(peoples, std::ref(queue), std::ref(maxqueue));
    t1.join();
    t2.join();

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
