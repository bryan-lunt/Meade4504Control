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

const int DATA_PIN = 4;
const int CLK_INTERRUPT = 0; // Pin 2.


const int DATASIZE = 2000;
const int NUM_BUFFS = 2;

const int CLOCK_EDGE = FALLING;

//The number of microseconds to wait for another timing pulse before deciding there won't be one.
const unsigned long PACKET_TIMEOUT = 4000;

volatile int x = 0;
volatile int buff_num = 0;
volatile int buff_sizes[NUM_BUFFS];
volatile byte data[NUM_BUFFS][DATASIZE];
volatile boolean to_send = false;
volatile unsigned long last_time;


void set_send(){
}

void pin2()
{
  int tmp_data = digitalRead(DATA_PIN);
 
  unsigned long new_time = micros();
  if(new_time - last_time > PACKET_TIMEOUT){
    to_send = true;
    buff_sizes[buff_num] = x;
    buff_num = (buff_num + 1) % NUM_BUFFS;
    x = 0;
  }
  data[buff_num][x] = tmp_data;
  x++;
  last_time = new_time;
  
}


void setup()
{
  Serial.begin(57600);
  attachInterrupt(CLK_INTERRUPT,pin2,CLOCK_EDGE);
  pinMode(DATA_PIN,INPUT);
  last_time = micros();
}

void loop()
{
   int my_buff = (buff_num + 1) % NUM_BUFFS;
   
   int num_bits;
   int i;
   if(to_send){
    num_bits = buff_sizes[my_buff];
    
    Serial.print(num_bits);
    Serial.print(" : ");
    
  
    for(i = 0;i<num_bits;i++){
      Serial.print(data[my_buff][i]);
    }
    Serial.println("");

    Serial.flush();
  }
  
}
