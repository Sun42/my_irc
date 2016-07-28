#include "ircd.h"

int	do_select(t_ircd *t_i)
{
  int	res;
  struct timeval	sel_timeout;

  bcopy(&(t_i->read_set), &(t_i->cur_read_set), sizeof(fd_set));
  bcopy(&(t_i->write_set), &(t_i->cur_write_set), sizeof(fd_set));
  sel_timeout.tv_sec = 1;
  if ((res = select(t_i->fd_max + 1, &(t_i->cur_read_set),  &(t_i->cur_write_set), 0, &(sel_timeout))) < 0)
    {
      fprintf(t_i->outfile, strerror(errno));
      return (-1);
    }
  return (res);
}
