#include <conf_parser.h>

int	def_syntax_error(t_parse *t_p)
{
  fprintf(stderr, "%s: %d: ERROR #%d: Syntax error in '%s'\n", t_p->file_name, t_p->num_line, t_p->num_errors, t_p->cur_line);
  return (1);
}

int	def_unknown_var(t_parse *t_p)
{
  fprintf(stderr, "%s: %d: ERROR #%d: Unknown variable '%s'\n", t_p->file_name, t_p->num_line, t_p->num_errors, t_p->var_name);
  return (1);
}

int	def_redef_var(t_parse *t_p, t_filevar *t_f)
{
  fprintf(stderr, "%s: %d: ERROR #%d: variable '%s' redefined (first definition on line %d)\n",
	  t_p->file_name, t_p->num_line, t_p->num_errors, t_p->var_name, t_f->dec_line);
  return (1);
}

int	def_end_parse(t_parse *t_p)
{
  if (t_p->num_errors)
    {
      fprintf(stdout, "\n**Parsing of '%s' finished whith %d error%s\n", t_p->file_name, t_p->num_errors, (t_p->num_errors > 1) ? "s" : "");
      return (0);
    }
  fprintf(stdout, "Parsing of '%s' succeded\n", t_p->file_name);
  return (1);
}
