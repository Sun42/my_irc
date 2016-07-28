#include <gtk/gtk.h>
#include <string.h>
#include "client.h"

void	send_msg(gchar **tab, gchar *cmd, gpointer data)
{
  int		len;
  gchar		*msg;
  t_supinfo	*supinfo;

  supinfo = (t_supinfo *)data;
  if (count_tab(tab) < 3)
    return ;
  cmd += strlen(tab[1]) + strlen(CMD_MSG);
  len = strlen(tab[1]) + strlen(cmd) + 3 + 1 + 1;
  msg = g_malloc(len);
  g_strlcpy(msg , "49[", 4);
  g_strlcat(msg, tab[1], strlen(tab[1]) + 4 + 1);
  g_strlcat(msg, "[", strlen(tab[1]) + 4 + 1);
  g_strlcat(msg, cmd, len);
  msg[2] = '\0';
  msg[3 + strlen(tab[1])] = '\0';
  g_printf("Msg %s \n", msg);
  if (send(supinfo->info_cli->s, msg, len, 0) == -1)
    add_text("Error sending message \n", data);
  g_free(msg);
}
