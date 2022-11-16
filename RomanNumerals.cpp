#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

int RomanToArabic (char num) 
{
	//Define the values
	switch(num) {
		case 'I':
			return 1;
			break;
		case 'V':
			return 5;
			break;
		case 'X':
			return 10;
			break;
		case 'L':
			return 50;
			break;
		case 'C':
			return 100;
			break;
		case 'D':
			return 500;
			break;
		case 'M':
			return 1000;
			break;
	}
	return 0;
}

int ConvertFromRoman (std::string s) {
	std::vector<int> values;
	for(int i = 0; i < s.length(); i++) {
		int a = RomanToArabic( s[i] );
		//Input is not I, V , X etc...
		if(a == 0 && s[i] != '\0') {
			std::cout << "Caught Exception: the given value: " << s[i] << " is not a valid roman numeral." << std::endl << std::endl;
			return 0;
		}
		int b = 0;
		if(i + 1 < s.length()) {
			b = RomanToArabic( s[i + 1] );
		}
		//Two values should be evaluated together, for example IV = 4, 
		if(b > a) {
			if(i - 1 >= 0) {
				int c = RomanToArabic( s[i - 1] );
				//Edge case: VIV = IX, Cannot have two V like this or even LIL = IC.
				if(c == b && (c == 5 || c == 50 || c == 500)) {
					std::cout << "Caught Exception: the given value: " << s[i-1] << s[i] << s[i+1] << " is not a valid roman numeral." << std::endl << std::endl;
					return 0;
				}
			}
			if(b - a == a) {
				//Edge case: VX = V, Should be written as just V
				std::cout << "Caught Exception: the given value: " << s[i] << s[i+1] << " is a redundant roman numeral." << std::endl << std::endl;
				return 0;
			}
			if(i + 2 < s.length()) {
				int d = RomanToArabic( s[i + 2] );
				if(a == d) {
					//Edge case: XLX = L , remove redundant values
					std::cout << "Caught Exception: the given value: " << s[i] << s[i+1] << s[i+2] << " is a redundant roman numeral." << std::endl << std::endl;
					return 0;
				}
			}
			if(! ( (a == 1 && b == 5) || (a == 1 && b == 10) || (a == 10 && b == 50) || (a == 10 && b == 100) || (a == 100 && b == 500) || (a == 100 && b == 1000) ) ) {
				//Edge case: Larger value is preceeded by something wrong, such as IC , XM
				std::cout << "Caught Exception: the given value: " << s[i] << s[i+1] << " is illegal." << std::endl << std::endl;
				return 0;
			}
			values.push_back(b - a);
			i += 1;
		}
		else {
			values.push_back(a);
		}
	}
	//Now we have converted the values
	//Now check for some more edge cases 
	int result = 0;
	for(int i = 0; i < values.size(); i++) {
		if(values[i] == 0) {
			break;
		}
		if(i - 1 >= 0) {
			//Edge case: numeral is not written in descending order. XMM (990 + 1000) is not valid. Should be: MCMXC (1000 + 900 + 90)
			if(values[i] > values[i - 1]) {
				std::cout << "Caught Exception: the roman numeral is not in descending order." << std::endl << std::endl;
				return 0;
			}
			//Edge case: numeral has more than one number divisible 5 in a row such as (VV or LL or DD)
			if((values[i] == 5 || values[i] == 50 || values[i] == 500) && values[i - 1] == values[i]) {
				std::cout << "Caught Exception: Exceeded maximum of one of the same number such as V, L or D in a row" << std::endl << std::endl;
				return 0;
			}
		}
		if(i - 3 >= 0) {
			//Edge case: Values such as IIII should be written as IV, in cases of M, there can be as many as you want.
			if(values[i - 3] == values[i] && values[i] != 1000) {
				std::cout << "Caught Exception: Exceeded maximum of three of the same number in a row" << std::endl << std::endl;
				return 0;
			}
		}
		result += values[i];
	}
	return result;
}



//This code implements the traditional values up to M = 1000.
//Program runs in O(2n) time.
int main () {
	while (true) {
		//Handle input and print
		std::cin.clear();
		std::string input = "";
		std::cin >> input;
		int result = ConvertFromRoman(input);
		if(result != 0) {
			std::cout << result << std::endl << std::endl;
		}
	}
}














