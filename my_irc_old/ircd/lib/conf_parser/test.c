
#include "conf_parser.h"
#include <stdio.h>

#define	OPEN_FAILED_MSG	"Can't open file '%s'\n"

int	main()
{
  t_parse	t_p;
  int		res;
  char		*var;
  int		var2 = 3;
  int		var3 = 13;

  var = 0;
  if ((res = init_parse(&t_p, "test.conf", VAR_HASH_SIZE)) != PARSE_ALL_OK)
    {
      if (res == PARSE_OPEN_FAILED)
	fprintf(stderr, OPEN_FAILED_MSG, "test.conf");
      return (0);
    }
  t_p.syntax_err_func = def_syntax_error;
  t_p.end_parse_func = def_end_parse;
  t_p.unknownvar_func = def_unknown_var;
  t_p.redefvar_func = def_redef_var;
  add_var(&t_p, "toto", &var, def_get_str);
  add_var(&t_p, "tata", &var2, def_get_int);
  set_bounds(add_var(&t_p, "blah", &var3, def_get_bound_int), 10, 500);
  do_parse(&t_p);
  close_parse(&t_p);
  if (var)
    {
      printf("|%s|\n", var);
      free(var);
    }
  printf("%d\n", var2);
  printf("%d\n", var3);
  return (0);
}
