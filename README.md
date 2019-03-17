# Slogger

Safer Logger tools for Android/iOS

## Why
所有基于Android logcat日志系统输出的工具，都会存在日志丢失的问题，在多线程切并发输出时尤为明显。
在一些严格的测试场景，非常依赖日志的完整性。这种场景下logcat的输出是不可信的。
另一方面iOS没有一个运行时观察日志的机制。

所以需要一个安全的日志工具，保证日志信息的完整性。

## Feature
* 高性能，C++实现、线程安全。
* 支持Android(Java和NDK)、支持iOS。
* 支持通过nc等TCP工具实时查看日志并支持多个观察者。
* 支持日志文件保存。

## Usage:
* Android

添加jitpack仓库后:
```groovy
implementation "com.github.shuai132:Slogger:${commitid}"
```
Java API:
```java
public static native void logTag(String tag, String msg);
public static native void logMsg(String msg);
```

* iOS

通过导入[slooger/cpp]目录下的源码

C API:
```c
void logTag(const char *tag, const char *msg);
void logMsg(const char *msg);
```

* 完整的测试用例见: [slogger/cpp/SLogger_test.cpp]

## Links
* [SocketLog](https://github.com/shuai132/SocketLog)
