```c
	   pipe() creates a pipe, a unidirectional data channel that can be
       used for interprocess communication.  The array pipefd is used to
       return two file descriptors referring to the ends of the pipe.
       pipefd[0] refers to the read end of the pipe.  pipefd[1] refers
       to the write end of the pipe.  Data written to the write end of
       the pipe is buffered by the kernel until it is read from the read
       end of the pipe.  For further details, see pipe(7).

       If flags is 0, then pipe2() is the same as pipe().  The following
       values can be bitwise ORed in flags to obtain different behavior:

       O_CLOEXEC
              Set the close-on-exec (FD_CLOEXEC) flag on the two new
              file descriptors.  See the description of the same flag in
              open(2) for reasons why this may be useful.

       O_DIRECT (since Linux 3.4)
              Create a pipe that performs I/O in "packet" mode.  Each
              write(2) to the pipe is dealt with as a separate packet,
              and read(2)s from the pipe will read one packet at a time.
              Note the following points:

              •  Writes of greater than PIPE_BUF bytes (see pipe(7))
                 will be split into multiple packets.  The constant
                 PIPE_BUF is defined in <limits.h>.

              •  If a read(2) specifies a buffer size that is smaller
                 than the next packet, then the requested number of
                 bytes are read, and the excess bytes in the packet are
                 discarded.  Specifying a buffer size of PIPE_BUF will
                 be sufficient to read the largest possible packets (see
                 the previous point).

              •  Zero-length packets are not supported.  (A read(2) that
                 specifies a buffer size of zero is a no-op, and returns
                 0.)

              Older kernels that do not support this flag will indicate
              this via an EINVAL error.

              Since Linux 4.5, it is possible to change the O_DIRECT
              setting of a pipe file descriptor using fcntl(2).

       O_NONBLOCK
              Set the O_NONBLOCK file status flag on the open file
              descriptions referred to by the new file descriptors.
              Using this flag saves extra calls to fcntl(2) to achieve
              the same result.

       O_NOTIFICATION_PIPE
              Since Linux 5.8, general notification mechanism is built
              on the top of the pipe where kernel splices notification
              messages into pipes opened by user space.  The owner of
              the pipe has to tell the kernel which sources of events to
              watch and filters can also be applied to select which
              subevents should be placed into the pipe.
```
