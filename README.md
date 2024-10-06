# web-server



### C++标准
  C++20··

### 编译环境
  centos 7
  gcc >= 11.2.1

```
.
├── build             目标文件
├── include           头文件
│   ├── db            数据库相关
│   │   ├── database.h
│   │   ├── sql.h
│   ├── json          json解析
│   │   ├── json.c
│   ├── log           日志相关
│   │   ├── log.h
│   ├── net           网络相关
│   │   ├── epoll.h
│   │   ├── http_server.h
│   │   ├── http.h
│   │   ├── socket.h
│   │   ├── tcp_server.h
│   ├── task          线程相关
│   │   ├── thread_pool.h
│   ├── time          计时相关
│   │   ├── timer.h
│   └── controller.h  总控试
├── src               与include下的文件一一对应
├── thirdlib          第三方库
├── main.cc
├── test.cc
├── test2.cc
├── makefile
├── LICENSE
└── readme.md
```
