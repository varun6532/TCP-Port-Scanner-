# TCP Connect Port Scanner

A simple TCP Connect Port Scanner written in C that scans a range of TCP ports on a target host to determine whether they are open or closed. The project uses POSIX socket programming and DNS resolution with `gethostbyname()` to resolve hostnames before attempting TCP connections.

This project was built as a learning exercise to understand low-level networking, socket programming, and TCP communication in Linux.

---

## Features

- Scan a custom range of TCP ports
- Accepts both hostnames and IPv4 addresses
- Resolves hostnames using `gethostbyname()`
- Displays the resolved IP address before scanning
- Uses TCP `connect()` to determine whether a port is open
- Configurable connection timeout
- Lightweight implementation using POSIX sockets

---

## Technologies Used

- C
- GCC
- Linux
- POSIX Socket API
- TCP/IP Networking

---

## Project Structure

```
tcp_port_scanner.c
```

---

## Compilation

Compile the project using GCC:

```bash
gcc tcp_port_scanner.c -o tcp_port_scanner.out
```

---

## Usage

```bash
./tcp_port_scanner.c <hostname> <start_port> <end_port>
```

Example:

```bash
./tcp_port_scanner.out google.com 80 100
```

Example Output:

```
Beginning the scan.....

Hostname: google.com
IP: 142.250.xxx.xxx

Port: 80 is UP....
Port: 81 is DOWN....
Port: 82 is DOWN....
...
```

---

## How It Works

1. Accepts a hostname or IP address from the command line.
2. Resolves the hostname using `gethostbyname()`.
3. Converts the resolved address into a socket address.
4. Iterates through the specified port range.
5. Creates a TCP socket for each port.
6. Attempts to establish a TCP connection using `connect()`.
7. Reports whether each port is open or closed.

---

## Concepts Practiced

- Socket Programming
- TCP/IP Networking
- DNS Resolution
- `gethostbyname()`
- `sockaddr_in`
- `connect()`
- `socket()`
- Network Byte Order (`htons()`)
- Memory Management (`memcpy()`)
- Command-Line Arguments
- Connection Timeouts

---

## Limitations

This project currently:

- Supports IPv4 only
- Performs sequential (single-threaded) scanning
- Detects only whether a TCP port is open or closed
- Does not perform service detection or banner grabbing

---

## Future Improvements

- Multi-threaded scanning
- IPv6 support using `getaddrinfo()`
- Service detection
- Banner grabbing
- Custom timeout values
- Better command-line options
- Export scan results to a file

---

## Disclaimer

This project is intended for educational purposes only.

Only scan systems that you own or have explicit permission to test.

Unauthorized port scanning may violate laws or network policies.

---

## Author

**Varun Singh**

GitHub: https://github.com/varun6532
