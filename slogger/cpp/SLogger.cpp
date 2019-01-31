//
// Created by liushuai on 2019/1/16.
//

#include "SLogger.h"
#include "SocketLog.h"
#include "log.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/time.h>

using namespace std;

#ifndef NDEBUG
#define LOGD(fmt, ...)  LOG("slogger: " fmt, ##__VA_ARGS__)
#else
#define LOGD(fmt, ...)  ((void)0)
#endif

static auto socketLog = SocketLog::getInstance();
static std::string logDir;
static FileCallback fileCallback = nullptr;
static ErrorCallback errorCallback = nullptr;

static volatile bool recording = false;
static ofstream logFileNow;
static string logFileFullPathNow;


static bool initFile(const string &filePath) {
    logFileNow.open(filePath);
    LOGD("initFile: %s open state:%d", filePath.c_str(), logFileNow.is_open());
    auto isOpen = logFileNow.is_open();
    if (!isOpen && errorCallback) {
        errorCallback(("create/open file failed: " + filePath).c_str());
    }
    return isOpen;
}

static string getTimeStringNow() {
    time_t t = time(nullptr);
    char ch[64];
    strftime(ch, sizeof(ch), "%Y-%m-%d %H:%M:%S", localtime(&t));
    return ch;
}

static int getMsNow() {
    timeval timeNow;
    gettimeofday(&timeNow, nullptr);
    return timeNow.tv_usec;
}

void init(const char *dir, FileCallback fCallback, ErrorCallback eCallback) {
    LOGD("init: logDir: %s", dir);
    logDir = dir;
    if (dir[strlen(dir) - 1] != '/') {
        logDir += "/";
    }
    fileCallback = fCallback;
    errorCallback = eCallback;

    socketLog->setSendInterceptor([](const std::string& msg) {
        LOGD("onLog: %s", msg.c_str());
        if (recording) {
            logFileNow<<msg;
        }
        return false;
    });
}

void startRecord() {
    LOGD("startRecord");
    if (recording && logFileNow.is_open()) {
        socketLog->flush();
        logFileNow.close();
    }

    logFileFullPathNow = logDir + getTimeStringNow() + ".log";
    recording = initFile(logFileFullPathNow);
}

void stopRecord() {
    LOGD("stopRecord");
    if (!recording) return;

    socketLog->flush();
    logFileNow.close();
    if (fileCallback) {
        fileCallback(logFileFullPathNow.c_str());
    }
    recording = false;
}

void logTag(const char *tag, const char *msg) {
    std::ostringstream header;
    // header
    header<<getTimeStringNow()<<"."<<getMsNow();
    header<<" ";
    header<<std::this_thread::get_id();
    header<<" ";

    // tag
    header<<tag<<": ";

    // msg
    header<<msg<<endl;
    socketLog->post(header.str());
}

void logMsg(const char *msg) {
    logTag("", msg);
}

int getSocketPort() {
    return socketLog->getPort();
}
