#include <glib.h>
#include <glib/gprintf.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include "client.h"

GtkWidget	*mk_window(int h, int w, gchar *title)
{
  GtkWidget	*win;

  win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(win), title);
  gtk_window_set_default_size(GTK_WINDOW(win), h, w);
  gtk_container_set_border_width(GTK_CONTAINER(win), 10);
  g_signal_connect(G_OBJECT(win), "destroy",\
		   G_CALLBACK(gtk_main_quit), NULL);
  return (win);
}


void		place_elem(gpointer data)
{
  t_main	*main_win;

  main_win = (t_main *)data;
  gtk_container_add(GTK_CONTAINER(main_win->win),	\
		    main_win->vbox);
  gtk_container_add(GTK_CONTAINER(main_win->scroll), main_win->textview);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(main_win->scroll),
				 GTK_POLICY_AUTOMATIC, 
				 GTK_POLICY_AUTOMATIC);
  gtk_text_view_set_editable(GTK_TEXT_VIEW(main_win->textview),	\
			     (gboolean)FALSE);
  gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(main_win->textview),
			      GTK_WRAP_WORD_CHAR);
  gtk_box_pack_start(GTK_BOX(main_win->vbox),		\
		     main_win->scroll, TRUE, TRUE, 60);
  gtk_box_pack_start(GTK_BOX(main_win->vbox),		\
		     main_win->hbox, FALSE, TRUE, 60);
  gtk_box_pack_start(GTK_BOX(main_win->hbox),		\
		     main_win->entry, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(main_win->hbox),		\
		     main_win->btsend, TRUE, TRUE, 60);
  gtk_box_pack_start(GTK_BOX(main_win->hbox),		\
		     main_win->btquit, TRUE, TRUE, 60);
  /*gtk_window_set_resizable(GTK_WINDOW(main_win->win), FALSE);*/ 
}

void		active_events(gpointer data)
{
  t_supinfo	*supinfo;

  supinfo = (t_supinfo *)data;
  g_signal_connect(G_OBJECT(supinfo->main_win->btquit), "clicked",\
		   G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(G_OBJECT(supinfo->main_win->btsend), "clicked",\
		   G_CALLBACK(on_update), (gpointer) supinfo);
  g_signal_connect(G_OBJECT(supinfo->main_win->entry), "activate",\
		   G_CALLBACK(on_update), (gpointer) supinfo);
}

void		create_elems(gpointer data)
{
  t_main	*main_win;

  main_win = (t_main *)data;
  main_win->win = mk_window(600, 600, TITLE);
  main_win->vbox = gtk_vbox_new(FALSE, 50);
  main_win->btquit = gtk_button_new_with_label("quit");
  main_win->btquit = gtk_button_new_from_stock(GTK_STOCK_QUIT);
  main_win->btsend = gtk_button_new_with_label("send");
  main_win->scroll = gtk_scrolled_window_new(NULL, NULL);
  main_win->textview = gtk_text_view_new();
  main_win->hbox = gtk_hbox_new(TRUE, 0);
  main_win->entry = gtk_entry_new();
}

void			on_update(GtkWidget *entry, gpointer data)
{
  const gchar		*text;
  gchar			*cmd;
  t_supinfo		*supinfo;

  supinfo = (t_supinfo *)data;
  text = gtk_entry_get_text(GTK_ENTRY(supinfo->main_win->entry));
  cmd = g_strdup(text);
  gtk_entry_set_text(GTK_ENTRY(supinfo->main_win->entry), "");
  parse_cmd(cmd, supinfo);
  g_free(cmd);
}
