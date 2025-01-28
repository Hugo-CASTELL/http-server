# HTTP Server
![Language](https://img.shields.io/badge/language-C-blue?style=for-the-badge)
![Status](https://img.shields.io/badge/status-Working-brightgreen?style=for-the-badge)

I have developped this project in order to explore and learn more about how HTTP servers work under the hood. It is written with a focus on simplicity so on HTTP/1.1.
I have licensed it under MIT License so feel free to fork it, clone it and remodel it.

---

## 📖 Table of Contents

1. [💡 How It Works](#️-how-it-works)  
2. [📦 Setup](#-setup)  
3. [🚀 Usage](#-usage)

---

## 💡 How It Works

#### RFCs

HTTP/1.1 : [RFC 7230](https://www.rfc-editor.org/info/rfc7230) - [RFC 7231](https://www.rfc-editor.org/info/rfc7231) - [RFC 7232](https://www.rfc-editor.org/info/rfc7232) - [RFC 7233](https://www.rfc-editor.org/info/rfc7233) - [RFC 7234](https://www.rfc-editor.org/info/rfc7234) - [RFC 7235](https://www.rfc-editor.org/info/rfc7235)

#### Roadmap

A HTTP server has a basic and simple roadmap to follow.

1. Listens to a port for incoming HTTP request
    - [Handling TCP/IP incoming messages](#-Handling-TCP/IP)
2. 

#### Handling TCP/IP

In order to answer to incoming HTTP requests, we have to be able to listens to an opened port via a socket to receive the messages.
Via this socket, we will also send the responses.

1. Create the socket
```c
// In order to create the socket, I used the unix standard library socket. (man socket)
int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
```
2. Identify the socket
```c
// The socket is bound to a specific port (I used 4600 by default) using the bind() system call. (man bind)
bind(socket_fd, (struct sockaddr *)&address, address_len);
```
3. On the server, wait for an incoming connection
```c
// Now we have to listen for incoming connections using the listen() system call. (man listen)
listen(socket_fd, LISTEN_BACKLOG);
```
4. Send and receive messages
```c
// Once a connection request is detected on the listened port, we use accept to create a file descriptor and establish the connection. (man accept)
int connection_fd = accept(socket_fd, (struct sockaddr *)&address, &address_len);

// In the first scenario (commit below), I wrote a simple message as a response.
const char *message = "Hello from server!\n";
write(connection_fd, message, strlen(message));
```
5. Close the socket
```c
close(connection_fd);
close(socket_fd);`
```

For more informations, please check out this commit (file src/main.c) : 

---

## 📦 Setup  

#### Prerequisites  

- Compiler for C code (if using the C version): `gcc` or equivalent.

#### Installation  

1. Clone the repository:  
   ```sh
   git clone https://github.com/Hugo-CASTELL/http-server.git && cd http-server
   ```

2. (Optional) Remove the .git:  
   ```sh
   rm -r .git
   ```

#### Build

TODO Build

---

## 🚀 Usage

TODO Usage

---

## 🙏 Credits

[Skrew Everything](https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa)
[Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
