
| Name           | Function      |
| -------------- | ------------- |
| DNS_struct. h  | dns 报文结构      |
| DNS_convert. h | 字节流和报文流转换     |
| DNS_print. h   | dns 字节流、报文流输出 |
| \*\*. h        | cache 存储使用的结构 |
| DNS_cache. h   | dns 存储 cache  |
| DNS_server. h  | 服务端           |
|                |               |
这是一段使用 C 语言结合 Winsock API 编写的网络通信程序，专门针对非阻塞和阻塞模式进行数据接收和处理的功能实现。以下是对这段代码的详细逐行注释和解释：

### 非阻塞模式 `setNonBlockingMode()`
```c
// 尝试将服务器和客户端套接字设置为非阻塞模式
if (ioctlsocket(serverSocket, FIONBIO, &socketMode) != 0 ||
    ioctlsocket(clientSocket, FIONBIO, &socketMode) != 0) {
    fprintf(stderr, "Failed to set non-blocking socketMode: %d\n\n", WSAGetLastError());
    closesocket(serverSocket);
    closesocket(clientSocket);
    WSACleanup();
    exit(EXIT_FAILURE);
}
```
- `ioctlsocket(serverSocket, FIONBIO, &socketMode)`: 使用 `ioctlsocket` 函数将 `serverSocket` 设置为非阻塞模式。`FIONBIO` 是控制码，指示将套接字设置为非阻塞。
- `&socketMode`: 指向 `socketMode` 变量的指针，用于控制套接字的阻塞/非阻塞模式。
- 如果设置失败，将输出错误信息，关闭套接字，清理 Winsock 资源，并退出程序。

```c
// 在非阻塞模式下，循环接收来自客户端和服务器的数据
while (1) {
    receive_client();  // 接收来自客户端的数据
    receive_server();  // 接收来自服务器的数据
}
```
- 进入无限循环，持续处理来自客户端和服务器的数据。
- `receive_client()`: 处理从客户端接收到的数据。
- `receive_server()`: 处理从服务器接收到的数据。
- 由于套接字是非阻塞的，这些函数将立即返回，即使没有数据可读。这允许程序继续执行而不会停顿在某个套接字操作上。

### 阻塞模式 `setBlockingMode()`
```c
// 使用WSAPoll进行阻塞模式下的事件监听
struct pollfd fds[2];
fds[0].fd = clientSocket;
fds[0].events = POLLIN;
fds[1].fd = serverSocket;
fds[1].events = POLLIN;
```
- 定义一个 `pollfd` 结构体数组，用于存储需要监听的套接字和事件类型。
- `fds[0].fd = clientSocket;` 和 `fds[1].fd = serverSocket;`: 设置需要监听的套接字。
- `fds[0].events = POLLIN;` 和 `fds[1].events = POLLIN;`: 指定监听的事件类型为 "可读"（有数据可读或连接已建立）。

```c
// 循环等待直到有事件发生
while (1) {
    int ret = WSAPoll(fds, 2, -1);
    if (ret == SOCKET_ERROR) {
        fprintf(stderr, "WSAPoll failed: %d\n", WSAGetLastError());
        closesocket(serverSocket);
        closesocket(clientSocket);
        WSACleanup();
        exit(EXIT_FAILURE);
    } else if (ret > 0) {
        if (fds[0].revents & POLLIN) {
            receive_client(); // 处理客户端事件
        }
        if (fds[1].revents & POLLIN) {
            receive_server(); // 处理服务器事件
        }
    }
}
```
- `WSAPoll(fds, 2, -1)`: 调用 `WSAPoll` 等待 `fds` 中列出的套接字上的事件。`-1` 参数表示无限等待，直到有事件发生。
- 如果 `WSAPoll` 返回错误，将输出错误信息，关闭套接字，清理 Winsock 资源，并退出程序。
- 如果检测到事件 (`ret > 0`)，检查具体是哪个套接字有事件，并调用相应的处理函数。

### 总结两种模式的实现原理和流程：
**非阻塞模式：**
- 套接字在操作时不会等待（例如，数据的到来），允许程序继续执行其他任务。
- 非阻塞模式适用于需要处理多个并发操作而不阻塞程序执行的场景。

**阻塞模式：**
- 套接字操作会阻塞程序的执行，直到操作完成（例如，数据到达套接字）。
- 阻塞模式适合程序顺序执行时简化代码逻辑，因为在一个操作完成之前，程序不会继续到下一个操作。

这两种模式的选择依赖于应用程序的具体需求和预期的用户体验。