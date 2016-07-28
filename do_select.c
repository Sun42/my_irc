#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <glib.h>
#include <glib/gprintf.h>
#include "client.h"

GSourceFunc		do_select(gpointer data)
{
  t_supinfo		*supinfo;
  struct timeval	tv;
  fd_set		rdfs;
  fd_set		wtfs;
 
  tv.tv_sec = 0;
  tv.tv_usec = 100;
  supinfo = (t_supinfo *)data;
  if (supinfo->info_cli->is_connected == 0)
    return ((GSourceFunc)TRUE);
  init_socket(supinfo->info_cli->s, &rdfs, &wtfs);
  if (select(supinfo->info_cli->s + 1, &rdfs, &wtfs, NULL, &tv) == -1)
    {
      perror("select()");
      return ((GSourceFunc)TRUE);
    }
  if (FD_ISSET(supinfo->info_cli->s, &rdfs))
    read_server(supinfo->info_cli->s, data);
  if (FD_ISSET(supinfo->info_cli->s, &wtfs))
    write_server(data);
  return ((GSourceFunc)TRUE);
}

void	init_socket(int sock, fd_set *rdfs, fd_set *wtfs)
{
  FD_ZERO(rdfs);
  FD_SET(sock, rdfs);
  FD_ZERO(wtfs);
  FD_SET(sock, wtfs);
}

int		read_server(int sock, gpointer data)
{
  int		n;
  t_supinfo	*supinfo;
  gchar		*text;
  
  supinfo = (t_supinfo *)data;
  n = 0;
  if ((n = recv(sock, supinfo->info_cli->rbuffer, BUFF_SIZE - 1, 0)) <= 0)
    supinfo->info_cli->is_connected = 0;
  supinfo->info_cli->rbuffer[n] = 0;
  text = xg_malloc(n + 1);
  g_strlcpy(text, supinfo->info_cli->rbuffer, n + 1);
  add_text(text, data);
  g_free(text);
  return (n);
}

void	write_server(gpointer data)
{
  t_supinfo	*supinfo;
  gchar		*str;
  int		len;
  int		nbsent;
  int	wpos;
  int	wnext;

  supinfo = (t_supinfo *)data;
  wpos = supinfo->info_cli->wpos;
  wnext = supinfo->info_cli->wnext;
  if (wpos == wnext)
    return ;
  g_printf("buff[wpos] %c %i, buff[wnext] %c %i\n", supinfo->info_cli->wbuffer[wpos], supinfo->info_cli->wbuffer[wnext],  supinfo->info_cli->wbuffer[wpos], supinfo->info_cli->wbuffer[wnext]); 
  g_printf("wpos :%i, wnext %i \n", supinfo->info_cli->wpos, supinfo->info_cli->wnext);
  len = get_len_extract(data);
  g_printf("len a extraire %i \n", len);
  if (len == -1)
    return ;
  if (len > MAX_LEN)
    len = MAX_LEN;
  str = extract_buffer(data, len);
  g_printf("msg extrait : %s, strlen %i \n", str, strlen(str));
  nbsent = send(supinfo->info_cli->s, str, len, 0);
  g_printf("len sended %i \n", nbsent);
  if (nbsent > 0)
    turn_my_buf(data, nbsent);
  g_printf("Ca passe ? \n");
  g_free(str);
  g_printf("FIN DO SELECT \n");
}

