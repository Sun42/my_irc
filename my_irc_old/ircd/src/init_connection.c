#include "ircd.h"

int			init_connection(t_ircd *t_i)
{
  struct sockaddr_in	server_addr;

  fprintf(t_i->outfile, "Creating socket...\n");
  if ((t_i->socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      fprintf(t_i->outfile, "Could'nt create socket, aborting...\n");
      return (0);
    }
  bzero(&server_addr, sizeof(struct sockaddr_in));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(t_i->port);
  fprintf(t_i->outfile, "Binding socket to port %d...\n", t_i->port);
  if (bind(t_i->socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
    {
      fprintf(t_i->outfile, "Binding failed, aborting...\n");
      return (0);
    }
  t_i->sock_size = sizeof(t_i->socket);
  return (1);
}
