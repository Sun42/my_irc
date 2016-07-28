#include "conf_parser.h"

int	clean_str(t_parse *t_p)
{
  int	i;

  while (*(t_p->work_line) == ' ' || *(t_p->work_line) == '\t')
    t_p->work_line++;
  for (i = 0; t_p->work_line[i]; i++)
    if (t_p->work_line[i] == t_p->comment_char)
      {
	t_p->work_line[i] = '\0';
	break;
      }
  while (i && (t_p->work_line[i - 1] == ' ' || t_p->work_line[i - 1] == '\t'))
    i--;
  t_p->work_line[i] = '\0';
  return (strlen(t_p->work_line));
}
