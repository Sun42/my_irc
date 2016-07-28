
#include "readlib.h"
#include <fcntl.h>
#include <stdlib.h>

int	get_char(t_file *file)
{
  if (file->buf_size <= 0)
    {
      if ((file->buf_size = read(file->fd, file->buffer, BUFFER_SIZE)) <= 0)
	return (END_OF_FILE);
      file->buf_pos = file->buffer;
    }
  file->buf_size--;
  return ((int)(*(file->buf_pos++)));
}

char	*get_line(t_file *file)
{
  char	*res;
  int	cur_buff_size;
  int	i;
  int	cur_char;

  cur_buff_size = 0;
  if (!(res = malloc(BUFFER_SIZE * sizeof(char))))
    return (NULL);
  for (i = 0;; i++)
    {
      if (i >= cur_buff_size)
	if (!(res = realloc(res, cur_buff_size += BUFFER_SIZE)))
	  return (NULL);
      res[i] = '\0';
      if ((cur_char = get_char(file)) == END_OF_FILE)
	{
	  if (i == 0)
	    {
	      free(res);
	      return (NULL);
	    }
	  else
	    return (res);
	}
      if ((char)cur_char == '\n')
	return (res);
      res[i] = (char)cur_char;
    }
}
