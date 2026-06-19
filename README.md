# UDP Server Client in C

A minimal UDP client-server implementation in C. The server listens for UDP messages on port `8080`, receives messages from a client, prints them to the terminal, and sends a reply back to the client.

## Features

- UDP socket communication using IPv4
- Simple server that listens on port `8080`
- Client sends a message to `127.0.0.1`
- Server replies after receiving the message
- Uses standard POSIX socket APIs

## Project Structure

```text
.
├── README.md
├── client.c
├── server.c
├── client
└── server
```

## Requirements

- Linux or Unix-like operating system
- GCC compiler
- Basic terminal access

## Build

Compile the server:

```sh
gcc server.c -o server
```

Compile the client:

```sh
gcc client.c -o client
```

Or compile both:

```sh
gcc server.c -o server
gcc client.c -o client
```

## Run

Start the server first:

```sh
./server
```

Expected output:

```text
UDP Server listening on port 8080...
```

In another terminal, run the client:

```sh
./client
```

Expected client output:

```text
Reply from server: Message Received(server)
```

Expected server output:

```text
Received from 127.0.0.1:<client-port> -> Hello, Server!
```

## How It Works

### Server

The server:

1. Creates a UDP socket using `socket()`
2. Binds the socket to port `8080`
3. Waits for incoming messages using `recvfrom()`
4. Prints the received message and client address
5. Sends a response back to the client using `sendto()`

### Client

The client:

1. Creates a UDP socket
2. Sets the server address to `127.0.0.1:8080`
3. Sends the message:

```text
Hello, Server!
```

4. Waits for the server response
5. Prints the reply

## Configuration

Both `client.c` and `server.c` define:

```c
#define PORT 8080
#define BUFFER_SIZE 1024
```

To use a different port, update `PORT` in both files and recompile.

## Notes

- UDP is connectionless, so no persistent connection is established between client and server.
- The server runs continuously in an infinite loop.
- Stop the server with:

```sh
Ctrl + C
```

## License

This project is intended for learning and experimentation.
