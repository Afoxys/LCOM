// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <minix/sysutil.h>
// Any header files included below this line should have been created by you
#include "kbc.h"

#define DELAY_US 20000  //Delay for the interrupts
#define IRQ1 1

uint8_t scancode;
uint8_t previous_scancode;




int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}



bool is_special() {
	if((scancode & 0xE0) == 0) return true;
	return false;
}


int read_scancode() {
	int size = 1;
	uint8_t bytes[2];
	if(previous_scancode) {
		size = 2;
		bytes[0] = previous_scancode;
		bytes[1] = scancode;
	} else {
		bytes[0] = scancode;
	}

	bool make = (scancode & 0x80);
	if (scancode == 0x81) { return -1; }
	kbd_print_scancode(make, size, bytes);
/*
	printf("Number of sys_in calls %d", int kbd_print_no_sysinb( cnt));
	if (kbd_print_no_sysinb(cnt) == 0) {
		return -1;
	}
	return 0; */
	return 0;
}

int (kbd_test_scan)(bool UNUSED(assembly)) {
	//variavel global mudada em kbc_ih
	

  int policy = IRQ_REENABLE | IRQ_EXCLUSIVE;

	int hook_id = 0;
	int temp_hook_id = hook_id;

  sys_irqsetpolicy(IRQ1, policy, &temp_hook_id);

  int ipc_status;
  message msg;
	
  while( 1 ) {
		int r;
		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
    if (is_ipc_notify(ipc_status)) { /* received notification */ 
      switch (_ENDPOINT_P(msg.m_source)) { 
        case HARDWARE: // hardware interrupt notification 
					if (msg.m_notify.interrupts & temp_hook_id) { // subscribed interrupt
						if(false) {
							kbc_asm_ih();
						} else {
							kbc_ih();
						}
						if(is_special() && !previous_scancode) {
							previous_scancode = scancode;
							break;
						}
						read_scancode();
						previous_scancode = 0;
					}
					break;
				default:
					break;
      } 
    } else {

    } 
  }
	
	if(false) sys_irqrmpolicy(&temp_hook_id);
	return -1;
}





int (kbd_test_poll)() {
	/*int policy = IRQ_REENABLE | IRQ_EXCLUSIVE;
	int hook_id = 0;
	int temp_hook_id = hook_id;
	sys_irqsetpolicy(IRQ1, policy, *temp_hook_id);
	int tickdelay_tries = 0;

	int ipc_status;
	message msg;

	int bottom_read = 0x20, bottom_write = 0x60;
	int top_check_kbc = 0xAA, top_check_kbi = 0xAB, top_disable_kbi = 0xAD, top_enable_kbi = 0xAE;

		0x20
			Read Command Byte
			Returns Command Byte
		0x60
			Write Command Byte
			Takes A : Command Byte
		0xAA
			Check KBC(Self - test)
			Returns 0x55, if OK
			Returns 0xFC, if error
		0xAB
			Check Keyboard Interface
			Returns 0, if OK
		0xAD
			Disable KBD Interface
		0xAE
			Enable KBD Interface*/

/*

	while (1){
		sys_inb(STAT_REG, bottom_read);
		if (stat & OBF) {
			sys_inb(OUT_BUF, &data);
			if ((stat &(PAR_ERR | TO_ERR)) == 0)
				return data;
			else
				return -1;
		}
		if (stat & OBF) {
			sys_inb(OUT_BUF, bottom_write);
			if ((stat &(PAR_ERR | TO_ERR)) == 0)
				return data;
			else
				return -1;
		}
		if (stat & OBF) {
			sys_inb(OUT_BUF, top_check_kbc);
			if ((stat &(PAR_ERR | TO_ERR)) == 0)
				return data;
			else
				return -1;
		}
		if (stat & OBF) {
			sys_inb(OUT_BUF, top_check_kbi);
			if ((stat &(PAR_ERR | TO_ERR)) == 0)
				return data;
			else
				return -1;
		}
		if (stat & OBF) {
			sys_inb(OUT_BUF, top_disable_kbi);
			if ((stat &(PAR_ERR | TO_ERR)) == 0)
				return data;
			else
				return -1;
		}
		if (stat & OBF) {
			sys_inb(OUT_BUF, top_enable_kbi);
			if ((stat &(PAR_ERR | TO_ERR)) == 0)
				return data;
			else
				return -1;
		}*/
		return 0;
}
int (kbd_test_timed_scan)(uint8_t UNUSED(n)) {
    /* To be completed */
    /* When you use argument n for the first time, delete the UNUSED macro */
		return 0;
}


