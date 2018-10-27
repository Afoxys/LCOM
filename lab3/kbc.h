

#define DELAY_US 20000



int sys_inb_cnt(port_t port, unsigned long *byte);

int issue_command_to_kbc();

void (kbc_ih)();

void (kbc_asm_ih)();

