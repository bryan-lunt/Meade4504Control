/**
* Author : Bryan Lunt <blunt A.t._Mark cs DOT ucsd DOT edu>
* 
* This is a tool to sniff the bits sent on an I2C or similar 2-wire serial interface, captured bits are sent (currently as text) on the Arduino serial port to the host computer.
* 
* Currently, it assumes that packets of only a few ( < 2000) bits are sent at intervals, with some miliseconds of rest between.
* 
* It could be altered to read on the rising or falling edge of a clock signal. My application uses low clock voltage to indicate a bit.
*
* You will have to look up which interrupt corresponds to which pin for your particular Arduino.
*
*/

#include "Buff.h"

const int DATA_PIN = 4;
const int CLK_INTERRUPT = 0; // Pin 2.


const int DATASIZE = 1000;
const int NUM_BUFFS = 5;

const int CLOCK_EDGE = FALLING;

//The number of microseconds to wait for another timing pulse before deciding there won't be one.
const unsigned long PACKET_TIMEOUT = 4000;

volatile unsigned long current_read_buff = 0;
unsigned long current_print_buff = 0;
volatile unsigned long last_time;

volatile boolean overflow_error = false;

Buff buffers[NUM_BUFFS];



void pin2()
{
  int tmp_data = digitalRead(DATA_PIN);
 
  unsigned long new_time = micros();
  if(new_time - last_time > PACKET_TIMEOUT){
    buffers[current_read_buff].set_ready(true);
    current_read_buff = (current_read_buff + 1)%NUM_BUFFS;
  }
  if(buffers[current_read_buff].get_ready()){
    overflow_error = true;
  }
  
  buffers[current_read_buff].put(tmp_data);
  last_time = new_time;
  
}


void setup()
{
  int i;
  for(i = 0;i<NUM_BUFFS;i++){
    buffers[i] = Buff();
  }
  
  Serial.begin(57600);
  attachInterrupt(CLK_INTERRUPT,pin2,CLOCK_EDGE);
  pinMode(DATA_PIN,INPUT);
  last_time = micros();
}

void loop()
{
  int i;
  
  if(overflow_error){
    Serial.println("OVERFLOW OF BUFFERS");
  }
  
   if(!buffers[current_print_buff].get_ready()){
     return;
   }
   //The current buffer is ready to be output.
    int num_bits = buffers[current_print_buff].get_size();
    
    Serial.print(num_bits);
    if(num_bits < 10){
      Serial.print("  : ");
    }else{
      Serial.print(" : ");
    }
    
  
    for(i = 0;i<num_bits;i++){
      Serial.print(buffers[current_print_buff].data[i]);
    }
    
    buffers[current_print_buff].clear_buff();
    
    Serial.println("");
    Serial.flush();
    
    current_print_buff = (current_print_buff + 1) % NUM_BUFFS;
    

  
}
