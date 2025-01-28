#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>

// #                  #
// # Static variables #
// #                  #
#define DEFAULT_PORT 4600
#define DEFAULT_QUEUE_SIZE 4

// #                  #
// # Helper functions #
// #                  #
void construct_address(struct sockaddr_in *address, socklen_t *address_len, int port) {
  memset(address, 0, sizeof(*address));
  address->sin_family = AF_INET;
  address->sin_addr.s_addr = htonl(INADDR_ANY); // Convert a long integer
  address->sin_port = htons(port); // Convert a short integer
  *address_len = sizeof(*address);
}

// #------#
// # Main #
// #------#
int main(int argc, char *argv[]) {
  // #              #
  // # Return codes #
  // #              #

  // 0 Success
  // 1 Error creating TCP/IPv4 socket
  // 2 Error binding socket
  // 3 Error listening on the port
  // 4 Error accepting connections
  
  // #          #
  // # Settings #
  // #          #
  // Later on, these will be passed as arguments
  const int PORT = DEFAULT_PORT;
  const int LISTEN_BACKLOG = DEFAULT_QUEUE_SIZE;

  // Create a socket : int domain   AF_INET     IPv4
  //                   int type     SOCK_STREAM TCP
  //                   int protocol 0           TCP is standard, no other option
  // As it is in UNIX, it returns a file descriptor (fd)
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  // Check if the socket was created successfully (doc says it returns -1 on error)
  if (socket_fd < 0) {
    perror("Error creating TCP/IPv4 socket");
    return 1;
  }

  // Bind the socket to a port : int sockfd            socket file descriptor
  //                             struct sockaddr *addr address specifications
  //                             socklen_t addrlen     specify the size in bytes
  // htonl and htons converts unsigned integer to network byte order
  // May seem useless at first glance but ensures it is working on all systems, regardless of their native byte order
  struct sockaddr_in address; socklen_t address_len;
  construct_address(&address, &address_len, PORT);

  int binded_port = bind(socket_fd, (struct sockaddr *)&address, address_len);

  // Check if the socket was binded successfully (doc says it returns -1 on error)
  if (binded_port < 0) {
    perror("Error binding socket");
    close(socket_fd);
    return 2;
  }

  // Listens on the port : int sockfd  socket file descriptor again
  //                       int backlog maximum queue size for pending connections
  int listen_success = listen(socket_fd, LISTEN_BACKLOG);

  // (doc says it returns 0 for success and -1 for error)
  if (listen_success != 0) {
    perror("Error listening on port");
    close(socket_fd);
    return 3;
  }

  // Accept connections on sockets : int socket_fd                        socket file descriptor
  //                                 struct sockaddr *_Nullable restrict  address of the peer socket 
  //                                 struct socklen_t *_Nullable restrict length of the peer address 
  int connection_fd = accept(socket_fd, (struct sockaddr *)&address, &address_len);

  // (doc says it returns -1 for error)
  if (connection_fd < 0) {
    perror("Error when accepting connections");
    close(socket_fd);
    return 4;
  }

  // Send a message to the client
  const char *message = "Hello from server!\n";
  write(connection_fd, message, strlen(message));

  // Closing the file descriptors
  close(socket_fd);
  close(connection_fd);

  return 0;
}
