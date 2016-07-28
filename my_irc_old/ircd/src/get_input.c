#include "ircd.h"

int	get_input(t_ircd *t_i)
{
  int	nread;
  char	buff[BUFF_SIZE];

  if (FD_ISSET(0, &(t_i->read_set)))
    {
      if ((nread = read(0, buff, BUFF_SIZE - 1)) == -1)
	return (0);
      buff[nread - 1] = '\0';
      if (!strcmp(buff, "exit") || !strcmp(buff, "quit"))
	return (0);
    }
  return (1);
}
