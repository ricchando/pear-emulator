/* dump.c - dump function
 *
 * (C) 2022 Yota Sasaki
 *
*/

#include <stdio.h>
#include "pear.h"

void
dump_mem()
{
  int i,j;

  for(i=0;i<24;i++){
    for(j=0;j<15;j++){
      printf(" %04x,",Screen[j+(i*16)]);
    }
    printf(" %04x :%03x0 \n",Screen[j+(i*16)],i);
  }
}

void
dump_reg(Regfile *r)
{
  printf("x: %04x y: %04x y2: %04x z: %02x t: %02x\n",
	 ((r->x_high & 0x0f) << 8) + r->x_low,
	 ((r->y_high & 0x0f) << 8) + r->y_low,
	 ((r->y2_high & 0x0f) << 8) + r->y2_low,
	 r->z,r->t);
}

