#include "ircd.h"
#include <time.h>

void	close_log(t_ircd *t_i)
{
  time_t	tmp;

  if (t_i->log_file)
    {
      free(t_i->log_file);
      time(&tmp);
      fprintf(t_i->outfile, "\n<< Server shutdown at %s\n", asctime(localtime(&(tmp))));
      fclose(t_i->outfile);
    }
}

void	free_user(UNUSED void *user)
{
}

void	free_chan(UNUSED void *user)
{
}

void	close_ircd(t_ircd *t_i)
{
  close_log(t_i);
  if (t_i->socket)
    close(t_i->socket);
  if (t_i->users)
    hfree(t_i->users, free_user);
  if (t_i->chans)
    hfree(t_i->chans, free_chan);
}
