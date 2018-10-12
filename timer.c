#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t UNUSED(timer), uint32_t UNUSED(freq)) {
	
	uint8_t byte = 0;
	//Read the timer configuration
	byte = 0;//(byte | TIMER_RB_CMD | BIT(5)); // Must use the read-back command so that it does not change the 4 LSBs (mode and BCD/binary) of the timer's control word.
	//int util_get_LSB(uint16_t val, uint8_t *lsb)
	//int util_get_MSB(uint16_t val, uint8_t *msb)
  return 1;
}

int (timer_subscribe_int)(uint8_t *UNUSED(bit_no)) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_unsubscribe_int)() {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void (timer_int_handler)() {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int (timer_get_conf)(uint8_t UNUSED(timer), uint8_t *UNUSED(st)) {

	uint8_t status;
	uint8_t byte = 0;

	byte = (byte | TIMER_RB_CMD | BIT(5)); //Defining byte value

	if (sys_outb(TIMER_CTRL, byte) != 0) { //Checking for errors in the comand sys_outb 
		printf("Function error");
		return 1; //Must return non-zero value if the function doesn't work

	}



  switch(timer){  //Switch-case function to define the behaviour for the diffrent clocks, we will read and save the clock information in the byte variable

    case 0:
		sys_inb(TIMER_0, byte);
		sys_out(TIMER_0, &byte);
		break;
   
    case 1:
		sys_inb(TIMER_1, byte);
		sys_out(TIMER_1, &byte);
		break;

    case 2:
		sys_inb(TIMER_2, byte);
		sys_out(TIMER_2, &byte);
		break;
  }

  *st = byte;

  return 0;
}


int timer_display_conf(uint8_t UNUSED(timer), uint8_t UNUSED(st), enum timer_status_field UNUSED(field)) {
  timer_print_config(timer, field, st)
  return 1;
}


int util_get_LSB(uint16_t val, uint8_t *lsb) {
	return 1; //Returns the LSB of a 2 byte integer.
}
int util_get_MSB(uint16_t val, uint8_t *msb) {
	//Poem metade do val em msb
	//Returns the MSB of a 2 byte integer.
	return 1;
}