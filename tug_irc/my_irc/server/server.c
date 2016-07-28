#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "server.h"


void	app(t_listc *listc, t_listh *listh, t_listm *listm, int sock)
{
  int		csock;
  int		max;
  fd_set	rdfs;
  fd_set	wdfs;

  max = sock;
  while (1)
    {
      init_rdfs(listc, &rdfs, sock);
      init_wdfs(listm, &wdfs);
      /*show_listm(listm);*/
      if (select(max + 1, &rdfs, &wdfs, NULL, NULL) < 0)
	{
	  perror("select()");
	  return ;
	}
      if(FD_ISSET(STDIN_FILENO, &rdfs))
	return;
      else if(FD_ISSET(sock, &rdfs))
	{
	  if ((csock = add_new_client(listc, sock, &rdfs)) > max)
	    max = csock;
	}
      else
	{
	  select_read(listc, listh, listm, &rdfs);
	  select_write(listm, &wdfs);
	}
    }
}

int	main(void)
{
  t_listc	*listc;
  t_listh	*listh;
  t_listm	*listm;
  int		sock;

  sock = init_connection();
  listc = init_listc();
  listh = init_listh();
  listm = init_listm();

  app(listc, listh, listm, sock);

  remove_all_client(listc);
  end_connection(sock);

  return EXIT_SUCCESS;
}
