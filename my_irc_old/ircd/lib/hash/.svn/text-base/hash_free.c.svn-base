
#include <libhash.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

int		hdel(t_hash *t, char *key, void (*free_func)(void *))
{
  t_helem	*list;
  t_helem	*tmp_list;
  int		hcode;

  hcode = hash(t, key);
  if (t->elems[hcode] == NULL)
    return (0);
  tmp_list = NULL;
  for (list = t->elems[hcode]; list != NULL;
       tmp_list = list, list = list->next)
    if (!strcmp(key, list->key))
      {
	if (tmp_list == NULL)
	  t->elems[hcode] = list->next;
	else
	  tmp_list->next = list->next;
	free(list->key);
	if (free_func)
	  free_func(list->data);
	if (list->is_dup)
	  free(list->data);
	free(list);
	t->nb_elems--;
	if (t->elems[hcode] == NULL)
	  t->nb_lines--;
	return (1);
      }
  return (0);
}

void		hfree(t_hash *t, void (*free_func)(void *))
{
  int		i;
  t_helem	*curr;
  t_helem	*prev;

  for (i = 0; i < t->size; i++)
    {
      curr = t->elems[i];
      t->elems[i] = NULL;
      while (curr)
	{
	  free(curr->key);
	  if (free_func)
	    free_func(curr->data);
	  if (curr->is_dup)
	    free(curr->data);
	  prev = curr;
	  curr = curr->next;
	  free(prev);
	}
    }
  free(t->elems);
  free(t);
}
