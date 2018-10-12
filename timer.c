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

int (timer_get_conf)(uint8_t timer, uint8_t *st) {

	
	u32_t byte = 0;

	byte = (byte | TIMER_RB_CMD | TIMER_RB_COUNT_); //Defining byte value

	if (sys_outb(TIMER_CTRL, byte) != 0) { //Checking for errors in the comand sys_outb 
		printf("Function error");
		return 1; //Must return non-zero value if the function doesn't work

	}



  switch(timer){  //Switch-case function to define the behaviour for the diffrent clocks, we will read and save the clock information in the byte variable

    case 0:
			sys_inb(TIMER_0, &byte);
			break;
   
    case 1:
			sys_inb(TIMER_1, &byte);
			break;

    case 2:
			sys_inb(TIMER_2, &byte);
			break;
  }

  *st = (uint8_t)byte;

  return 0;
}


int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {

	union timer_status_field_val conf;
	
	switch(field){
		case all:
			conf = st;
			break;
		case initial:
			switch(in_mode){
				case INVAL_val:
					break;
				case LSB_only:
					break;
				case MSB_only:	
					break;
				case MSB_after_LSB:
					break;
			}
		case mode:
			conf = (st | BIT(3)| BIT(2)| BIT(1));
			break;
		case base:
			conf = (st|BIT(0));
			break;

	}

  timer_print_config(timer, field, conf) 
  return 0;
}

