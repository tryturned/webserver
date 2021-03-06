/*
 * @Autor: taobo
 * @Date: 2020-05-27 20:57:51
 * @LastEditTime: 2020-06-01 19:40:19
 * @Description: 日志类单元测试文件
 */
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include "../Log/AsyncLogging.h"
#include "../Log/Logger.h"
#include "../base/thread.h"

using namespace std;

int test_Logger()  //已经确保日志对外接口类Logger的运行正常
/*输出示例
2020-05-28 12:46:09
thread446_9 -- /home/go/webserver/Log/log_test.cpp:34
*/
{
  cout << __FILE__ << " " << __LINE__ << endl;
  for (int i = 0; i < 10000; ++i) {
    time_t rawtime;
    struct tm* ptm;
    rawtime = time(NULL);
    ptm = gmtime(&rawtime);
    char buf[24];
    sprintf(buf, "thread%d%d_%d", ptm->tm_mon, ptm->tm_min, ptm->tm_sec);
    LOG << buf;
  }
  cout << __FILE__ << " " << __LINE__ << endl;
  while (1)
    ;
  return 0;
}

int test_AsyncLogging()  //已经确保日志核心类AsyncLogging的运行正常
{
  AsyncLogging Log(string("log_527"));
  Log.start();
  for (int i = 0; i < 500; ++i) Log.append(string("2020_5_27_TaoBo\n"));
  Log.append(string("2020_5_28_TaoBo\n"));
  Log.append(string("2020_5_29_TaoBo\n"));
  Log.append(string("2020_5_30_TaoBo\n"));
  std::this_thread::sleep_for(chrono::seconds(2));
  for (int i = 0; i < 10000; ++i) {
    Log.append(string("TaoBo 123456 forever\n"));
  }
  while (1)
    ;
  return 0;
}