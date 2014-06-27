#ifndef BUFF_H
#define BUFF_H

#include <Arduino.h>

#ifndef BUFF_SIZE
#define BUFF_SIZE 200
#endif

class Buff{
	public:
		Buff();
		~Buff();
		void put(int bit);
		void set_ready(boolean in);
		boolean get_ready();

		int get_size( );
                void clear_buff();

		volatile int data[BUFF_SIZE];
	private:
		volatile int size;
		volatile boolean ready;
};


#endif
