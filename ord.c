#include <glib.h>
#include <glib/gprintf.h>
#include <stdlib.h>
#include "client.h"

void	free_tab(gchar **tab)
{
  int	i;

  i = 0;
  while (i < count_tab(tab) - 1)
    {
      i++;
      g_free(tab[i]);
    }
  g_free(tab);
}

int	count_tab(gchar **tab)
{
  int	i;
  
  i = 0;
  while (tab[i] != 0)
    {
      i++;
    }
  return (i);
}

int	word_len(gchar *str)
{
  int	i;

  i = 0;
  while (isletter(str[i]))
    i++;
  return (i);
}

int	count_word(gchar *str)
{
  int	i;
  int	flag;

  flag = 0;
  i = 0;
  while (*str)
    {
      if (isletter(*str) && !flag)
	{
	  i++;
	  flag = 1;
	}
      if (!isletter(*str))
	flag = 0;
      str++;
    }
  return (i);
}


int	isletter(char c)
{
  if (c >= '!' && c <= '~')
    return (1);
  return (0);
}

void	my_putchar(char c)
{
  write(1, &c, 1);
}

