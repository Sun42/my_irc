#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include "server.h"


int		init_connection(void)
{
  int		sock;
  SOCKADDR_IN	sin;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock == INVALID_SOCKET)
    {
      perror("socket()");
      exit(errno);
    }
  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_port = htons(PORT);
  sin.sin_family = AF_INET;
  if(bind(sock,(SOCKADDR *) &sin, sizeof sin) < 0)
    {
      perror("bind()");
      exit(errno);
    }
  if(listen(sock, MAX_CLIENTS) < 0)
    {
      perror("listen()");
      exit(errno);
    }
  return sock;
}

int	end_connection(int sock)
{
  if (closesocket(sock) < 0)
  {
    perror("closesocket()");
    return (-1);
  }
  return (0);
}


void		init_wdfs(t_listm *first, fd_set *wdfs)
{
  t_listm	*listm;

  FD_ZERO(wdfs);
  listm = first->next;
  while (listm != first)
    {
      FD_SET(listm->sock, wdfs);
      listm = listm->next;
    }
}

void		init_rdfs(t_listc *first, fd_set *rdfs, SOCKET sock)
{
  t_listc	*listc;

  FD_ZERO(rdfs);
  FD_SET(STDIN_FILENO, rdfs);
  FD_SET(sock, rdfs);
  listc = first->next;
  while (listc != first)
    {
      FD_SET(listc->sock, rdfs);
      listc = listc->next;
    }
}

void	exec_cmd(char *buffer, t_listc *listc, t_listh *firsth, t_listm *firstm)
{
  char	cmd;

  cmd = buffer[0];
  if (cmd == CMD_NICK)
    func_nick(buffer + 2, listc, firstm);
  if (cmd == CMD_JOIN)
    func_join(buffer + 2, listc, firsth, firstm);
  if (cmd == CMD_PART)
    func_part(listc, firstm);
  if (cmd == CMD_LISTN)
    func_listn(listc, firsth, firstm);
  if (cmd == CMD_LISTS)
    func_lists(buffer + 2, listc, firsth, firstm);
  if (cmd == CMD_MSG)
    func_msg(buffer + 2, listc, firstm);
  if (cmd == CMD_MSGP)
    func_msgp(buffer + 2, listc, firstm);
  if (cmd == CMD_USER)
    func_user(listc, firstm);
}

void	aff_debug(char *buffer, int sock)
{
  char	cmd;
  char	*param;

  cmd = buffer[0];
  param = buffer + 2;
  printf("From:%d\ncmd:%d(%c)\nparam:%s\n\n", sock, (int)cmd, cmd, param);
}

void		select_read(t_listc *firstc, t_listh *firsth, t_listm
*firstm, fd_set *rdfs)
{
  t_listc	*listc;
  t_listc	*prev;
  char		buffer[BUF_SIZE];
  int		sread;

  prev = firstc;
  listc = firstc->next;
  while (listc != firstc)
    {
      if (FD_ISSET(listc->sock, rdfs))
	{
	  sread = read_client(listc->sock, buffer);
	  if(sread == 0)
	    disconnect_client(prev, listc);
	  else
	    {
	      /*aff_debug(buffer, listc->sock);*/
	      exec_cmd(buffer, listc, firsth, firstm);
	    }
	  return;
	}
      prev = listc;
      listc = listc->next;
    }
}

void		select_write(t_listm *firstm, fd_set *wdfs)
{
  t_listm	*cur;
  t_listm	*prev;

  prev = firstm;
  cur = firstm->next;
  while (cur != firstm)
    {
      if (FD_ISSET(cur->sock, wdfs))
	{
	  if (write_client(cur->sock, cur->msg) >= 0)
	    del_listm(prev, cur);
	  return ;
	}
      prev = cur;
      cur = cur->next;
    }
}
