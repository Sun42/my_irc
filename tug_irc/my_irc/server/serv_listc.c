#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "server.h"



t_listc		*init_listc()
{
  t_listc	*first;

  first = malloc(sizeof(*first));
  first->next = first;
  first->sock = 0;
  first->channel = 0;
  first->name = "default_name";
  return (first);
}

void		add_listc(t_listc *first, int new_sock, char *name)
{
  t_listc	*new_listc;

  new_listc = malloc(sizeof(*new_listc));
  new_listc->next = first->next;
  new_listc->sock = new_sock;
  new_listc->channel = 42;
  new_listc->name = xstrdup(name);
  first->next = new_listc;
}

t_listh		*init_listh()
{
  t_listh	*first;

  first = malloc(sizeof(*first));
  first->next = first;
  first->num_chan = 0;
  first->name = "default chan";
  return (first);
}

t_listh		*add_listh(t_listh *first, char *name)
{
  t_listh	*new_listh;
  t_listh	*cur;
  t_listh	*prev;

  prev = first;
  cur = first->next;
  while (cur != first)
    {
      prev = cur;
      cur = cur->next;
    }
  new_listh = malloc(sizeof(*new_listh));
  new_listh->next = prev->next;
  new_listh->num_chan = prev->num_chan + 1;
  new_listh->name = xstrdup(name);
  prev->next = new_listh;
  return (new_listh);
}


t_listm		*init_listm()
{
  t_listm	*first;

  first = malloc(sizeof(*first));
  first->next = first;
  first->sock = 0;
  first->msg = "default message";
  return (first);
}

void		add_listm(t_listm *first, int sock, char *msg)
{
  t_listm	*new_listh;

  new_listh = malloc(sizeof(*new_listh));
  new_listh->next = first->next;
  new_listh->sock = sock;
  new_listh->msg = xstrdup(msg);
  first->next = new_listh;
}

void		add_all_listm(t_listm *firstm, t_listc *listc, char *msg)
{
  t_listc	*cur;

  add_listm(firstm, listc->sock, msg);
  if (listc->channel == 0)
    return ;
  cur = listc->next;
  while (cur != listc)
    {
      if (cur->channel == listc->channel)
	add_listm(firstm, cur->sock, msg);
      cur = cur->next;
    }
}

void		del_listm(t_listm *prev, t_listm *cur)
{
  prev->next = cur->next;
  free(cur->msg);
  free(cur);
}


void		show_listc(t_listc *first)
{
  t_listc	*listc;

  puts("########## CLIENTS ##############");
  listc = first->next;
  while (listc != first)
    {
      printf("addr : %p\nNext : %p\nsock : %d\nname : %s\nchannel : %d\n\n\n", (void*)listc,
	     (void *)listc->next, listc->sock, listc->name, listc->channel);
      listc = listc->next;
    }
}

void		show_listm(t_listm *first)
{
  t_listm	*listm;

  puts("########## MSG ##############");
  listm = first->next;
  while (listm != first)
    {
      printf("addr : %p\nNext : %p\nsock : %d\nmsg : %s\n\n", (void*)listm,
	     (void *)listm->next, listm->sock, listm->msg);
      listm = listm->next;
    }
}

void		show_listh(t_listh *first)
{
  t_listh	*listh;

  puts("######### CHANNELS ################");
  listh = first->next;
  printf("addr : %p\nNext : %p\nnum : %d\nname : %s\n\n\n", (void*)first,
	     (void *)first->next, first->num_chan, first->name);
  while (listh != first)
    {
      printf("addr : %p\nNext : %p\nnum : %d\nname : %s\n\n", (void*)listh,
	     (void *)listh->next, listh->num_chan, listh->name);
      listh = listh->next;
    }
  puts("######### END CHANNELS ############\n\n");
}
