#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>
#include "client.h"

gchar		**wordtab2(gchar *str, int nbwords);

gpointer	xg_malloc(gsize n_bytes)
{
  gpointer	ptr;

  if ((ptr = g_malloc(n_bytes)) == NULL)
    exit(EXIT_FAILURE);
  return (ptr);
}

gchar	**wordtab(gchar *str)	
{
  int	nbwords;
  gchar	**tab;

  nbwords = count_word(str);
  tab = wordtab2(str, nbwords);
  return (tab);
}

gchar	**wordtab2(gchar *str, int nbwords)
{
  gchar	**tab;
  int	i;
  int	flag;
  
  init_vars(&i, &flag);
  tab = xg_malloc(sizeof(*tab) * (nbwords + 1));
  while (*str)
    {
      if (isletter(*str))
        {
          if (!flag)
            {
	      tab[i] = xg_malloc(word_len(str) + 1);	
	      g_strlcpy(tab[i], str, word_len(str) + 1);
	      str += word_len(str) - 1;
	      flag = ++i;
	    }
        }
      else
	flag = 0;
      str++;
    }
  tab[nbwords] = 0;
  return (tab);
}

void	init_vars(int *i, int *flag)
{
  *flag = 0;
  *i = 0;
}
