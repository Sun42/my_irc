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

void		add_buffer(gpointer data, gchar *text, int len)
{
  t_supinfo	*supinfo;
  int		wnext;
  int		cpt;
  
  cpt = 0;
  supinfo = (t_supinfo *)data;
  wnext = supinfo->info_cli->wnext;
  while (cpt < len)
    {
      if (wnext == BUFF_SIZE)
	wnext = 0;
      supinfo->info_cli->wbuffer[wnext] = text[cpt];
      cpt++;
      wnext++;
    }
  supinfo->info_cli->wnext = wnext;
  g_printf("Apres add buffer wnext => %i\n", wnext);
}


gint	get_len_extract(gpointer data)
{
  gint		cpt;
  t_supinfo	*supinfo;
  int		next;
  int		i;

  supinfo = (t_supinfo *)data;
  cpt = 0;
  i = supinfo->info_cli->wpos;
  while (cpt < BUFF_SIZE)
    {
      if (i == BUFF_SIZE)
	i = 0;
      next = i + 1;
      if (next == BUFF_SIZE)
	next = 0;
      if (supinfo->info_cli->wbuffer[i] == ']')
	{
	  g_printf("] found \n , %i", supinfo->info_cli->wbuffer[next]);
	  if (supinfo->info_cli->wbuffer[next] == '\0')
	    return (cpt + 2);
	}
	i++;
	cpt++;
    }
  if (cpt == BUFF_SIZE)
    return (-1);
}

gchar		*extract_buffer(gpointer data, int len)
{
  t_supinfo	*supinfo;
  gchar		*str;
  int		i;
  int		wpos;



  supinfo = (t_supinfo *)data;
  i = 0;
  wpos = supinfo->info_cli->wpos;
  str = g_malloc(len + 1);	
  g_printf("o_o wpos %i \n", wpos);
  while (i <= len)
    {
      if (wpos == BUFF_SIZE)
	wpos = 0;
      str[i] = supinfo->info_cli->wbuffer[wpos];
      wpos++;
      i++;
    }
  g_printf("extracted %s %i", str, strlen(str));
  return (str);
}

void	turn_my_buf(gpointer data, int len)
{
 t_supinfo	*supinfo;
 int		i;
 int		cpt;
 
 cpt = 0;
 supinfo = (t_supinfo *)data;
 i = supinfo->info_cli->wpos;
 while (cpt < len)
   {
     if (i == BUFF_SIZE)
       i = 0;
     supinfo->info_cli->wbuffer[i] = '\0';
     i++;
     cpt++;
   }
 supinfo->info_cli->wpos = i;
 g_printf("wpos is now %i \n ", i);
}


void	init_buff(gpointer data)
{
  t_supinfo	*supinfo;
  
  supinfo = (t_supinfo *)data;
  bzero(supinfo->info_cli->wbuffer, BUFF_SIZE - 1);
  supinfo->info_cli->wpos = 0;
  supinfo->info_cli->wnext = 0;
}
