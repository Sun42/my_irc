#include <stdlib.h>
#include <stdio.h>
#include "server.h"
#include <string.h>
int	strcasecmp(const char *s1, const char *s2);
char	*strcasestr(const char *s1, const char *s2);

void	func_nick(char *nick, t_listc *listc, t_listm *firstm)
{
  char	*tmp;
  char	str[BUF_SIZE];

  if (strlen(nick) <= 0)
    return ;
  if ((tmp = xstrdup(nick)) == NULL)
    return ;
  if (sprintf(str, "*** %s is now known as %s\n", listc->name, tmp) < 0)
    {
      perror("sprintf()");
      return ;
    }
  add_all_listm(firstm, listc, str);
  free(listc->name);
  listc->name = tmp;
}

t_listh		*find_chan(char *name_chan, t_listh *firsth)
{
  t_listh	*listh;

  listh = firsth->next;
  while (listh != firsth)
    {
      if (strcasecmp(listh->name, name_chan) == 0)
	return (listh);
      listh = listh->next;
    }
  return (NULL);
}

void		func_join(char *name_chan, t_listc *listc, t_listh *firsth, t_listm *firstm)
{
  t_listh	*listh;
  char		str[BUF_SIZE];

  listh = find_chan(name_chan, firsth);
  if (listh == NULL)
      listh = add_listh(firsth, name_chan);
  listc->channel = listh->num_chan;
  if (sprintf(str, "*** %s has joined channel #%s\n", listc->name, listh->name) < 0)
    {
      perror("sprintf()");
      return ;
    }
  add_all_listm(firstm, listc, str);
}

void		func_part(t_listc *listc, t_listm *firstm)
{
  char		str[BUF_SIZE];

  if (sprintf(str, "*** %s has left the channel\n", listc->name) < 0)
    {
      perror("sprintf()");
      return ;
    }
  add_all_listm(firstm, listc, str);
  listc->channel = 0;
}

void		buffer_send(int sock, char *add)
{
  static char	*buffer;
  static int	size_buf;
  int		size_tmp;

  if (buffer == NULL)
    {
      buffer = malloc(BUF_SIZE);
      buffer[0] = 0;
    }
  if (add != NULL)
    size_tmp = strlen(add);
  if ((size_buf + size_tmp + 1 > BUF_SIZE || add == NULL) && buffer != NULL)
    {
      write_client(sock, buffer);
      free(buffer);
      buffer = NULL;
      size_buf = 0;
    }
  if (add != NULL)
    {
      strcat(buffer, add);
      size_buf += size_tmp;
      buffer[size_buf] = '\n';
      size_buf++;
    }
}

void		func_listn(t_listc *listc, t_listh *firsth, t_listm *firstm)
{
  t_listh	*listh;
  char		str[BUF_SIZE];

  if (sprintf(str, "*** Name\n") < 0)
    {
      perror("sprintf()");
      return ;
    }
  listh = firsth->next;
  while (listh != firsth)
    {
      if (sprintf(str + strlen(str), "*** %s\n", listh->name) < 0)
	{
	  perror("sprintf()");
	  return ;
	}
      listh = listh->next;
    }
  add_listm(firstm, listc->sock, str);
}

void		func_lists(char *pattern, t_listc *listc, t_listh *firsth, t_listm *firstm)
{
  t_listh	*listh;
  char		str[BUF_SIZE];

  if (sprintf(str, "*** Name\n") < 0)
    {
      perror("sprintf()");
      return ;
    }
  listh = firsth->next;
  while (listh != firsth)
    {
      if (strcasestr(listh->name, pattern) != NULL)
	{
	  if (sprintf(str + strlen(str), "*** %s\n", listh->name) < 0)
	    {
	      perror("sprintf()");
	      return ;
	    }
	}
      listh = listh->next;
    }
  add_listm(firstm, listc->sock, str);
}

void		func_msg(char *msg, t_listc *listc, t_listm *firstm)
{
  char		str[BUF_SIZE];

  if (listc->channel == 0)
    return ;
  if (sprintf(str, "*%s* %s\n", listc->name, msg) < 0)
    {
      perror("sprintf()");
      return ;
    }
  add_all_listm(firstm, listc, str);
}

t_listc		*find_user(char *name, t_listc *firstc)
{
  t_listc	*listc;

  if (strlen(name) < 1)
    return (NULL);
  listc = firstc->next;
  while (listc != firstc)
    {
      if (strcasecmp(listc->name, name) == 0)
	return (listc);
      listc = listc->next;
    }
  return (NULL);
}

void	func_error()
{
  puts("fucking error");
}

void		func_msgp(char *msg, t_listc *listc, t_listm *firstm)
{
  char		str[BUF_SIZE];
  t_listc	*dest;

  dest = find_user(msg + strlen(msg) + 1, listc);
  if (dest == NULL)
    {
      func_error();
      return ;
    }
  if (sprintf(str, "->*%s* %s\n", listc->name, msg) < 0)
    {
      perror("sprintf()");
      return ;
    }
  add_listm(firstm, dest->sock, str);
}

void		func_user(t_listc *listc, t_listm *firstm)
{
  t_listc	*cur;
  char		str[BUF_SIZE];

  if (listc->channel == 0)
    {
      func_error();
      return ;
    }
  cur = listc->next;
  if (sprintf(str, "*** Users\n*** %s\n", listc->name) < 0)
    {
      perror("sprintf()");
      return ;
    }
  while (cur != listc)
    {
      if (cur->channel == listc->channel)
	{
	  if (sprintf(str + strlen(str), "*** %s\n", cur->name) < 0)
	    {
	      perror("sprintf()");
	      return ;
	    }
	}
      cur = cur->next;
    }
  add_listm(firstm, listc->sock, str);
}
