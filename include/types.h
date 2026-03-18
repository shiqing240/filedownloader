#pragma once

#include <atomic>

namespace dowmloader{

struct DownloadPart{
    // 分段的起始字节位置
    long long start = 0;
    // 分段的结束字节位置
    long long end = 0;
    // 已经下载的字节数（原子类型，多线程安全）
    std::atomic<long long> downloaded{0};
    // 该分段是否下载完成
    std::atomic<bool> finished{false};
    // 该分段是否下载成功
    std::atomic<bool> success{false};
    // 构造函数
    DownloadPart() = default;

    // 禁用拷贝构造和拷贝复制，防止多线程下载出现错乱
    DownloadPart(const DownloadPart&) = delete;
    DownloadPart& operator=(const DownloadPart&) = delete;
    
    // 使用移动构造函数进行赋值
    DownloadPart(DownloadPart&& other) noexcept
        :start(other.start)
        ,end(other.end)
        ,downloaded(other.downloaded.load())
        ,finished(other.finished.load())
        ,success(other.success.load())
    {

    }

    // 移动赋值运算符函数
    








};


};