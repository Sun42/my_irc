#ifndef __CLI_IRC_H__
# define __CLI_IRC_H__

#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define TITLE "My IrC"
#define NOT_CONNECTED "You need to connect first \n"
#define	CMD_SERVER "/server "
#define CMD_NICK "/nick "
#define CMD_LIST "/list"
#define CMD_JOIN "/join "
#define CMD_PART "/part"
#define CMD_MSG "/msg "
#define BUFF_SIZE 25
#define MAX_LEN	512
#define TO_SEND (a) > (MAX_LEN) ? (MAX_LEN) : (a)

typedef struct s_mainwindow
{
  GtkWidget	*win;
  GtkWidget	*vbox;
  GtkWidget	*hbox;
  GtkWidget	*entry;
  GtkWidget	*btsend;
  GtkWidget	*btquit;
  GtkWidget	*textview;
  GtkWidget	*scroll;

} t_main;

typedef	struct s_info_cli
{
  int			is_connected;
  int			s;
  gchar			rbuffer[BUFF_SIZE];
  gchar			wbuffer[BUFF_SIZE];
  int			wpos;
  int			wnext;
} t_info_cli;


typedef	struct	s_supinfo
{
  t_main	*main_win;
  t_info_cli	*info_cli;
} t_supinfo;

/*
** client.c 
*/
void		init_cli(int ac , char **av);
void		parse_cmd(gchar *text, gpointer data);
void		init_infocli(gpointer data);
void		send_cmd(gchar *cmd, gpointer data);
void		add_text(gchar *text, gpointer data);

/*
**do_select
*/
GSourceFunc	do_select(gpointer data);
void		init_socket(int sock, fd_set *rdfs, fd_set *wtfs);

int		read_server(int sock, gpointer data);
void		write_server(gpointer data);

/*
** connect.c
*/
void		do_connect(gchar *cmd, gpointer data);
int		try_connect(gchar **tab, gpointer supinfo);


/*
** cmd.c
*/
void		send_nick(gchar **tab, gpointer supinfo);
void		send_list(gchar **tab, gpointer data);
void		send_join(gchar **tab, gpointer data);
void		send_part(gpointer data);
void		send_default(gchar *cmd, gpointer data);

/*
** cmd2.c
*/
void		send_msg(gchar **tab, gchar *cmd, gpointer data);

/*
** graphics.h
*/
GtkWidget	*mk_window(int h, int w, gchar *title);
void		on_update(GtkWidget *entry, gpointer data);
void		place_elem(gpointer data);
void		active_events(gpointer data);
void		create_elems(gpointer data);


/*
** ord.h
*/
int	isletter(char c);
int	count_word(gchar *str);
int	word_len(gchar *str);
int	count_tab(gchar **tab);
void	free_tab(gchar **tab);

/*
** cli_utils.h
*/
gpointer	xg_malloc(gsize n_bytes);
gchar		**wordtab(gchar *str);
void		init_vars(int *i, int *flag);


/*
** buffer.c
*/
void	add_buffer(gpointer data, gchar *text, int len);
gint	get_len_extract(gpointer data);
gchar	*extract_buffer(gpointer data, int len);
void	turn_my_buf(gpointer data, int len);
void	init_buff(gpointer data);
#endif /*__CLI_IRC_H__ */
