#include "ircd.h"

int	ircd_mainloop(t_ircd *t_i)
{
  int	res;

  while (1)
    {
      if ((res = do_select(t_i)) == -1)
	return (-1);
      if (res)
	{
	  if (!get_input(t_i))
	    return (0);
 	  get_connection(t_i);
/* 	  get_client_msg(t_i); */
/* 	  send_client_msg(t_i); */
	}
    }
}
