# TCP Connect Port Scanner

A multi-threaded TCP Connect Port Scanner written in C that scans a range of TCP ports on a target host to determine whether they are open or closed. The scanner uses POSIX sockets for network communication, POSIX threads (`pthreads`) for concurrent scanning, and DNS resolution with `gethostbyname()` to resolve hostnames before attempting TCP connections.

This project was built as a learning exercise to understand low-level networking, socket programming, multithreading, and TCP communication in Linux.

---

## Features

- Scan a custom range of TCP ports
- Multi-threaded scanning using POSIX Threads (`pthreads`)
- Accepts both hostnames and IPv4 addresses
- Resolves hostnames using `gethostbyname()`
- Displays the resolved IP address before scanning
- Uses TCP `connect()` to determine whether a port is open
- Configurable socket timeout
- Lightweight implementation using POSIX sockets

---

## Technologies Used

- C
- GCC
- Linux
- POSIX Socket API
- POSIX Threads (pthreads)
- TCP/IP Networking

---

## Project Structure

```
tcp_port_scanner.c
```

---

## Compilation

Compile using GCC with pthread support:

```bash
gcc tcp_port_scanner.c -o tcp_port_scanner.out -pthread
```

---

## Usage

```bash
./tcp_port_scanner.out <hostname> <start_port> <end_port>
```

### Example

```bash
./tcp_port_scanner.out scanme.nmap.org 20 100
```

---

## Example Output

```
Beginning the scan!

Hostname: scanme.nmap.org
IP: 45.33.xxx.xxx

Port:22 is up...
Port:80 is up...
Port:53 is up...

Scan Complete
```

---

## How It Works

1. Accepts a hostname/IP address and port range from the command line.
2. Resolves the hostname using `gethostbyname()`.
3. Divides the specified port range into four equal chunks.
4. Creates four worker threads using `pthread_create()`.
5. Each thread scans its assigned range independently.
6. For each port:
   - Creates a TCP socket.
   - Sets socket send/receive timeouts.
   - Attempts a TCP connection using `connect()`.
   - Reports whether the port is open.
7. The main thread waits for all worker threads to finish using `pthread_join()`.
8. Prints **"Scan Complete"** when all threads have finished.

---

## Multithreading

To improve scanning speed, the scanner splits the target port range into four equal sections.

Each section is assigned to a separate thread, allowing multiple connection attempts to occur simultaneously.

Example:

```
Ports 1–100

Thread 1 → 1–25
Thread 2 → 26–50
Thread 3 → 51–75
Thread 4 → 76–100
```

This significantly reduces the overall scan time compared to sequential scanning.

---

## Concepts Practiced

- Socket Programming
- TCP/IP Networking
- POSIX Threads (`pthread_create`, `pthread_join`)
- DNS Resolution
- `gethostbyname()`
- `sockaddr_in`
- `connect()`
- `socket()`
- Socket Timeouts (`setsockopt()`)
- Network Byte Order (`htons()`)
- Memory Copy (`memcpy()`)
- Command-Line Arguments

---

## Limitations

Currently, the scanner:

- Supports IPv4 only
- Uses a fixed thread count (4 threads)
- Detects only whether a TCP port is open
- Does not identify running services
- Does not perform banner grabbing
- Does not support UDP scanning

---

## Future Improvements

- Configurable number of threads
- IPv6 support using `getaddrinfo()`
- Service detection
- Banner grabbing
- UDP port scanning
- Custom timeout values
- Better command-line argument parsing
- Export results to CSV or JSON
- Progress indicator
- Graceful interruption using `Ctrl+C`

---

## Disclaimer

This project is intended for educational purposes only.

Only scan systems that you own or have explicit permission to test.

Unauthorized port scanning may violate laws or network policies.

---

## Author

**Varun Singh**

GitHub: https://github.com/varun6532
