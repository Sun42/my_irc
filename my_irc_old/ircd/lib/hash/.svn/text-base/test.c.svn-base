
#include "libhash.h"
#include <stdio.h>

void	test_free(void *i)
{
  printf("deleting %d\n", *(int *)i);
}

int		main()
{
  t_hash	*h;
  int		i;
  int		*ptr;

  h = hcreate(101);
  i = 0;
  hadd(h, "test1", &i);
  hadd_dup(h, "test2", &i, sizeof(int));
  i = 42;
  hadd(h, "test3", &i);
  hadd_dup(h, "test4", &i, sizeof(int));
  i = 12;
  ptr = hget(h, "test1");
  printf("test1 -> %d\n", *ptr);
  ptr = hget(h, "test2");
  printf("test2 -> %d\n", *ptr);
  ptr = hget(h, "test3");
  printf("test3 -> %d\n", *ptr);
  ptr = hget(h, "test4");
  printf("test4 -> %d\n", *ptr);
  hdel(h, "test3", test_free);
  hdel(h, "test4", test_free);
  hfree(h, test_free);
}
