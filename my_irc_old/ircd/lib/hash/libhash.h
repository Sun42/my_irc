#ifndef		_LIBHASH_H_
# define	_LIBHASH_H_

#include <sys/types.h>

#define FNV_PRIME_32	16777619

#ifndef NULL
#define NULL (void *)0
#endif

typedef	struct		s_hash_elem
{
  char			*key;
  void			*data;
  short			is_dup;
  struct s_hash_elem	*next;
}			t_helem;

typedef	struct
{
  t_helem	**elems;
  int		nb_elems;
  int		nb_lines;
  int		size;
}		t_hash;

/* hash.c */
t_hash		*hcreate(int);
t_helem		*hadd(t_hash *, char *, void *);
t_helem		*hadd_dup(t_hash *, char *, void *, size_t);
void		*hget(t_hash *, char *);
int		hdel(t_hash *, char *, void (*)(void*));
void		hfree(t_hash *, void (*)(void*));
int		hash(t_hash *, char *);

#endif		/* !_LIBHASH_H_ */
