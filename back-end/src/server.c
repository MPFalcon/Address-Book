#include "server.h"

#define GLB_PORT                      (uint16_t)31337U
#define MAX_PORT_STR_LEN              6
#define BACKLOG_CAPACITY              10
#define TIMEOUT                       -1
#define DEFAULT_OPT                   1
#define HOST_NAME_LEN                 255
#define MAX_ALLOWED_OPERATION_MSG_LEN 10

/**
 * @brief Attempt to bind the server socket to an address.
 *
 * @param server_sock The server socket file descriptor.
 * @return 0 on success, -1 on failure.
 */
static int attempt_binding(int server_sock)
{
    int status_code = FAILURE;

    socklen_t server_addr_len = sizeof(struct sockaddr_in);

    struct addrinfo * results                       = NULL;
    struct addrinfo * curr_results                  = NULL;
    struct addrinfo   hints                         = { 0 };
    char              port_buffer[MAX_PORT_STR_LEN] = { 0 };

    hints.ai_flags    = 1;
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_IP;

    (void)snprintf(port_buffer, MAX_PORT_STR_LEN, "%hu", GLB_PORT);

    if (SUCCESS != getaddrinfo("0.0.0.0", port_buffer, &hints, &results))
    {
        ERRORPRINTF(getaddrinfo());
        goto EXIT;
    }

    for (curr_results = results; curr_results != NULL;
         curr_results = curr_results->ai_next)
    {
        // Attempt to bind sockaddr struct information
        // to file descriptor on system

        status_code = bind(server_sock, curr_results->ai_addr, server_addr_len);
        if (SUCCESS == status_code)
        {
            break;
        }
    }

    DEBUGPRINTF("Successfully bound socket");

    if (SUCCESS != status_code)
    {
        goto CLEAN;
    }

    status_code = SUCCESS;
CLEAN:
    if (NULL != results)
    {
        freeaddrinfo(results);
    }

EXIT:
    return status_code;
}

/**
 * @brief Set up the server socket.
 *
 * @return The file descriptor of the server socket on success, -1 on failure.
 */
static int server_setup()
{
    int  status_code            = FAILURE;
    int  server_sock            = 0;
    int  opt                    = DEFAULT_OPT;
    char ip_addr[HOST_NAME_LEN] = { 0 };

    // Ensure address and socket can be used again
    server_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (ERROR == server_sock)
    {
        ERRORPRINTF(socket());
        goto EXIT;
    }

    if (SUCCESS !=
        setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        ERRORPRINTF(setsockopt());
        goto EXIT;
    }

    // Start attempting a bind between the server socket and the IP address
    if (SUCCESS != attempt_binding(server_sock))
    {
        ERRORPRINTF(attempt_binding());
        goto EXIT;
    }

    if (SUCCESS != gethostname(ip_addr, HOST_NAME_LEN))
    {
        ERRORPRINTF(gethostname());
        goto EXIT;
    }

    DEBUGPRINTF("Server started on hostname \"%s\" running on port %hu",
                ip_addr,
                GLB_PORT);

    if (ERROR == listen(server_sock, BACKLOG_CAPACITY))
    {
        ERRORPRINTF(listen());
        goto EXIT;
    }

    status_code = SUCCESS;
EXIT:
    if (SUCCESS != status_code)
    {
        server_sock = ERROR;
    }

    return server_sock;
}

int start_server(void)
{
    fd_set             read_fds   = { 0 };
    fd_set             master_fds = { 0 };
    struct timeval     timeout    = { .tv_sec = (time_t)TIMEOUT, .tv_usec = 0 };
    ssize_t            bytes      = 0;
    struct sockaddr_in client_addrinfo     = { 0 };
    socklen_t          client_addrinfo_len = sizeof(client_addrinfo);
    char               operation_buffer[MAX_ALLOWED_OPERATION_MSG_LEN] = { 0 };
    char               addr_str[INET_ADDRSTRLEN]                       = { 0 };
    int                status_code = FAILURE;
    int                sock_fd     = server_setup();
    if (ERROR == sock_fd)
    {
        ERRORPRINTF(server_setup());
        goto EXIT;
    }

    // Initialize the master file descriptor set and add the server socket to it
    FD_ZERO(&master_fds);
    FD_SET(sock_fd, &master_fds);
    while (1)
    {
        // Copy the master file descriptor set to the read file descriptor set
        read_fds = master_fds;
        if (ERROR == select(FD_SETSIZE, &read_fds, NULL, NULL, NULL))
        {
            ERRORPRINTF(select());
            continue;
        }
        // Iterate through the file descriptors to check for ready sockets
        for (int if_idx = 0; if_idx < FD_SETSIZE; if_idx++)
        {
            if (FD_ISSET(if_idx, &read_fds))
            {
                DEBUGPRINTF("Ready to read from FD %d", if_idx);
                if (if_idx == sock_fd)
                {
                    DEBUGPRINTF("Server Pinged");
                    // Accept a new connection on the server socket
                    int conn_fd = accept(sock_fd,
                                         (struct sockaddr *)&client_addrinfo,
                                         &client_addrinfo_len);
                    if (ERROR == conn_fd)
                    {
                        ERRORPRINTF(accept());
                    }
                    else
                    {
                        inet_ntop(AF_INET,
                                  &(client_addrinfo.sin_addr),
                                  addr_str,
                                  INET_ADDRSTRLEN);
                        DEBUGPRINTF("Connection received - %s:%d",
                                    addr_str,
                                    client_addrinfo.sin_port);
                        FD_SET(conn_fd, &master_fds);
                    }
                }
                else
                {
                    // Handle data from an existing client socket
                    if (0 < if_idx)
                    {
                        bytes = recv(if_idx,
                                     operation_buffer,
                                     MAX_ALLOWED_OPERATION_MSG_LEN,
                                     (O_NONBLOCK));
                        if (ERROR == bytes)
                        {
                            ERRORPRINTF(recv());
                        }
                        else if (0 == bytes)
                        {
                            // Client has closed the connection
                            DEBUGPRINTF("Closing client #%d", if_idx);
                            FD_CLR(if_idx, &master_fds);
                            close(if_idx);
                        }
                        else
                        {
                            // Process the received operation message
                            DEBUGPRINTF("Operation recieved: %s",
                                        operation_buffer);
                            // operation_select(if_idx, operation_buffer);
                            memset(operation_buffer,
                                   0,
                                   MAX_ALLOWED_OPERATION_MSG_LEN);
                        }
                    }
                }
            }
        }
    }

    status_code = SUCCESS;
CLEAN:
    if (STDIN_FILENO < sock_fd)
    {
        close(sock_fd);
    }
EXIT:
    return status_code;
}

// EOF
