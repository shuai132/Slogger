//
// Created by liushuai on 2019/1/17.
//

#include "SLogger.h"

#include <string>
#include <iostream>
#include <thread>

using namespace std;
using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
    init("./", [](const char *fileFullPath) {
        cout<<"upload: "<<fileFullPath<<endl;
    }, [](const char *errorMsg) {
        cout<<"errorMsg:"<<endl;
    });

    cout<<"请使用如下命令连接nc:\n  nc localhost "<<getSocketPort()<<endl;
    //std::this_thread::sleep_for(std::chrono::seconds(5));

    startRecord();

    logMsg("中文测试");

    logMsg("thread safe test...");
    const auto COUNT_NUM = 100;
    auto thread1 = new thread([]{
        for (auto i = 0; i < COUNT_NUM; i++) {
            logTag("thread1", ("***hello:" + to_string(i)).c_str());
        }
    });
    auto thread2 = new thread([]{
        for (auto i = 0; i < COUNT_NUM; i++) {
            logTag("thread2", ("---world:" + to_string(i)).c_str());
        }
    });
    thread1->join();
    thread2->join();

    stopRecord();
}
