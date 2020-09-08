#include <stdio.h>

int main(){
	int anos, afranio, ermengarda;
	anos = 0;
	afranio = 80;
	ermengarda = 45;
	while(afranio > ermengarda){
		afranio += 2;
		ermengarda += 3;
		anos++;
	}
	
	printf("%d anos.\n", anos);
	
	return 0;
}