# Building Process

测试部分采用 C++11 标准，构建系统使用 CMake，使用 GTest 和 JSON 库。

## GTest library

For the first building, you have to uncomment a sequence of CMake commands between `###### uncomment` begin and `###### uncomment end`. 

For the later building and testing, you can comment these commands for high speed.

## JSON library

For the first building JSON, you have to clone the JSON repo into `test/json`:

```shell
git clone https://github.com/nlohmann/json.git --depth=1 test/json
```

This clone process could be very slow, therefore you may have some workaround.

After such two steps, everything done.