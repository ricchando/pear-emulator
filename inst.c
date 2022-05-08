/* inst.c - pear instruction
 *
 * (C) 2022 Yota Sasaki
 * See LICENSE for license details.
*/

#include "pear.h"

void
op_ldws(Regfile *r, int disp, char mode)
{
  if(!r->z || (r->z & 0xf0))
    err_pear("Stack Overflow",r);

  r->y2_low = read_screen(r->z) & 0x0ff;
  r->y2_high = (read_screen(r->z) & 0xf00) >> 8;

  write_screen(r->z--,(r->y_high << 8) + r->y_low);

  r->y_low = r->x_low;
  r->y_high = r->x_high;

  if(mode){
    r->x_low = read_screen(disp+0x100) & 0x0ff;
    r->x_high = (read_screen(disp+0x100) & 0xf00) >> 8;
  }
  else{
    r->x_low = read_screen(disp+(r->y2_low + (r->y2_high << 8))) & 0x0ff;
    r->x_high = (read_screen(disp+(r->y2_low + (r->y2_high << 8))) & 0xf00) >> 8;
  }
}

void
op_sbn(Regfile *r, int disp)
{
  int al_upper, al_lower;

  al_upper = (r->y_high << 8) + r->y_low;
  al_lower = (r->x_high << 8) + r->x_low;

  if((al_lower = al_upper - al_lower)<0)
    write_screen(0,(read_screen(0)+disp));

  r->x_low = al_lower & 0x0ff;
  r->x_high = (al_lower & 0xf00) >> 8;

  r->y_low = r->z;
  r->y_high = 0;

  r->z = r->t;
}

void
op_stws(Regfile *r, int disp, char mode)
{
  if(r->z==15 || r->z & 0xf0)
    err_pear("Stack Underflow",r);

  r->y2_low = r->y_low;
  r->y2_high = r->y_high;

  if(mode){
    write_screen(disp+0x100, r->x_low + (r->x_high << 8));
  }
  else{
    write_screen(disp+(r->y2_low + (r->y2_high << 8)),
		 r->x_low + (r->x_high << 8));
  }

  r->x_low = r->y_low;
  r->x_high = r->y_high;
  r->y_low = read_screen(r->z) & 0x0ff;
  r->y_high = (read_screen(r->z++) & 0xf00) >> 8;
}

void
op_lix(Regfile *r, int val, char mode)
{
  if(mode){
    if(!r->z || (r->z & 0xf0)){
      err_pear("Stack Underflow",r);
    }
    write_screen(r->z--,(r->y_high << 8) + r->y_low);
  }
  else {
    r->t = r->z;
    r->z = r->y_low & 0x0f;
  }
  r->y_low = r->x_low;
  r->y_high = r->x_high;
  r->x_low = val & 0x0ff;
  r->x_high = (val & 0xf00) >> 8;
}

void
op_userop(Regfile *r, char op, char from, char to, char mode)
{
  int i,al_upper, al_lower;
  unsigned char *reg_at8[] =
    {&r->x_low,
     &r->x_high,
     &r->y_low,
     &r->y_high,
     &r->z,
     &r->t
    };

  if((op & 0x8)==0){
    if((from|to)>=2)
      err_pear("Illegal Addressing(Register)",r);
    if(from==REG_Y){
      al_upper = (r->y_high << 8) + r->y_low;
      al_lower = (r->x_high << 8) + r->x_low;
    }
    else{
      al_upper = (r->x_high << 8) + r->x_low;
      al_lower = (r->y_high << 8) + r->y_low;
    }
    switch(op){
    case 1:
      al_lower += al_upper;
      break;
    case 2:
      al_lower -= al_upper;
      break;
    case 3:
      al_lower <<= al_upper;
      break;
    case 4:
      al_lower >>= al_upper;
      break;
    case 5:
      al_lower |= al_upper;
      break;
    case 6:
      al_lower &= al_upper;
      break;
    case 7:
      al_lower ^= al_upper;
      break;
    default:
      err_pear("Internal Error", r);
      break;
    }
    r->x_low = al_lower & 0x0ff;
    r->x_high = (al_lower & 0xf00) >> 8;
  }
  else{
    if(from<2){
      r->y2_low = *reg_at8[from*2]; // 0 or 2
      r->y2_high = *reg_at8[from*2+1]; // 1 or 3
    }
    else{
      if(from==REG_Z && mode){
	r->y2_low = read_screen(r->z) & 0x0ff;
	r->y2_high = (read_screen(r->z) & 0xf00) >> 8;
      }
      else{
	r->y2_low = *reg_at8[from+2]; // 4 or 5 (2+2 or 3+2)
	r->y2_high = 0;
      }
    }
    switch(op){
    case 8:
      if(to==REG_Z && mode){
	write_screen(r->z,(r->y2_high << 8) + r->y2_low);
      }
      else if(to<2){
	*reg_at8[to*2] = r->y2_low;
	*reg_at8[to*2+1] = r->y2_high;
      }
      else{
	*reg_at8[to+2] = r->y2_low & 0xf;
      }
      break;
    case 9:
      if(to<2){
	if(from<2){
	  *reg_at8[from*2] = *reg_at8[to*2];
	  *reg_at8[from*2+1] = *reg_at8[to*2+1];

	  *reg_at8[to*2] = r->y2_low;
	  *reg_at8[to*2+1] = r->y2_high;
	}
	else{
	  *reg_at8[from+2] = *reg_at8[to*2] & 0xf;

	  *reg_at8[to*2] = r->y2_low;
	  *reg_at8[to*2+1] = r->y2_high;
	}
      }
      else{
	if(from<2){
	  *reg_at8[from*2] = *reg_at8[to+2] & 0xf;
	  *reg_at8[from*2+1] = 0;

	  *reg_at8[to+2] = r->y2_low & 0xf;
	}
	else{
	  *reg_at8[from+2] = *reg_at8[to+2] & 0xf;

	  *reg_at8[to+2] = r->y2_low & 0xf;
	}
      }
      break;
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
      err_pear("Not Implemented",r);
      break;
    default:
      err_pear("Internal Error",r);
      break;
    }
  }
}
