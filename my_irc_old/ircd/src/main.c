#include "ircd.h"

int		main()
{
  t_ircd	t_i;
/*   int		new_sock; */
/*   struct sockaddr_in	connect_addr; */
/*   char	buff[512]; */
/*   struct sockaddr_in  name; */
/*   socklen_t	sl; */

  if (init_ircd(&t_i))
    {
      fflush(t_i.outfile);
      ircd_mainloop(&t_i);
/*       listen(t_i.socket, 5); */
/*       new_sock = accept(t_i.socket, (struct sockaddr *)&connect_addr, &(t_i.sock_size)); */
/*       sl = sizeof(name); */
/*       getpeername(new_sock, (struct sockaddr *)&name, &sl); */
/*       realhostname(buff, 512, &(name.sin_addr)); */
/*       printf("%s, %s\n", inet_ntoa(name.sin_addr), buff); */
/*       write (new_sock, "Creve salope\n", 13); */
      close_ircd(&t_i);
    }
  fflush(t_i.outfile);
  return (0);
}
