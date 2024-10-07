# web-server

## 项目介绍
- 利用IO复用技术Epoll与线程池实现多线程的Reactor高并发模型；
- 实现了http协议，以解析网页动态的请求；
- 基于set实现的定时器，关闭超时的非活动连接；
- 利用RAII机制实现了数据库，同时实现了用户注册登录功能；


---

### C++标准
  C++20<br>

### 编译环境
  centos 7<br>
  gcc >= 11.2.1<br>

---

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
├── test              单元测试
├── makefile
├── LICENSE
└── README.md
```
