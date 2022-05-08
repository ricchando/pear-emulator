/* msg.c - message and error function
 *
 * (C) 2022 Yota Sasaki
 * See LICENSE for license details.
*/

#include <stdio.h>
#include <stdlib.h>
#include "pear.h"

void
err_pear(char *error_str, Regfile *r)
{
  fprintf(stderr,"ERR: %s\n",error_str);
  fprintf(stderr,"Previous Register Status:\n");
  dump_reg(r);
  exit(1);
}

void
msg()
{
  printf("PEAR Version 0;1\'0\"0\n");
  printf("(C) 2022 Yota Sasaki\n");
  printf("See LICENSE for license details.\n\n");
}
