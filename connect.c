#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "client.h"

void	do_connect(gchar *cmd, gpointer data)
{
  gchar	**tab;

  tab = wordtab(cmd);
  if (count_tab(tab) < 2)
    add_text("/server ip port \n", data);
  else
    {
      if (try_connect(tab, data))
	add_text("Connected succesfully \n", data);
      else
	add_text("Error while trying to connect \n", data);
    }
  free_tab(tab);
}

int			try_connect(gchar **tab, gpointer data)
{
  int			port;
  int			sock;
  struct sockaddr_in	sin;
  t_supinfo		*supinfo;

  supinfo = (t_supinfo *)data;
  port = atoi(tab[2]);
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      add_text("Socket error \n", data);
      return (0);
    }
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = inet_addr(tab[1]);
  if ((connect(sock , (struct sockaddr *)&sin, sizeof(struct sockaddr_in))) == -1)
    {
      add_text("Connexion error \n", data);
      return (0);
    }
  supinfo->info_cli->s = sock;
  send(supinfo->info_cli->s, "noname", strlen("noname"), 0);
  supinfo->info_cli->is_connected = 1;
  return (1);
}
