#include "types.h"

#include <string>
#include <vector>

namespace downloader{

class Downloader
{
public:
    // 构造函数
    Downloader(const std::string& url , const std::string& output , int thread_num = 4)
    :url_(url)
    ,output_(output)
    ,thread_num_(thread_num)
    {

    }




private:
    std::string url_;       // 下载链接
    std::string output_;    // 输出文件路径
    int thread_num_ = 4;    // 下载线程数，默认为4

    // 文件信息
    long long content_length_ = 0; // 文件总长度
    bool support_range_ = false;   // 是否支持范围请求
    int fd_ = -1;              // 文件描述符    

    // 下载状态管理
    std::vector<DownloadPart> parts_; // 分段信息
    std::atomic<long long> total_downloaded_{0};  // 全局已下载的总共字节数
    


};







}