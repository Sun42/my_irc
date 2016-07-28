#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "server.h"

int	add_new_client(t_listc *listc, SOCKET sock, fd_set *rdfs)
{
/*  SOCKADDR_IN csin = { 0 };
  size_t sinsize = sizeof csin;
  if((csock = accept(sock, (SOCKADDR *)&csin, &sinsize)) < 0)*/
  int	csock;
  char	buffer[BUF_SIZE];

  if((csock = accept(sock, NULL, NULL)) < 0)
  {
    perror("accept()");
    return (-1);
  }
  if(read_client(csock, buffer) < 0)
    return (-1);
  printf("new client:%d\n", csock);
  FD_SET(csock, rdfs);
  add_listc(listc, csock, buffer);
  return (csock);
}


void	disconnect_client(t_listc *prev, t_listc *cur)
{
  if (end_connection(cur->sock) != -1)
    printf("Client_%d disconnect\n", cur->sock);
  if (prev != NULL)
    {
      prev->next = cur->next;
      free(cur->name);
      free(cur);
    }
}

void		remove_all_client(t_listc *first)
{
  t_listc	*listc;

  listc = first->next;
  while (listc != first)
    {
      disconnect_client(NULL, listc);
      listc = listc->next;
    }
}

int	read_client(SOCKET sock, char *buffer)
{
  int n;

  n = 0;
  if ((n = recv(sock, buffer, BUF_SIZE - 1, 0)) < 0)
    {
      perror("recv()");
      return (-1);
    }
  buffer[n] = '\0';
  return (n);
}

int	write_client(SOCKET sock, const char *buffer)
{
  if (buffer == NULL || strlen(buffer) < 1)
    return (0);
  if(send(sock, buffer, strlen(buffer), 0) < 0)
    {
      perror("send()");
      return (-1);
    }
  return (0);
}
