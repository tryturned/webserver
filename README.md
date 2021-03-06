<!--
 * @Autor: taobo
 * @Date: 2020-06-01 23:18:18
 * @LastEditTime: 2020-12-22 13:47:09
 * @Description: file content
--> 
# webserver [![Build Status](https://travis-ci.com/tryturned/webserver.svg?branch=main)](https://travis-ci.com/tryturned/webserver)

项目测试页面：[http://47.93.13.231/notes](http://47.93.13.231/notes)


#### 介绍
使用C++11 编写的静态服务器，简单解析了get、head请求，丢弃了post请求， 在阅读《Linux多线程服务端编程》之后，参考了[muduo](https://github.com/chenshuo/muduo) 与 linya的[WebServer](https://github.com/linyacool/WebServer)日志实现方式，实现了自己的异步日志模块。    

[测试截图](https://gitee.com/windyGOlife/webserver/blob/master/example/test_page.png)  
**软件架构**
| Part Ⅰ | Part Ⅱ | Part Ⅲ | Part Ⅳ | Part Ⅴ | 
| :--------: | :---------: | :---------: | :---------: | :---------: | 
| [Reactor模型](./Reactor)|[异步日志](./Log)|[历史版本](https://gitee.com/windyGOlife/webserver/tree/master) | [测试](./WebBench/测试.md) | [总结](./总结.md)   

**本机环境**
* OS:  Ubuntu 18.04.3 LTS
* Complier: gcc version 7.4.0  

**安装教程**  
```powershell
git clone git@gitee.com:windyGOlife/webserver.git
cd webserver
make
./main -p(port) -l(logfilename) -t(threadnum)
```
或者：  
直接使用vscode打开webserver文件夹，进入main.cpp文件之后按`Ctrl+Shift+B`一键构建

**使用说明**

1.  考虑服务器的安全性问题与资源开销，使用多线程以充分利用多核CPU，并使用线程池避免线程频繁创建销毁的开销
2.  基于one loop per thread 模式为网络框架的核心
3.  使用基于`std::priority_queue`的定时器来管理tcp连接，以及时处理超时请求
4.  使用Epoll的ET触发模式 + 非阻塞IO处理连接请求
5.  采取轮询的方式将IO请求分发给某一个IO线程
6.  对资源的管理，大多使用RAII等机制
7.  相比前面的版本(基于C) ，本次使用eventfd 取代socketpair唤醒线程，使用更加简便

**代码统计**  
![cloc](https://gitee.com/windyGOlife/webserver/raw/master/example/code.png)
