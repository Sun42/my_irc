
#ifndef READLIB_H_
# define READLIB_H_

#define	BUFFER_SIZE	512

typedef struct
{
  char	*buf_pos;
  char	*buffer;
  int	buf_size;
  int	fd;
}t_file;

#ifndef NULL
#define NULL (void *)0
#endif

#define END_OF_FILE	1000

t_file		*open_file(const char *);
void		*close_file(t_file *);
int		get_char(t_file *);
char		*get_line(t_file *);

#endif /* !READLIB_H_ */
