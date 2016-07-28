#include "conf_parser.h"

int	set_file_var(t_parse *t_p, t_filevar *t_f)
{
  if (!t_f->is_found)
    {
      t_f->is_found = 1;
      t_f->dec_line = t_p->num_line;
      if (t_f->get_val && !t_f->get_val(t_p, t_f, t_p->work_line))
	return (PARSE_GETVAR_FAILED);
      return (PARSE_ALL_OK);
    }
  t_p->num_errors++;
  if (t_p->redefvar_func && !t_p->redefvar_func(t_p, t_f))
    {
      free(t_p->cur_line);
      free(t_p->dup_line);  
      return (PARSE_REDEF_VAR);
    }
  return (PARSE_ALL_OK);
}

int	parse_line(t_parse *t_p)
{
  t_filevar	*t_f;
  
  if (get_var_name(t_p) == PARSE_ALL_OK)
    {
      if ((t_f = (t_filevar *)hget(t_p->vars_hash, t_p->var_name)))
	return (set_file_var(t_p, t_f));
      t_p->num_errors++;
      if (t_p->unknownvar_func && !t_p->unknownvar_func(t_p))
	{
	  free(t_p->cur_line);
	  free(t_p->dup_line);
	  return (PARSE_UNKNOWN_VAR);
	}
      return (PARSE_ALL_OK);
    }
  t_p->num_errors++;
  if (t_p->syntax_err_func && !t_p->syntax_err_func(t_p))
    {
      free(t_p->cur_line);
      free(t_p->dup_line);  
      return (PARSE_SYNTAX_ERR);
    }
  return (PARSE_ALL_OK);
}

int	do_parse(t_parse *t_p)
{
  int	res;

  while ((t_p->cur_line = get_line(t_p->conf_file)))
    {
      t_p->num_line++;
      if (!(t_p->work_line = t_p->dup_line = strdup(t_p->cur_line)))
	return(PARSE_MALLOC_FAILED);
      if (clean_str(t_p))
	if ((res = parse_line(t_p)) != PARSE_ALL_OK)
	  return (res);
      free(t_p->cur_line);
      free(t_p->dup_line);
    }
  if (t_p->end_parse_func && !t_p->end_parse_func(t_p))
    return (PARSE_FAILED);
  return (PARSE_ALL_OK);
}
