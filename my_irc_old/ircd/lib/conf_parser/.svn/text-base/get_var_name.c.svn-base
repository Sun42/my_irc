#include "conf_parser.h"

int	get_var_name(t_parse *t_p)
{
  int i;

  t_p->var_name = t_p->work_line;
  while (*(t_p->work_line) && *(t_p->work_line) != t_p->affect_char)
    ++(t_p->work_line);
  if (*(t_p->work_line) == '\0')
    return (PARSE_SYNTAX_ERR);
  *(t_p->work_line++) = '\0';
  for (i = strlen(t_p->var_name) - 1; i >= 0 && (t_p->var_name[i] == ' ' || t_p->var_name[i] == '\t'); i--)
    ;
  t_p->var_name[i + 1] = '\0';
  while (*(t_p->work_line) == ' ' || *(t_p->work_line) == '\t')
    t_p->work_line++;
  if (!strlen(t_p->work_line) || !strlen(t_p->var_name))
    return (PARSE_SYNTAX_ERR);
  return (PARSE_ALL_OK);
}
