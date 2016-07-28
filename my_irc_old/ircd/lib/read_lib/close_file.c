
#include <readlib.h>
#include <unistd.h>
#include <stdlib.h>

void		*close_file(t_file *file)
{
  close(file->fd);
  free(file->buffer);
  free(file);
}
