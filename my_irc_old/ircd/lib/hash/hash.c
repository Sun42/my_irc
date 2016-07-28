
#include <libhash.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

t_hash		*hcreate(int size)
{
  t_hash	*table;
  int		i;

  if (!(table = malloc(sizeof(*table))))
    return (NULL);
  table->nb_elems = 0;
  table->nb_lines = 0;
  table->size = size;
  if (!(table->elems = malloc(table->size * sizeof(*table->elems))))
    return (NULL);
  for (i = 0; i < table->size; i++)
    table->elems[i] = NULL;
  return (table);
}

int		hash(t_hash *t, char *key)
{
  unsigned int	h;
  int		i;

  for (i = 0, h = 0; key[i]; i++)
    {
      h ^= (unsigned int) key[i];
      h = (h * FNV_PRIME_32) % t->size;
    }
  return ((int) h);
}

t_helem		*hadd(t_hash *t, char *key, void *data)
{
  int		hcode;
  t_helem	*el;

  if (!(el = malloc(sizeof(*el)))
      || !(el->key = strdup(key)))
    return (NULL);
  el->data = data;
  el->next = NULL;
  hcode = hash(t, el->key);
  if (t->elems[hcode] != NULL)
    el->next = t->elems[hcode];
  else
    t->nb_lines++;
  t->elems[hcode] = el; 
  (t->nb_elems)++;
  el->is_dup = 0;
  return (el);
}

t_helem		*hadd_dup(t_hash *t, char *key, void *data, size_t data_size)
{
  int		hcode;
  t_helem	*el;
  void		*data_dup;

  if (!(el = malloc(sizeof(*el))) ||
      !(el->key = strdup(key)))
    return (NULL);
  if (!(data_dup = malloc(data_size)))
    return (NULL);
  bcopy(data, data_dup, data_size);
  el->data = data_dup;
  el->next = NULL;
  el->is_dup = 1;
  hcode = hash(t, el->key);
  if (t->elems[hcode] != NULL)
    el->next = t->elems[hcode];
  else
    t->nb_lines++;
  t->elems[hcode] = el; 
  (t->nb_elems)++;
  return (el);
}

void		*hget(t_hash *t, char *key)
{
  t_helem	*list;

  list = t->elems[hash(t, key)];
  while (list)
    {
      if (!strcmp(list->key, key))
	return (list->data);
      list = list->next;
    }
  return (NULL);
}
