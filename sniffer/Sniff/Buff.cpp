#include "Buff.h"

Buff::Buff(){
	size = 0;
	ready = false;
}

Buff::~Buff(){}

void Buff::put(int bit){
	data[size] = bit;
	size++;
}

void Buff::set_ready(boolean in){
	noInterrupts();
	ready = in;
	interrupts();
}

boolean Buff::get_ready(){
	boolean retval;
	noInterrupts();
	retval = ready;
	interrupts();
	return retval;
}

int Buff::get_size(){
	int retval;
	noInterrupts();
	retval = size;
	interrupts();
	return size;
}

void Buff::clear_buff(){
        noInterrupts();
        size = 0;
        ready = false;
        interrupts();
}


