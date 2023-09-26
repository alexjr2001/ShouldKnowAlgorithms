//Caesar Cipher 27/06/2020
#include<iostream>
#include<string.h>

//Alphabet to make the code more understandable
char alfa[26] = { 'a','b','c','d','e', 'f', 'g', 'h','i', 'j', 'k', 'l','m', 'n', 'o', 'p', 'q', 'r', 's', 't','u', 'v', 'w', 'x', 'y', 'z'};
char alfaMayuscula[26] = { 'A', 'B','C', 'D', 'E','F','G','H','I','J','K','L','M','N', 'O', 'P', 'Q', 'R', 'S',	'T','U', 'V','X','Y','Z'};
char result[100] = {};
std::string result2[100] = {};

void getMessage() {  		//Get a cipher message of maximum 100 chars
	char message[100];
	int resultado;
	int correct;   //Index of the correct message
	std::cout << "Type the message: \n"; //Receive the word
	std::cin >> message;
	//Algorithm Brute Force
	for (int i = 0; i < 26; i++) {		// Loops to get all the possible scenarios of the word
		std::cout << "\n" << i << ") Times of shifting -> " << i << ": ";
		for (int j = 0; j < strlen(message); j++) {
			for (int k = 0; k < 26; k++) {
				if (message[j] == alfa[k] || message[j] == alfaMayuscula[k]) {
					resultado = k + i;
					if (k + i > 25) { 		//Preventing to change from Z to A
						resultado = k + i - 26;
					}
					std::cout << alfa[resultado];
					result[j] = alfa[resultado];
				}
			}
		}
		result2[i] = result;
		for (int i = 0; i < strlen(result); i++) {
			result[i] = ' ';
		}
	}

	std::cout << "\nType the number of the phrase that makes sense: "; 		//Ask the user for the number of shifting to decode the message
	std::cin >> correct;
	system("cls");
	std::cout << "\nThe message is: " << result2[correct];
}

int main() {
	getMessage();
	return 0;
}