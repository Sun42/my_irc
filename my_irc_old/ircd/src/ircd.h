#ifndef IRCD_H_
# define IRCD_H_

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <libutil.h>
#include <sys/select.h>
#include <errno.h>
#include "conf_parser.h"
#include "libhash.h"

typedef struct s_list
{
  void		*data;
  struct s_list	*next;
}t_list;

typedef struct
{
  char		*log_file;
  FILE		*outfile;
  int		max_users;
  int		max_chans;
  int		port;
  t_hash	*users;
  t_list	*user_list;
  int		num_users;
  t_hash	*chans;
  int		num_chans;
  int		socket;
  socklen_t     sock_size;
  fd_set	read_set;
  fd_set	write_set;
  fd_set	cur_read_set;
  fd_set	cur_write_set;
  int		fd_max;
}t_ircd;

#define MODE_I		1
#define MODE_S		2
#define MODE_W		4
#define MODE_O		8

typedef struct
{
  char		*nick;
  char		*username;
  char		*host;
  int		mode;
  t_list	*chan_list;
  short		is_registered;
}t_user;

#define BUFF_SIZE		512

#define CONFIG_FILE		"ircd.conf"
#define	DEFAULT_PORT		6667
#define DEFAULT_MAX_USERS	512
#define DEFAULT_MAX_CHANS	128

#define NO_CONF_FILE_WARN	"WARNING: can't open '%s'\n"
#define PARSE_FAILED_WARN	"WARNING: failed to read configuration file\n"

int	init_ircd(t_ircd *);
void	close_ircd(t_ircd *);
int	init_connection(t_ircd *);
void	close_log(t_ircd *);
int	ircd_mainloop(t_ircd *);
int	do_select(t_ircd *);
int	get_input(t_ircd *);
int	get_connection(t_ircd *);

#endif /* !IRCD_H_ */
