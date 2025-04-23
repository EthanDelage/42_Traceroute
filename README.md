# ft_traceroute

This is a project for the 42 school which implements a simple traceroute utility in C.

## Usage

```bash
Usage: ft_traceroute [-?] [-f first_ttl] [-m max_ttl] [-p port] [-q nqueries]
            [-w MAX] [--first=first_ttl] [--max-hop=max_ttl] [--port=port]
            [--queries=nqueries] [--wait=MAX] [--help] [--usage]
            host [packet_len]
```

## Options

| Short opt | Long opt             | Description                                                                   |
|:---------:|----------------------|-------------------------------------------------------------------------------|
|   `-m`    | `--max-hop=max_ttl`  | Set the max number of hops (max TTL to be reached). Default is 30             |
|   `-q`    | `--queries=nqueries` | Set the number of probes per each hop. Default is 3                           |
|   `-f`    | `--first=first_ttl`  | Start from the first_ttl hop (instead from 1)                                 |
|   `-p`    | `--port=port`        | Set the destination port to use (incremented by each probe, default is 33434) |
|   `-w`    | `--wait=MAX`         | Wait for a probe no more than MAX (default 5.0) seconds                       |
|   `-?`    | `--help`             | Give this help list                                                           |
|           | `--usage`            | Give a short usage message                                                    |

## Description
The ft_traceroute command traces the route that packets take from the source to a destination host, reporting each hop along the way. It simulates the behavior of the standard `traceroute` utility, with basic functionality to trace the path of the packets.

The command sends packets with increasing TTL (Time-to-Live) values and measures the response times from intermediate routers, allowing you to observe the network path and identify where delays or failures occur.

## Examples

Trace the route to example.com with the default settings (30 hops max, UDP packets):

```bash
./ft_traceroute example.com
```

## Build Instructions
To build the ft_traceroute executable, use make:

```bash
make
```

This will compile the source code and produce the ft_traceroute executable.

## Requirements
This project requires a Unix-like system capable of sending and receiving raw packets (UDP or ICMP).

Root privileges might be required for some functionalities (e.g., raw socket creation).

## Author
This project was developed by **edelage**.

## Disclaimer
Use this software responsibly and only on networks and hosts that you have permission to test.

Network probing tools like traceroute can be subject to security policies and legal regulations. Ensure you have the proper authorization before testing any network.
