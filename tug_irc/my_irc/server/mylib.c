

#include <stdio.h>
#include <string.h>

/****************************/
char * strdup (const char *s);

char	*xstrdup(char *str)
{
  char	*ret;

  if ((ret = strdup(str)) == NULL)
    {
      perror("strdup()");
      return (NULL);
    }
  return (ret);
}
