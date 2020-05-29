/*
 * @Autor: taobo
 * @Date: 2020-05-29 22:42:19
 * @LastEditTime: 2020-05-29 22:51:55
 */ 
#include <memory>
#include <vector>
#include "EventLoop.h"
#include "EventLoopThread.h"
#include "ThreadPool.h"

using namespace std;

ThreadPool::ThreadPool(EventLoop* base, int nums):baseloop_(base),
numThreads_(nums), next_(0),
started_(false){}
void ThreadPool::start()
{
    started_ = true;
    for(int i=0;i<numThreads_;++i)
    {
        sp_evthread tmp(new EventLoopThread());
        threads_.push_back(tmp);
        loops_.push_back(tmp->startLoop());
    }
}
EventLoop* ThreadPool::getNextLoop()
{
    if(!started_) return nullptr;
    EventLoop* p = baseloop_;
    if(!loops_.empty())
    {
        p = loops_[next_];
        next_ = (next_+1)%numThreads_;
    }
    return p;
}