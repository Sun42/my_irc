
#include "conf_parser.h"
#include <string.h>

int	init_parse(t_parse *tp, const char *file_name, int var_size)
{
  memset(tp, 0, sizeof(t_parse));
  tp->file_name = file_name;
  if (!(tp->conf_file = open_file(file_name)))
    return (PARSE_OPEN_FAILED);
  if (!(tp->vars_hash = hcreate((var_size < 16) ? VAR_HASH_SIZE : var_size)))
    {
      close_file(tp->conf_file);
      return (PARSE_MALLOC_FAILED);
    }
  tp->affect_char = DEFAULT_AFFECT;
  tp->comment_char = DEFAULT_COMMENT;
  return (PARSE_ALL_OK);
}

void	clear_var(void *var)
{
  free(((t_filevar *)var)->var_name);
}

void	close_parse(t_parse *tp)
{
  close_file(tp->conf_file);
  hfree(tp->vars_hash, clear_var);
}

t_filevar	*add_var(t_parse *tp, const char *var_name, void *dest, int (*get_val)(t_parse *, t_filevar *, char *))
{
  t_filevar	new_var;
  t_helem	*node;

  if (!(new_var.var_name = strdup(var_name)))
    return (NULL);
  new_var.dest = dest;
  new_var.is_found = 0;
  new_var.get_val = get_val;
  if (!(node = hadd_dup(tp->vars_hash, new_var.var_name, &new_var, sizeof(new_var))))
    {
      free(new_var.var_name);
      return(NULL);
    }
  return (node->data);
}

t_filevar	*set_bounds(t_filevar *t_f, int b1, int b2)
{
  if (t_f)
    {
      t_f->bound1 = b1;
      t_f->bound2 = b2;
    }
  return (t_f);
}
