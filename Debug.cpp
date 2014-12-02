extern "C"{
	#include<stdio.h>

	void debug_msg(const char* msg) {
		#ifdef DEBUG
			printf(msg);
		#undif
	}

}