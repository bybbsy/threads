#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex m;

const int ARR_SIZE = 14;
const int AMOUNT_OF_THREADS = 5;

int numbers[ARR_SIZE] = { 1, 2, 3, 4, 5, 1234, 41, 12, 5, 5, 6, 7, 123214, 11 };


int getChunk() {
    return ARR_SIZE / AMOUNT_OF_THREADS;
}

int getRemainder() {
    return ARR_SIZE % AMOUNT_OF_THREADS;
}

bool isFinishIndex(int i) {
    return (i + 1) == AMOUNT_OF_THREADS;
}

void mult(int i, int current, int& accumulator) {
    std::lock_guard<std::mutex> guard(m);

    int chunk = getChunk();
    int remainder = getRemainder();
    int isFinishInd = isFinishIndex(i);

    if (isFinishInd && remainder > 0) {
        chunk += remainder;

        for (int j = i * (chunk - remainder); j < i * (chunk - remainder) + chunk; j++) {
            accumulator += numbers[j];
            std::cout << j << std::endl;
        }
    }
    else {
        for (int j = i * chunk; j < i * chunk + chunk; j++) {
            accumulator += numbers[j];
            std::cout << j << std::endl;
        }
    }

    std::cout << "CHUNK: " << chunk << " I: " << i << std::endl;
    std::cout << "First: " << i * chunk << " Second: " << i * chunk + chunk << std::endl;

    //123296

    //std::cout << "ID: " << i << " Acc: " << accumulator << std::endl;

    
}

void console(std::string name) {
    std::cout << name << std::endl;
}

int main()
{

    int accumulator = 0;

    //getRanges(ARR_SIZE, AMOUNT_OF_THREADS);

    

    std::vector<std::thread> threads;


    for (int i = 0; i < AMOUNT_OF_THREADS; i++) {
        threads.push_back(std::thread(mult, i, numbers[i], std::ref(accumulator)));
    }

    for (auto &th: threads) {
        th.join();
    }
   
    //thread.join();

    std::cout << accumulator << std::endl;
}