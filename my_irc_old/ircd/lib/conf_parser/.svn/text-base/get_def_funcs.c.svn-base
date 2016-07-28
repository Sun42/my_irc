#include <conf_parser.h>

int	def_get_str(UNUSED t_parse *t_p, t_filevar *t_f, char *val)
{
  int	s;

  if (val[0] == '"' || val[0] == '\\' || val[0] == '\'')
    val++;
  s = strlen(val);
  if (val[s - 2] == '\\')
    {
      val[s - 2] = val[s - 1];
      val[s - 1] = '\0';
    }
  else if (val[s - 1] == '"' || val[s - 1] == '\'')
    val[s - 1] = '\0';
  if (!(*((char **)t_f->dest) = strdup(val)))
    {
      fprintf(stderr, "Fatal: malloc failed");
      return (0);
    }
  return (1);
}

int	def_get_int(t_parse *t_p, t_filevar *t_f, char *val)
{
  int	res;
  char	*err;

  res = (int)strtol(val, &err, 0);
  if (*err)
    fprintf(stderr, "%s: %d: ERROR #%d: '%s' must be an integer\n", t_p->file_name, t_p->num_line, t_p->num_errors, t_p->var_name);
  else
    *((int *)t_f->dest) = res;
  return (1);
}

int	def_get_uint(t_parse *t_p, t_filevar *t_f, char *val)
{
  long	res;
  char	*err;

  res = strtol(val, &err, 0);
  if (*err || res < 0)
    fprintf(stderr, "%s: %d: ERROR #%d: '%s' must be a positive integer\n", t_p->file_name, t_p->num_line, t_p->num_errors, t_p->var_name);
  else
    *((unsigned int *)t_f->dest) = (unsigned int)res;
  return (1);
}

int	def_get_bound_int(t_parse *t_p, t_filevar *t_f, char *val)
{
  int	res;
  char	*err;

  res = (int)strtol(val, &err, 0);
  if (*err)
    fprintf(stderr, "%s: %d: ERROR #%d: '%s' must be an integer\n", t_p->file_name, t_p->num_line, t_p->num_errors, t_p->var_name);
  else if (res < t_f->bound1 || res > t_f->bound2)
    fprintf(stderr, "%s: %d: ERROR #%d: '%s' must be an integer between %d and %d\n",
	    t_p->file_name, t_p->num_line, t_p->num_errors, t_p->var_name, t_f->bound1, t_f->bound2);
  else
    *((int *)t_f->dest) = res;
  return (1);
}

/* uses bound1 as bit position (LSB is 0) */
int	def_get_bit(t_parse *t_p, t_filevar *t_f, char *val)
{
  if (!strcasecmp(val, "yes") || !strcasecmp(val, "y") || !strcasecmp(val, "true") || !strcmp(val, "1"))
    *((int *)t_f->dest) |= 1 << t_f->bound1;
  else if (!strcasecmp(val, "no") || !strcasecmp(val, "n") || !strcasecmp(val, "false") || !strcmp(val, "0"))
    *((int *)t_f->dest) &= ~(1 << t_f->bound1);
  else
    fprintf(stderr, "%s: %d: ERROR #%d: '%s' is a boolean\n", t_p->file_name, t_p->num_line, t_p->num_errors, t_p->var_name);
  return (1);
}
