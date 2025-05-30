/*
To start on the hardware side, I connected pins 2 - 5 in port D to their corresponding LEDs. I then 
connected each LED to a resistor that leads to GROUND on the ardurino. Then I connected the "click led" to pin 6 
and also connected it to ground with a resistor. Afterwards, I connected the joystick to the ardurino. Ground went
to ground, +5V went to 5V, VRx went to A0, VRy went to A1, and SW went to pin 7. For the code, I used the methods
analog_init() and analog8() given by the lab description to setup the joystick. In setup, I turned on the pins 2-6
to output power to leds, and I cleared pin 7 to make it take in input. In the loop, the main premise is to check if 
the joystick was pushed 80 units in either direction. The loop starts with getting coordinates of the joystick
and putting x and y in register 16 and 17 respectively. If the joystick is pushed 80 offset from the center, it turns 
on the corresponding led based on direction. The loop also checks if the joystick is clicked down and turns on the
led joystick if clicked. 

*/
void analog_init()
{
// Analog functions can be used as-is
  ADCSRA |= (1 << ADEN);
  ADMUX |= (1 << REFS0);
  ADMUX |= (1 << ADLAR); // Left justified output for 8bit mode
  ADCSRA |= (1 << ADSC);  // start conversion
}

uint8_t analog8(uint8_t channel)
{
  // Analog funcitions can be used as-is
  ADMUX &= 0xF0;
  ADMUX |= channel;
  ADCSRA |= (1 << ADSC);
  while ( ADCSRA & (1 << ADSC));
  return ADCH;
}

void setup() 
{
  Serial.begin(9600);
  analog_init();
  asm("sbi 0x0A, 6"); //sets bit 6 in portD for output
  asm("cbi 0x0A, 7"); //clears bit 7 in portD for input 
  asm("sbi 0x0B, 7"); //setting up pullup resistor for pin 7 in portD

  asm("sbi 0x0A, 5"); //sets ports to output to power leds
  asm("sbi 0x0A, 4");
  asm("sbi 0x0A, 3");
  asm("sbi 0x0A, 2");

}

void loop() {

asm("start: ");

// Get analog values for X and Y
// Load from ADCH (0x79) into r16/r17 
int x_axis = analog8(0);
asm(" lds r16, 0x79 ");
int y_axis = analog8(1);
asm(" lds r17, 0x79 ");

Serial.print("< "); //prints out coordinates to serial monitor to help with debugging
Serial.print(x_axis);
Serial.print(", ");
Serial.print(y_axis);
Serial.println(" >");
delay(2); 

asm(" in r25, 0x09 "); // Load PIND into r25 asm
asm(" andi r25, 0x80"); // ands all bits with 0x80 to mask the 7th bit and put in register 25
asm(" cpi  r25, 0x80"); // compares register 25 with 0x80 to check if the 7th bit is set
asm(" brne click_on");  // branches if 7th bit is set to subroutine "click on"
asm(" cbi  0x0B, 6"); //turns off click LED 

asm("left: "); // left led 
asm("subi r16, 0x50"); //checks if x axis is left (subtracts 80 from x-value in register 16 and checks if negative)
asm("brlo left_on"); // branches if result is negative
asm("cbi 0x0B, 2"); // turns off left LED

asm("up: "); // up led 
asm("subi r17, 0x50"); //checks if x axis is up (subtracts 80 from y-value in register 17 and checks if negative)
asm("brlo up_on"); 
asm("cbi 0x0B, 3"); 

asm("right: "); // right led
asm("subi r16, -0x50"); // add 80 since 80 was subtracted after checking in left subroutine since they both use register 16
asm("subi r16, -0x50"); // adds 80 to check for overflow (over 255)
asm("brsh right_on"); // branches if same or higher, branches if result is over 255
asm("cbi 0x0B, 4");

asm("down: "); // down led
asm("subi r17, -0x50");
asm("subi r17, -0x50");
asm("brsh down_on");
asm("cbi 0x0B, 5");

asm("rjmp end"); //jumps to end to loop after checking all directions and click

asm(" left_on: "); //turns on LEFT LED
asm(" sbi 0x0B, 2"); //sets bit on port 2 to turn on led
asm(" rjmp up  "); //jumps to up to check other directions

asm(" up_on: "); //turns on up led
asm(" sbi 0x0B, 3");
asm(" rjmp right ");

asm(" right_on: "); // turns on right led
asm(" sbi 0x0B, 4");
asm(" rjmp down");

asm(" down_on: "); // turns on down led
asm(" sbi 0x0B, 5");
asm(" rjmp end");

asm(" click_on: "); //turns on LED when clicked
asm(" sbi 0x0B, 6"); 

asm(" end: ");
asm(" rjmp start  ");

}



