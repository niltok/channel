#include <iostream>
#include <random>
#include <thread>
#include <vector>
#include <cassert>

#include "channel.hpp"

const int size = 1e6;
const int threads = 4;

int main() {
    channel<unsigned int> ch;
    std::vector<unsigned int> send(size);
    std::random_device random;
    for (auto &i : send) i = random();
    std::vector<std::vector<unsigned int>> resv(threads);
    std::vector<std::thread> pool(threads);
    for (int i = 0; i < threads; i++) {
        auto out = ch();
        pool[i] = std::thread(
            [&resv, i](channel<unsigned int>::listener out) {
                for (int j = 0; j < size; j++) resv[i].push_back(out());
            },
            out);
    }
    for (auto &i : send) ch << i;
    for (auto &t : pool)
        if (t.joinable()) t.join();
    for (auto &v : resv) {
        for (int i = 0; i < size; i++) assert(v[i] == send[i]);
    }
}