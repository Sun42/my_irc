
#include "readlib.h"
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

t_file		*open_file(const char *file_name)
{
  t_file	*new_file;

  if (!(new_file = malloc(sizeof(t_file))))
    return (NULL);
  memset(new_file, 0, sizeof(t_file));
  if ((new_file->fd = open(file_name, O_RDONLY)) == -1)
    {
      free(new_file);
      return (NULL);
    }
  if (!(new_file->buffer = malloc(BUFFER_SIZE * sizeof(char))))
    {
      close(new_file->fd);
      free(new_file);
      return (NULL);
    }
  new_file->buf_pos = new_file->buffer;
  return (new_file);
}
