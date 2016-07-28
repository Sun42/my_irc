#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <netdb.h>
#include <sys/time.h>
#define h_addr  h_addr_list[0]

#include "client.h"



int	read_keyboard(char *buffer)
{
  if (fgets(buffer, BUF_SIZE - 1, stdin) == NULL)
  {
    perror("fgets()");
    return (-1);
  }
  return (0);
}

void	init_socket(int sock, fd_set *rdfs)
{
  FD_ZERO(rdfs);
  FD_SET(STDIN_FILENO, rdfs);
  FD_SET(sock, rdfs);
}

void	transmit_cmd(char *buffer, int sock)
{
  buffer = "*\0hello\0Lol";
  send(sock, buffer, 12, 0);
  /*  sleep(1);
   buffer = ".\0-ChAn2";
  send(sock, buffer, strlen(buffer) + strlen(buffer + 2) + 1, 0);
  sleep(1);
  buffer = ".\0ChYn3";
  sleep(1);
  send(sock, buffer, strlen(buffer) + strlen(buffer + 2) + 1, 0);
  buffer = "-\0Chan";
  sleep(1);
  send(sock, buffer, strlen(buffer) + strlen(buffer + 2) + 1, 0);*/
}
void	app(const char *address, const char *name)
{
  int sock;
  char buffer[BUF_SIZE];
  fd_set rdfs;

  strcpy(buffer, "hello");

  sock = init_connection(address);
  write_server(sock, name);
  while (1)
  {
    init_socket(sock, &rdfs);
    if(select(sock + 1, &rdfs, NULL, NULL, NULL) == -1)
    {
      perror("select()");
      exit(errno);
    }
    if(FD_ISSET(STDIN_FILENO, &rdfs))
    {
      if (read_keyboard(buffer) < 0)
	continue;
      transmit_cmd(buffer,sock);
    }
    else if(FD_ISSET(sock, &rdfs))
    {
      int n = read_server(sock, &buffer);
	printf("receive : %s|\n", buffer);
      if (fgets(buffer, BUF_SIZE - 1, stdin) == NULL)
	{
	  perror("fgets()");
	  continue;
	}
      printf("receive:%s\n",buffer);
      /* server down */
      if(n == 0)
      {
	printf("Server disconnected !\n");
	break;
      }
      puts(buffer);
    }
  }

  end_connection(sock);
}

static int init_connection(const char *address)
{
  SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
  SOCKADDR_IN sin;/* = { 0 };*/
  struct hostent *hostinfo;

  if (sock == INVALID_SOCKET)
    {
      perror("socket()");
      exit(errno);
    }

  hostinfo = gethostbyname(address);
  if (hostinfo == NULL)
    {
      fprintf (stderr, "Unknown host %s.\n", address);
      exit(EXIT_FAILURE);
    }

  sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
  sin.sin_port = htons(PORT);
  sin.sin_family = AF_INET;

  if(connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
    {
      perror("connect()");
      exit(errno);
    }

  return sock;
}

static void end_connection(int sock)
{
  closesocket(sock);
}

static int read_server(SOCKET sock, char *buffer)
{
  int n = 0;

  if((n = recv(sock, buffer, BUF_SIZE - 1, 0)) < 0)
    {
      perror("recv()");
      exit(errno);
    }

  buffer[n] = 0;

  return n;
}

static void write_server(SOCKET sock, const char *buffer)
{
  if(send(sock, buffer, strlen(buffer), 0) < 0)
    {
      perror("send()");
      exit(errno);
    }
}

int main(int argc, char **argv)
{
  if(argc < 2)
    {
      printf("Usage : %s [address] [pseudo]\n", argv[0]);
      return EXIT_FAILURE;
    }

  app(argv[1], argv[2]);

  return EXIT_SUCCESS;
}
