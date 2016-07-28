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

int		main(int ac, char **av)
{
  init_cli(ac, av);
  return (EXIT_SUCCESS);
}

void		init_cli(int argc , char **argv)
{
  t_main	*main_win;
  t_supinfo	*supinfo;

  gtk_init(&argc,&argv);
  supinfo = g_malloc(sizeof(t_supinfo));
  supinfo->main_win = g_malloc(sizeof(t_main));
  supinfo->info_cli = g_malloc(sizeof(t_info_cli));
  supinfo->info_cli->is_connected = 0;
  init_buff(supinfo);
  create_elems((gpointer)supinfo->main_win);
  place_elem((gpointer)supinfo->main_win);
  active_events((gpointer)supinfo);
  gtk_widget_show_all(supinfo->main_win->win);
  g_idle_add((GSourceFunc) do_select, (gpointer) supinfo);
  gtk_main();
  g_free(supinfo->main_win);
  g_free(supinfo->info_cli);
  g_free(supinfo);
}

void	send_cmd(gchar *cmd, gpointer data)
{
  gchar	**tab;

  tab = wordtab(cmd);
  if (g_strncasecmp(cmd, CMD_NICK, 6) == 0)
    send_nick(tab, data);
  else if (g_strncasecmp(cmd, CMD_LIST, 5) == 0)
    send_list(tab, data);
  else if (g_strncasecmp(cmd, CMD_JOIN, 6) == 0)
    send_join(tab, data);
  else if (g_strncasecmp(cmd, CMD_PART, 5) == 0)
    send_part(data);
  else if (g_strncasecmp(cmd, CMD_MSG, 5) == 0)
    send_msg(tab, cmd, data);
  else
    send_default(cmd, data);
  free_tab(tab);
}

void		add_text(gchar *text, gpointer data)
{
  t_supinfo	*supinfo;
  GtkTextBuffer	*textbuffer;
  GtkTextIter	start;
  GtkTextIter	end;
  
  supinfo = (t_supinfo *)data;
  textbuffer =\
    gtk_text_view_get_buffer(GTK_TEXT_VIEW(supinfo->main_win->textview));
  gtk_text_buffer_get_start_iter(textbuffer, &start);
  gtk_text_buffer_get_end_iter(textbuffer, &end);
  gtk_text_buffer_insert_interactive(textbuffer, &end, text, strlen(text), 1);
}

void		parse_cmd(gchar *cmd, gpointer data)
{
  t_supinfo	*supinfo;

  supinfo = (t_supinfo *)data;
  if (supinfo->info_cli->is_connected == 0)
    {
      if (g_strncasecmp(CMD_SERVER, cmd, 8) == 0)
        {
          add_text("Tentative de connexion \n", data);
          do_connect(cmd, supinfo);
        }
      else
        add_text(NOT_CONNECTED, data);
    }
  else
    {
      send_cmd(cmd, data);
    }
}
