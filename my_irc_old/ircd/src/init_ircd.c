#include "ircd.h"
#include <time.h>

static int	init_ircd2(t_ircd *);

int	set_parse_var(t_ircd *t_i, t_parse *t_p)
{
  return (set_bounds(add_var(t_p, "port", &(t_i->port), def_get_bound_int), 1, 65535)
	  && set_bounds(add_var(t_p, "max_users", &(t_i->max_users), def_get_bound_int), 1, 65535)
	  && set_bounds(add_var(t_p, "max_channels", &(t_i->max_chans), def_get_bound_int), 1, 65535)
	  && add_var(t_p, "log_file", &(t_i->log_file), def_get_str));
}

int		open_log(t_ircd *t_i)
{
  time_t	tmp;

  if (!(t_i->outfile = fopen(t_i->log_file, "a")))
    return (0);
  time(&tmp);
  fprintf(t_i->outfile, "\n>> Log started at %s\n", asctime(localtime(&(tmp))));
  return (1);
}

int		init_ircd(t_ircd *t_i)
{
  t_parse	t_p;
  int		res;

  memset(t_i, 0, sizeof(t_ircd));
  t_i->port = DEFAULT_PORT;
  t_i->max_users = DEFAULT_MAX_USERS;
  t_i->max_chans = DEFAULT_MAX_CHANS;
  if ((res = init_parse(&t_p, CONFIG_FILE, 512)) != PARSE_ALL_OK)
    {
      if (res == PARSE_OPEN_FAILED)
	fprintf(stderr, NO_CONF_FILE_WARN, CONFIG_FILE);
    }
  else
    {
      t_p.syntax_err_func = def_syntax_error;
      t_p.unknownvar_func = def_unknown_var;
      t_p.redefvar_func = def_redef_var;
      if (set_parse_var(t_i, &t_p))
	do_parse(&t_p);
      else
	fprintf(stderr, PARSE_FAILED_WARN);
      close_parse(&t_p);
    }
  printf("port: %d\n", t_i->port);
  printf("max_users: %d\n", t_i->max_users);
  printf("max_chans: %d\n", t_i->max_chans);
  return (init_ircd2(t_i));
}

static int		init_ircd2(t_ircd *t_i)
{
  t_i->outfile = stdout;
  if (t_i->log_file && !open_log(t_i))
    {
      t_i->outfile = stdout;
      fprintf(t_i->outfile, "**Can't open log file '%s'\n", t_i->log_file);
      free(t_i->log_file);
      return (0);
    }
  if (!init_connection(t_i))
    {
      close_ircd(t_i);
      return (0);
    }
  if (!(t_i->users = hcreate(t_i->max_users)) || !(t_i->chans = hcreate(t_i->max_chans)))
    {
      fprintf(t_i->outfile, "**Memory exhausted\n");
      close_ircd(t_i);
      return (0);
    }
  FD_ZERO(&(t_i->read_set));
  FD_ZERO(&(t_i->write_set));
  FD_SET(0, &(t_i->read_set));
  FD_SET(t_i->fd_max = t_i->socket, &(t_i->read_set));
  return (1);
}
