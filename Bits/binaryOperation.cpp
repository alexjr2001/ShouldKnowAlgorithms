#include <iostream>
#include "math.h"

int numbers[2][100];	//Save the two numbers inserted
int bits;

void convertNumber(int num, int pos, int bits) {  //Convert number
	int multiplo = 2;				//Base
	bool noOverload = true;		//Is there an overload?
	if (num >= 0) {			//Verify if the number of bits will be enough (no overload)
	 numbers[pos][0] = 0;
		if (num >= pow(multiplo, bits - 1)) {
			std::cout << "An overload, try again!\n";
			noOverload = false;
		}
	}
	else if (num < 0) {			//Verify if the number of bits will be enough (no overload)
	 numbers[pos][0] = 1;
		int msb = pow(multiplo, bits - 1);   //Most significant bit
		num = msb + num;
		if (num < 0) {
			std::cout << "An overload, try again!\n";
			noOverload = false;
		}
	}

	if (noOverload) {						//We convert the number if there's no overload
		for (int i = 1; i < bits; i++) {	//In the for we substract the number if the current bit has higher value (1) otherwise the bit is 0
			int j = bits - (i + 1);
			int value = pow(multiplo, j);
			if (num >= value) {
				num -= value;
			 numbers[pos][i] = 1;
			}
			else {
			 numbers[pos][i] = 0;
			}
			if (num == 0) {
				break;
			}
		}
	}
}


int convertBinary(int* A, int* Q) {			//Convert binary to number
	int tam = bits * 2;
	int MSB = -1*(A[0] * pow(2,tam-1));		//Most significant bit
	int sum = 0;
	int result = 0;

	for (int i = 1; i < bits; i++) {				
		sum += A[i] * (pow(2, tam - 1 - i));
	}
	for (int i = 0; i < bits; i++) {
		sum += Q[i] * (pow(2, bits - 1 - i));
	}
	result = MSB + sum;


	return result;
}

void suma(int* A, int *M, int bits) { 	//Sum
	int carry = 0;
	int sum=0;
	for (int i = 0; i < bits; i++) {
		sum = A[bits - 1 - i] + M[bits - 1 - i]+carry;
		if (sum == 1) {
			A[bits - 1 - i] = 1;
			carry = 0;
		}
		else if (sum == 2) {
			A[bits - 1 - i] = 0;
			carry = 1;
		}
		else if (sum == 3) {
			A[bits - 1 - i] = 1;
			carry = 1;
		}
		else {
			A[bits - 1 - i] = 0;
			carry = 0;
		}
	}

}
void substraction(int* A, int* M, int bits) {
	//Flip the number 
	int carry = 1;
	int Minversa[100];			//M inverted
	for (int i = 0; i < bits; i++) {
		if (M[i] == 0) {
			Minversa[i] = 1;
		}
		else {
			Minversa[i] = 0;
		}
	}

	for (int i = 0; i < bits; i++) {
		int sum = Minversa[bits-1-i] + carry;
		if (sum == 1) {
			Minversa[bits - 1 - i] = 1;
			carry = 0;
		}
		else if (sum == 0) {
			Minversa[bits - 1 - i] = 0;
			carry = 0;
		}
		else {
			Minversa[bits - 1 - i] = 0;
			carry = 1;
		}
	}
	suma(A, Minversa, bits);
}

void shift(int *A, int *Q, int &q, int bits) {
	int cambio = A[bits-1];
	q = Q[bits - 1];
	for (int i = 0; i < bits-1; i++) {
		A[bits-1-i] = A[bits-2-i];
		Q[bits-1-i] = Q[bits-2-i];	
	}
	Q[0] = cambio;
}

void print2(int *A, int *Q, int *M,int q, int bits) {
	for (int i = 0; i < bits; i++) {
		std::cout << A[i] << " ";
	}
	std::cout << " ";
	for (int i = 0; i < bits; i++) {
		std::cout << Q[i] << " ";
	}
	std::cout << " " << q << "  ";

	for (int i = 0; i < bits; i++) {
		std::cout << M[i] << " ";
	}
	
}
void multiplication(int bits) {				//We make the multiplication
	int A[100];
	int Q[100];
	int M[100];
	int q=0;
	int veces = bits;
	for (int i = 0; i < bits; i++) {
		A[i] = 0;
		Q[i] = numbers[0][i];
		M[i] = numbers[1][i];
	}

	print2(A, Q, M, q, bits);
	std::cout << std::endl << std::endl;

	while (veces > 0) {
		if (Q[bits - 1] == 1 && q == 0) {
			substraction(A, M, bits);
			print2(A, Q, M, q, bits);
			std::cout << "A-M (Substraction)" << std::endl;
		}
		else if (Q[bits - 1] == 0 && q == 1) {
			suma(A, M, bits);
			print2(A, Q, M, q, bits);
			std::cout << "A+M (sum)" << std::endl;
		}
		shift(A, Q, q, bits);
		print2(A, Q, M, q, bits);
		std::cout << "shift\n" << std::endl;
		veces--;
	}
	
	//Print Result
	std::cout << "Result: ";
	for (int i = 0; i < bits; i++) {
		std::cout << A[i] << " ";
	}
	for (int i = 0; i < bits; i++) {
		std::cout << Q[i] << " ";
	}
	std::cout << "= " << convertBinary(A, Q);
}

void print(int bits) {
	std::cout << "\nMultiplicand(Q): ";
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < bits ; j++) {
			std::cout << numbers[i][j] << " ";
		}
		std::cout << std::endl;
		if(i==0) std::cout << "Multiplier(M): ";
	}
	std::cout << std::endl;
}

void askNumbers() {
	int a, b;
	std::cout << "\nInsert the quantity of bits: ";
	std::cin >> bits;
	std::cout << "\nInsert the first number: ";
	std::cin >> a;
	std::cout << "\nInsert the second number: ";
	std::cin >> b;

	convertNumber(a,0, bits);
	convertNumber(b,1, bits);
	print(bits);
	multiplication(bits);
}

int main() {
	askNumbers();
	return 0;
}