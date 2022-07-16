/* screen.c - screen comands
 *
 * (C) 2022 Yota Sasaki
 * See LICENSE for license details.
*/

#include "pear.h"

int Screen[4096];

int
read_screen(int addr)
{
  return Screen[addr] & 0x0fff;
}


void
write_screen(int addr, int val)
{
  Screen[addr] = val & 0x0fff;
}

