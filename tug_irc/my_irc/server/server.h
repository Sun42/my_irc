#ifndef __SERVER_H_
#define __SERVER_H_

#include <sys/types.h>
#include <sys/socket.h>



#include <sys/time.h>

#include <netinet/in.h>


#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#define CRLF "\r\n"
#define PORT 1977
#define MAX_CLIENTS 100

#define BUF_SIZE 1024


#define CMD_USER	42
#define CMD_NICK	43
#define CMD_LISTN	44
#define CMD_LISTS	45
#define CMD_JOIN	46
#define CMD_PART	47
#define CMD_MSG		48
#define CMD_MSGP	49
#define CMD_ERROR	51


typedef struct
{
  int		sock;
  char		name[BUF_SIZE];
  int		chanel;
}Client;


/* liste chaine des clients */
typedef struct		s_listc
{
  struct s_listc	*next;
  SOCKET		sock;
  char			*name;
  int			channel;
}			t_listc;

/* liste chaine des messages en attente d'envoie */
typedef struct		s_listm
{
  struct s_listm	*next;
  int			sock;
  char			*msg;
}			t_listm;

/* liste chaine des channel */
typedef struct		s_listh
{
  struct s_listh	*next;
  int			num_chan;
  char			*name;
}			t_listh;

/* manage_connexion */
int		init_connection(void);
int		end_connection(int sock);
void		init_wdfs(t_listm *first, fd_set *wdfs);
void		init_rdfs(t_listc *first, fd_set *rdfs, SOCKET sock);
void		select_read(t_listc *firstc, t_listh *firsth, t_listm
*firstm, fd_set *rdfs);
void		select_write(t_listm *firstm, fd_set *wdfs);

/* manage_listc */
void		add_listc(t_listc *first, int new_sock, char *name);
t_listc		*init_listc(void);
t_listh		*init_listh(void);
t_listh		*add_listh(t_listh *first, char *name);
t_listm		*init_listm();
void		add_listm(t_listm *first, int sock, char *msg);
void		add_all_listm(t_listm *firstm, t_listc *listc, char *msg);
void		del_listm(t_listm *prev, t_listm *cur);
void            show_listm(t_listm *first);
void		show_listh(t_listh *first);
void		show_listc(t_listc *first);

/* manage_client */
void		remove_all_client(t_listc *first);
void		disconnect_client(t_listc *prev, t_listc *cur);
int		add_new_client(t_listc *listc, SOCKET sock, fd_set *rdfs);
int		read_client(SOCKET sock, char *buffer);
int		write_client(SOCKET sock, const char *buffer);

/* mylib */
char		*xstrdup(char *str);

/* function */
void		func_listn(t_listc *listc, t_listh *firsth, t_listm *firstm);
void		func_nick(char *nick, t_listc *listc, t_listm *firstm);
void		func_join(char *name_chan, t_listc *listc, t_listh *firsth, t_listm *firstm);
void		func_part(t_listc *listc, t_listm *firstm);
void		func_listn(t_listc *listc, t_listh *firsth, t_listm *firstm);
void		func_lists(char *pattern, t_listc *listc, t_listh *firsth,
t_listm *firstm);
void		func_msg(char *msg, t_listc *listc, t_listm *firstm);
void		func_msgp(char *msg, t_listc *listc, t_listm *firstm);
void		func_user(t_listc *listc, t_listm *firstm);

#endif /* __SERVER_H_ */
