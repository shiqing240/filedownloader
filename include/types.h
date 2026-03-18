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
    DownloadPart& operator=(DownloadPart&& other) noexcept
    {
        // 防止自赋值
        if(this != &other)
        {
            start = other.start;
            end = other.end;
            downloaded.store(other.downloaded.load());
            finished.store(other.finished.load());
            success.store(other.success.load());
        }
        return *this;
    }
    
};

struct HeaderInfo{
    // 文件总长度：字节
    long long content_length = 0;
    // 服务器是否支持范围请求（即是否能分段下载）
    bool accept_ranges = false;
};

struct WriteContext{
    // 文件描述符
    int fd = -1;
    // 本次写入的字节偏移量
    long long offset = 0;
    // 关联的下载分段
    DownloadPart* part = nullptr;
    // 全局已下载总字节数（原子类型指针，用于统计整体进度）
    std::atomic<long long>* total_downloaded = nullptr;
};


} // namespace dowmloader