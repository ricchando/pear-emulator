/* pear.h
 *
 * (C) 2022 Yota Sasaki
 * See LICENSE for license details.
*/

typedef struct Regfile {
  unsigned char x_high;
  unsigned char x_low;
  unsigned char y_high;
  unsigned char y_low;
  unsigned char y2_high;
  unsigned char y2_low;
  unsigned char z;
  unsigned char t;
} Regfile;

typedef enum reg_id {
  REG_X = 0,
  REG_Y = 1,
  REG_Z = 2,
  REG_T = 3,
  REG_Y2 = 7
} Reg_id;

extern int Screen[4096];

void err_pear(char *error_str, Regfile *r);

int read_screen(int addr);
void write_screen(int addr, int val);
void op_ldws(Regfile *r, int disp, char mode);
void op_sbn(Regfile *r, int disp);
void op_stws(Regfile *r, int disp, char mode);
void op_lix(Regfile *r, int val, char mode);
void op_userop(Regfile *r, char op, char from, char to, char mode);
void dump_mem();
void dump_reg(Regfile *r);
void msg();
