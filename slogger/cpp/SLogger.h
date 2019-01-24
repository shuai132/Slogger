//
// Created by liushuai on 2019/1/16.
//

#ifndef SLOGGER_H
#define SLOGGER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void(*FileCallback)(const char *fileFullPath);
typedef void(*ErrorCallback)(const char *errorMsg);

/**
 * 初始化
 * @param logDir        日志存放目录
 * @param fileCallback  当停止记录后会产生回调(文件绝对路径)
 * @param errorCallback 错误回调
 */
void init(const char *logDir,
        FileCallback fileCallback,
        ErrorCallback errorCallback);

/**
 * 开始记录新日志
 */
void startRecord();

/**
 * 保证所有log记录完毕并产生文件回调
 */
void stopRecord();

/**
 * 记录日志(线程安全) 会自动换行
 */
void logTag(const char *tag, const char *msg);
void logMsg(const char *msg);

/**
 * @return socket端口号 用于nc等工具连接
 */
int getSocketPort();

#ifdef __cplusplus
}
#endif

#endif //SLOGGER_H
