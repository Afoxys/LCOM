// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <minix/sysutil.h>  
// Any header files included below this line should have been created by you

#define DELAY_US 20000


#define STAT_REG    0x64
#define KBC_CMD_REG 0x64
#define BIT(n) (0x01<<(n))
#define OUT_BUF 0x60
#define TO_ERR BIT(6)
#define PAR_ERR BIT(7)

extern __uint32_t scancode;

int sys_inb_cnt(port_t port, __uint32_t *byte) {
  return sys_inb(port, byte);
  #ifdef LAB3
  return sys_inb_cnt(port, &byte);
  //count
  #else
  #define sys_inb_cnt(p,q) sys_inb(p,q)
  #endif
}

int issue_command_to_kbc(){
	int cmd = 0;
  int tickdelay_tries = 0;
  while( 1 ) {
	__uint32_t stat;
    sys_inb(STAT_REG, &stat);
    if( stat ) {
      sys_outb(OUT_BUF, cmd);
      if ( (stat & (PAR_ERR | TO_ERR)) == 0 )
        return 1;
      else
        return -1;
      }
    tickdelay(micros_to_ticks(DELAY_US));
    tickdelay_tries++;
	if (tickdelay_tries > 5) return -1;
  }
}

void (kbc_ih)() {
	while( 1 ) {
	 __uint32_t stat;
	 __uint32_t data;
    sys_inb(STAT_REG, &stat);
    if( (stat ) == 0 ) {
		  sys_inb(KBC_CMD_REG, &data);
      if ((stat &(PAR_ERR | TO_ERR)) == 0) {
        scancode = data;
        return;
      }
    }
  }
}

void (kbc_asm_ih)() {

	//TODO - Assembly program
  return;
}

