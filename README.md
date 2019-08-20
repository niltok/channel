# Channel

[![CircleCI](https://circleci.com/gh/goldimax/channel.svg?style=svg)](https://circleci.com/gh/goldimax/channel)

## Usage

```c++
#include "channel.hpp"

int main() {
    channel<int> ch; // define a channel which can pass int value
    auto listen = ch(); // get a listener
    ch << 42; // pass a value
    int recv;
    listen >> recv; // get a value
}
```