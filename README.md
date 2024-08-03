# Echo Server

这是一个简单的回声服务器，使用 C 语言编写，基于 epoll 事件处理，支持非阻塞 IO 操作。

## 开始

以下说明将帮助您在本地机器上安装和运行项目，进行开发和测试。

### 先决条件

确保您的系统安装了以下软件：

- GCC 编译器
- GNU Make

### 安装

克隆此仓库到本地机器：

```bash
git clone https://github.com/xywml/echo_server.git
```

进入项目目录：

```bash
cd yourproject
```

编译项目：

```bash
make
```

### 运行

启动服务器：

```bash
./echo_server [port]
```

### 清理

清除编译生成的文件：

```bash
make clean
```

## 贡献

欢迎您的贡献。请先讨论您想要更改的内容，然后提交拉取请求。

## 版权和许可

本项目遵循 MIT 许可。有关详细信息，请参阅 `LICENSE` 文件。
