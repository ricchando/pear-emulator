/* pear.c
 * 遊び方はREADME.mdを参照ください。
 * (C)2022 Yota Sasaki
 * See LICENSE for license details.
*/

#include <stdio.h>
#include <stdlib.h>
#include "pear.h"

int
main()
{
  msg();

  Regfile *r = malloc(sizeof(Regfile));

  char *etest = "This is a test";

  /* レジスタの初期値 */

  r->x_high = 0x1;
  r->x_low = 0x22;
  r->y_high = 0x3;
  r->y_low = 0x44;
  r->y2_high = 0;
  r->y2_low = 0;
  r->z = 0xe;
  r->t = 0xc;

  /* 直接実行したい命令を入力 */
  /* 実装している命令についてはinst.cを参照 */

  write_screen(0xe,0x0677);
  op_userop(r,8,REG_Z,REG_X,1);

  /* 命令はここまで。以下は終了後のレジスタとメモリの表示 */

  dump_reg(r);
  dump_mem();

  free(r);
}
