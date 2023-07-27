#include <iostream>
#include <cmath>
#include <thread>
#include <cstdio>
#include <ctime>
// 4х поточная программа по итогу на таком числе работает 18 - 20 секунд, а однопоточная 45 - 48 секунд. Cool, разница есть.

bool IsPrime(uint64_t x, uint64_t from, uint64_t to) {

    for (auto i = from; i < to; ++i) {
        if (x % i == 0) {
            return false;
        }
    }

    return true;
}

int main() {

    //unsigned int cpu_count = std::thread::hardware_concurrency(); 4 ядра у меня на ноутбуке.

    std::clock_t start;
    double duration;
    start = std::clock();

    uint64_t x = 18446744073709551557; // > 2^64 - 1. // 48 секунд работает однопоточный алгоритм.
    std::cout << IsPrime(x, 2, sqrt(x) + 6) << "\n";

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"printf: "<< duration <<'\n';

    /*
    std::clock_t start;
    double duration;
    start = std::clock();

    uint64_t x = 18446744073709551557; // big prime number; // 48 секунд работает один поток. го посмотрим на работу четырёх потоков.
    uint64_t root = sqrt(x);
    auto bound = std::min(root + 6, x);

    std::thread t1(IsPrime, x, 2, bound / 4);
    std::thread t2(IsPrime, x, bound / 4, bound / 2);
    std::thread t3(IsPrime, x, bound / 2, 3 * (bound / 4));
    std::thread t4(IsPrime, x, 3 * (bound / 4), bound);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"printf: "<< duration <<'\n';
    */
    return 0;
}
