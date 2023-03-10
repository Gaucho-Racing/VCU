#include <Arduino.h>
#include <imxrt.h>

volatile int foo = 0;

void IRQ_GPI01_INT0_Handler() {
  
  foo = 1;
  
}

void setup() {
  
  NVIC_ENABLE_IRQ(IRQ_GPIO1_INT0);
  attachInterruptVector(IRQ_GPIO1_INT0, &IRQ_GPI01_INT0_Handler);

}

void loop() {
  // generate a random integer between 0 and 5
  foo = random(6);

  // check if foo is greater than 1
  Serial.print("foo is ");
  Serial.print(foo);
  if (foo > 1) {
    // set the interrupt flag for PORTB in the NVIC
    NVIC_TRIGGER_IRQ(IRQ_GPIO1_INT0);
  }
  Serial.print("foo is ");
  Serial.print(foo);

  delay(1000); // wait for 1 second
}


