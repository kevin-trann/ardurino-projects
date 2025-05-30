/*
To start, the first step is to load a full constant "0xFF" into register 16. This means that every bit
in register 16 is "1"/on. Then you turn on outputs for the data direction register addresses for port D
by loading the value from register 16 to that address. Next, I would plug in the pins from 0-6 into the 
seven segment display. I used resistors to ensure I didn't break the seven segment display by lowering 
the voltage. I then plugged in the ground to the seven segment display's "com" section. 

To start the loop, I would create the subroutine "loop", and then create a 1 second delay at the beginning 
to account of the delay when transferring from 9 to 0. Then I would turn on and clear pins based on which 
number I needed to display from 0-9 using SBI and LDI. I would light up the corresponding letters for each
number using the pins. I made sure to add a 1 second delay before each number to ensure that you're able to 
see the number for 1 second in addition to ensuring the display counts up properly like a timer. Then at the 
end, I created a jump back to the subroutine loop to ensure it loops properly back to 0.


*/


void setup() {
  
  asm("ldi r16, 0xFF"); // loads an immediate 0xFF to register 16
  asm("out 0x0A, r16"); // change 0x0A to output data which is the port D data direction register address by loading the value of r16 into the address
  
}

void loop() {
  //starts seven segment display at 0

  asm ("loop: "); // starts subroutine called loop
  delay(1000); // delays by a second
  asm("cbi 0x0B, 6"); //g       // clears bits for g so when it loops back from 9, it turns back to 0, 0x0B is the data address for port D, 6 is the pin number
  asm("sbi 0x0B, 0"); // a      // sets bits on for 0x05 which is the port B data register at pin 0 
  asm("sbi 0x0B, 1"); // b      
  asm("sbi 0x0B, 2"); // c
  asm("sbi 0x0B, 3"); // d
  asm("sbi 0x0B, 4"); // e
  asm("sbi 0x0B, 5"); // f
 

  delay(1000);

  // sets ports to display 1
  
  asm("cbi 0x0B, 0");
  asm("cbi 0x0B, 5");
  asm("cbi 0x0B, 3");
  asm("cbi 0x0B, 4");
  asm("cbi 0x0B, 6");
  asm("cbi 0x0B, 0");

  delay(1000);

  // sets ports for seven segment to display 2

  asm("sbi 0x0B, 0");
  asm("sbi 0x0B, 6"); 
  asm("sbi 0x0B, 4"); 
  asm("sbi 0x0B, 3");
  asm("sbi 0x0B, 7");
  asm("cbi 0x0B, 2"); 

  delay(1000);

  // sets ports for seven segment to display 3
  
  asm("sbi 0x0B, 2");
  asm("cbi 0x0B, 4");
  asm("cbi 0x0B, 5");
  asm("sbi 0x0B, 7");

  delay(1000);

  // sets ports for seven segment to display 4

  asm("sbi 0x0B, 4");
  asm("sbi 0x0B, 5"); 
  asm("cbi 0x0B, 3"); 
  asm("cbi 0x0B, 4"); 
  asm("cbi 0x0B, 0");

  delay(1000);

  // sets ports for seven segment to display 5

  asm("sbi 0x0B, 0");
  asm("sbi 0x0B, 3"); 
  asm("cbi 0x0B, 7"); 
  asm("cbi 0x0B, 1");

  delay(1000);

  // sets ports for seven segment to display 6

  asm("sbi 0x0B, 4");

  delay(1000);

  // sets ports for seven segment to display 7

  asm("sbi 0x05, 0"); 
  asm("sbi 0x0B, 7"); 
  asm("cbi 0x0B, 6"); 
  asm("cbi 0x0B, 5"); 
  asm("cbi 0x0B, 3"); 
  asm("cbi 0x0B, 4"); 
  asm("sbi 0x0B, 1");

  delay(1000);

  // sets ports for seven segment to display 8

  asm("sbi 0x0B, 6"); 
  asm("sbi 0x0B, 0");
  asm("sbi 0x0B, 7"); 
  asm("sbi 0x0B, 2"); 
  asm("sbi 0x0B, 3"); 
  asm("sbi 0x0B, 4"); 
  asm("sbi 0x0B, 5"); 

  delay(1000);

  // sets ports for seven segment to display 9

  asm("cbi 0x0B, 4"); 
  asm("rjmp loop "); // branch back to subroutine "loop" to keep looping the seven segment display from 0 to 9

}

