# Echo Server

[English](#english) / [简体中文](#简体中文)

## English

This is a simple echo server written in C, based on epoll event handling, and supports non-blocking IO operations.

### Getting Started

These instructions will help you install and run the project on your local machine for development and testing.

#### Prerequisites

Make sure your system has the following software installed:

- GCC compiler
- GNU Make

#### Installation

Clone this repository to your local machine:

```bash
git clone https://yourrepository.git
```

Navigate to the project directory:

```bash
cd yourproject
```

Build the project:

```bash
make
```

#### Running

Start the server:

```bash
./echo_server [port]
```

#### Cleanup

Remove compiled files:

```bash
make clean
```

### Contributing

We welcome your contributions. Please discuss what you would like to change before submitting a pull request.

### License

This project is licensed under the MIT License. See the `LICENSE` file for details.

---

## 简体中文

这是一个简单的回声服务器，使用 C 语言编写，基于 epoll 事件处理，支持非阻塞 IO 操作。

### 开始

以下说明将帮助您在本地机器上安装和运行项目，进行开发和测试。

#### 先决条件

确保您的系统安装了以下软件：

- GCC 编译器
- GNU Make

#### 安装

克隆此仓库到本地机器：

```bash
git clone https://yourrepository.git
```

进入项目目录：

```bash
cd yourproject
```

编译项目：

```bash
make
```

#### 运行

启动服务器：

```bash
./echo_server [port]
```

#### 清理

清除编译生成的文件：

```bash
make clean
```

### 贡献

欢迎您的贡献。请先讨论您想要更改的内容，然后提交拉取请求。

### 版权和许可

本项目遵循 MIT 许可。有关详细信息，请参阅 `LICENSE` 文件。
