#include <iostream>
using namespace std;

int fatorial(int num) {

	if (num < 0) return 0;

	if ((num == 0) || (num == 1)) return 1;

	return num * fatorial(num-1);
}

int main() {
    
	int numero;
	cout << "digite um numero maior que zero: ";
	cin >> numero;
	
	cout << numero << "! = " << fatorial(numero) << endl;
	
	return 0;
}