#include <iostream>
#include <vector>
#include "RSA.h"


//converts char to 5 bits 
//a = 1, b = 2, c = 3, etc...(represented in binary)
std::vector<LL> RSA::Serialize(const std::string& str)
{
	std::vector<LL> serialize_data;
	LL serial = 0; 
	for (int i = 0; i < str.size(); i++)
	{
		// 6 letters for each unsigned long long 
		LL bits = str[i] - 'a' + 1;
		serial = serial << 5; 
		serial = serial | bits; 

		if (  i != 0 && i%5 == 0  ||(i == str.size() - 1))
		{
			serialize_data.push_back(serial);
			std::cout << serial << " ";
			serial = 0; 
		}
	}
	return serialize_data; 
}


//converts bits to char 
std::string RSA::Deserialize(const std::vector<LL>& serialized_data)
{
	std::string text; 
	for (int i = 0; i < serialized_data.size(); i++)
	{
		LL serial = serialized_data[i];
		for (int j = 1; j <= 6; j++)
		{
			//read from left most bit 
			char letter = (serial >> ((6 - j) * 5)) & 0b11111;
			if (letter == 0) continue; 
		    letter = letter + 'a' - 1;
			text.push_back(letter);
		}
	}
	return text;
}


