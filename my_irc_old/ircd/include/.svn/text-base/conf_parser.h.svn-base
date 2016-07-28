
#ifndef CONF_PARSER_H_
#define CONF_PARSER_H_

#include "libhash.h"
#include "readlib.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define UNUSED  __attribute__ ((unused))

struct s_filevar;

typedef struct s_parse
{
  const char	*file_name;
  t_file	*conf_file;
  t_hash	*vars_hash;
  void		*user_data;
  int		num_line;
  int		num_errors;
  char		*cur_error;
  char		*cur_line;
  char		*dup_line;
  char		*work_line;
  char		*var_name;

  char		affect_char;
  char		comment_char;

  int		(*redefvar_func)(struct s_parse *, struct s_filevar *);
  int		(*unknownvar_func)(struct s_parse *);
  int		(*syntax_err_func)(struct s_parse *);
  int		(*end_parse_func)(struct s_parse *);
}t_parse;

typedef struct s_filevar
{
  char		*var_name;
  void		*dest;
  int		(*get_val)(t_parse *, struct s_filevar *, char *);
  int		is_found;
  int		bound1;
  int		bound2;
  int		dec_line;
}t_filevar;

#define	VAR_HASH_SIZE	512

#define PARSE_ALL_OK		0
#define PARSE_OPEN_FAILED	-1
#define PARSE_MALLOC_FAILED	-2
#define PARSE_SYNTAX_ERR	-3
#define PARSE_FAILED		-4
#define PARSE_UNKNOWN_VAR	-5
#define PARSE_GETVAR_FAILED	-6
#define PARSE_REDEF_VAR		-7

/* default values for the file format */

#define DEFAULT_COMMENT	'#'
#define DEFAULT_AFFECT	'='

int		init_parse(t_parse *, const char *, int);
void		close_parse(t_parse *);
t_filevar	*add_var(t_parse *, const char *, void *,
			 int (*)(t_parse *, t_filevar *, char*));
t_filevar	*set_bounds(t_filevar *, int, int);
int		do_parse(t_parse *);
int		clean_str(t_parse *);
int		get_var_name(t_parse *t_p);

/* default functions */
int	def_syntax_error(t_parse *);
int	def_unknown_var(t_parse *);
int	def_redef_var(t_parse *, t_filevar *);
int	def_end_parse(t_parse *);

int	def_get_str(t_parse *, t_filevar *, char *);
int	def_get_int(t_parse *, t_filevar *, char *);
int	def_get_uint(t_parse *, t_filevar *, char *);
int	def_get_bound_int(t_parse *, t_filevar *, char *);
int	def_get_bit(t_parse *, t_filevar *, char *);

#endif /* !CONF_PARSER_H_ */
