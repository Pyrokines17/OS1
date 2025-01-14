- [различия между udp и tcp](https://www.techtarget.com/searchnetworking/definition/UDP-User-Datagram-Protocol#:~:text=User%20Datagram%20Protocol%20(UDP)%20is,receiving%20party%20provides%20an%20agreement.)

---

```c
struct sockaddr_in {
           sa_family_t     sin_family;     /* AF_INET */
           in_port_t       sin_port;       /* Port number */
           struct in_addr  sin_addr;       /* IPv4 address */
       };
```

---

```c
socket() creates an endpoint for communication and returns a file
       descriptor that refers to that endpoint.  The file descriptor
       returned by a successful call will be the lowest-numbered file
       descriptor not currently open for the process.

       The domain argument specifies a communication domain; this
       selects the protocol family which will be used for communication.
       These families are defined in <sys/socket.h>.  The formats
       currently understood by the Linux kernel include:
       Name         Purpose                                    Man page
       AF_UNIX      Local communication                        unix(7)
       AF_LOCAL     Synonym for AF_UNIX
       AF_INET      IPv4 Internet protocols                    ip(7)
       AF_AX25      Amateur radio AX.25 protocol               ax25(4)
       AF_IPX       IPX - Novell protocols
       AF_APPLETALK AppleTalk                                  ddp(7)
       AF_X25       ITU-T X.25 / ISO-8208 protocol             x25(7)
       AF_INET6     IPv6 Internet protocols                    ipv6(7)
       AF_DECnet    DECet protocol sockets
       AF_KEY       Key management protocol, originally
                    developed for usage with IPsec
       AF_NETLINK   Kernel user interface device               netlink(7)
       AF_PACKET    Low-level packet interface                 packet(7)
       AF_RDS       Reliable Datagram Sockets (RDS) protocol   rds(7)
                                                               rds-rdma(7)
       AF_PPPOX     Generic PPP transport layer, for setting
                    up L2 tunnels (L2TP and PPPoE)
       AF_LLC       Logical link control (IEEE 802.2 LLC)
                    protocol
       AF_IB        InfiniBand native addressing
       AF_MPLS      Multiprotocol Label Switching
       AF_CAN       Controller Area Network automotive bus
                    protocol
       AF_TIPC      TIPC, "cluster domain sockets" protocol
       AF_BLUETOOTH Bluetooth low-level socket protocol
       AF_ALG       Interface to kernel crypto API
       AF_VSOCK     VSOCK (originally "VMWare VSockets")       vsock(7)
                    protocol for hypervisor-guest
                    communication
       AF_KCM       KCM (kernel connection multiplexer)
                    interface
       AF_XDP       XDP (express data path) interface
```

---

```c
When a socket is created with socket(2), it exists in a name
       space (address family) but has no address assigned to it.  bind()
       assigns the address specified by addr to the socket referred to
       by the file descriptor sockfd.  addrlen specifies the size, in
       bytes, of the address structure pointed to by addr.
       Traditionally, this operation is called “assigning a name to a
       socket”.

       It is normally necessary to assign a local address using bind()
       before a SOCK_STREAM socket may receive connections (see
       accept(2)).

       The rules used in name binding vary between address families.
       Consult the manual entries in Section 7 for detailed information.
       For AF_INET, see ip(7); for AF_INET6, see ipv6(7); for AF_UNIX,
       see unix(7); for AF_APPLETALK, see ddp(7); for AF_PACKET, see
       packet(7); for AF_X25, see x25(7); and for AF_NETLINK, see
       netlink(7).

       The actual structure passed for the addr argument will depend on
       the address family.  The sockaddr structure is defined as
       something like:

           struct sockaddr {
               sa_family_t sa_family;
               char        sa_data[14];
           }

       The only purpose of this structure is to cast the structure
       pointer passed in addr in order to avoid compiler warnings.  See
       EXAMPLES below.
```

---

```c
The recvfrom() function shall receive a message from a
       connection-mode or connectionless-mode socket. It is normally
       used with connectionless-mode sockets because it permits the
       application to retrieve the source address of received data.

       The recvfrom() function takes the following arguments:

       socket      Specifies the socket file descriptor.

       buffer      Points to the buffer where the message should be
                   stored.

       length      Specifies the length in bytes of the buffer pointed
                   to by the buffer argument.

       flags       Specifies the type of message reception. Values of
                   this argument are formed by logically OR'ing zero or
                   more of the following values:

                   MSG_PEEK    Peeks at an incoming message. The data is
                               treated as unread and the next recvfrom()
                               or similar function shall still return
                               this data.

                   MSG_OOB     Requests out-of-band data. The
                               significance and semantics of out-of-band
                               data are protocol-specific.

                   MSG_WAITALL On SOCK_STREAM sockets this requests that
                               the function block until the full amount
                               of data can be returned. The function may
                               return the smaller amount of data if the
                               socket is a message-based socket, if a
                               signal is caught, if the connection is
                               terminated, if MSG_PEEK was specified, or
                               if an error is pending for the socket.

       address     A null pointer, or points to a sockaddr structure in
                   which the sending address is to be stored. The length
                   and format of the address depend on the address
                   family of the socket.

       address_len Either a null pointer, if address is a null pointer,
                   or a pointer to a socklen_t object which on input
                   specifies the length of the supplied sockaddr
                   structure, and on output specifies the length of the
                   stored address.
```

---

```c
The sendto() function shall send a message through a connection-
       mode or connectionless-mode socket.

       If the socket is a connectionless-mode socket, the message shall
       be sent to the address specified by dest_addr if no pre-specified
       peer address has been set. If a peer address has been pre-
       specified, either the message shall be sent to the address
       specified by dest_addr (overriding the pre-specified peer
       address), or the function shall return -1 and set errno to
       [EISCONN].

       If the socket is connection-mode, dest_addr shall be ignored.

       The sendto() function takes the following arguments:

       socket      Specifies the socket file descriptor.

       message     Points to a buffer containing the message to be sent.

       length      Specifies the size of the message in bytes.

       flags       Specifies the type of message transmission. Values of
                   this argument are formed by logically OR'ing zero or
                   more of the following flags:

                   MSG_EOR       Terminates a record (if supported by
                                 the protocol).

                   MSG_OOB       Sends out-of-band data on sockets that
                                 support out-of-band data. The
                                 significance and semantics of out-of-
                                 band data are protocol-specific.

                   MSG_NOSIGNAL  Requests not to send the SIGPIPE signal
                                 if an attempt to send is made on a
                                 stream-oriented socket that is no
                                 longer connected. The [EPIPE] error
                                 shall still be returned.

       dest_addr   Points to a sockaddr structure containing the
                   destination address. The length and format of the
                   address depend on the address family of the socket.

       dest_len    Specifies the length of the sockaddr structure
                   pointed to by the dest_addr argument.
```

---

```c
listen() marks the socket referred to by sockfd as a passive
       socket, that is, as a socket that will be used to accept incoming
       connection requests using accept(2).

       The sockfd argument is a file descriptor that refers to a socket
       of type SOCK_STREAM or SOCK_SEQPACKET.

       The backlog argument defines the maximum length to which the
       queue of pending connections for sockfd may grow.  If a
       connection request arrives when the queue is full, the client may
       receive an error with an indication of ECONNREFUSED or, if the
       underlying protocol supports retransmission, the request may be
       ignored so that a later reattempt at connection succeeds.
```

---