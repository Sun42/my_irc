
#include "readlib.h"
#include <stdio.h>

int	main()
{
  t_file	*file;
  char		*buf;

  if (!(file = open_file("blah.txt")))
    printf("rate\n");
  else
    {
      while (buf = get_line(file))
	{
	  printf(">>>%s<<<\n", buf);
	  free(buf);
	}
      close_file(file);
    }
  return (0);
}
