#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include "client.h"

void		send_nick(gchar **tab, gpointer data)
{
  int		len;
  gchar		*msg;
  t_supinfo	*supinfo;

  supinfo = (t_supinfo *)data;
  if (count_tab(tab) < 2)
    return ;
  len = strlen(tab[1]) + 4;
  msg = g_malloc(len);
  g_strlcpy(msg , "+[", 3);
  g_strlcat(msg, tab[1], len);
  /*msg[1] = '\0';*/
  msg[len - 2] = ']'; /*\13 */
  msg[len - 1] = '\0'; /*\0 */
  g_printf("msg : %s strlen : %i len : %i\n", msg , strlen(msg), len);
  add_buffer(data, msg, len);
  g_free(msg);
}

void		send_join(gchar **tab, gpointer data)
{
  int		len;
  gchar		*msg;
  t_supinfo	*supinfo;
  
  supinfo = (t_supinfo *)data;
  if (count_tab(tab) < 2)
    return ;
  len = strlen(tab[1]) + 4;
  msg = g_malloc(len);
  g_strlcpy(msg , ".[", 3);
  g_strlcat(msg, tab[1], len);
  /*msg[1] = '\0';*/
  msg[len - 2] = ']'; /*\13*/
  msg[len - 1] = '\0';
  add_buffer(data, msg, len);
  g_free(msg);
}

void	send_part(gpointer data)
{
  t_supinfo	*supinfo;

  supinfo = (t_supinfo *)data;
  if (send(supinfo->info_cli->s, "/\0", 2, 0) == -1)
    add_text("Error sending message \n", data);
}

void		send_list(gchar **tab, gpointer data)
{
  int		len;
  gchar		*msg;
  t_supinfo	*supinfo;

  supinfo = (t_supinfo *)data;
  if (count_tab(tab) < 2)
    {
      len = 2;
      msg = g_malloc(len);
      g_strlcpy(msg , ",", 2);
    }
  else
    {
      len = strlen(tab[1]) + 3;
      msg = g_malloc(len);
      g_strlcpy(msg , "-[", 3);
      g_strlcat(msg, tab[1], len);
      msg[1] = '\0';
    }
  if (send(supinfo->info_cli->s, msg, len, 0) == -1)
    add_text("Error sending message \n", data);
  g_free(msg);
}

void	send_default(gchar *cmd, gpointer data)
{
  t_supinfo	*supinfo;
  int		len;
  gchar		*msg;

  if (strlen(cmd) > 0)
    {
      supinfo = (t_supinfo *)data;
      len = strlen(cmd) + 3;
      msg = g_malloc(len);
      g_strlcpy(msg , "0[", 3);
      g_strlcat(msg, cmd, len);
      msg[1] = '\0';
      if (send(supinfo->info_cli->s, msg, len, 0) == -1)
	add_text("Error sending message \n", data);
     g_free(msg);
    }
}
