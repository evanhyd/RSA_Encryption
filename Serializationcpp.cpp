#include <iostream>
#include <vector>
#include "RSA.h"


//converts char to 5 bits 
//a = 1, b = 2, c = 3, etc...(represented in binary)
std::vector<LL> Serialize(const std::string& str)
{
	std::vector<LL> serialize_data;
	LL serial = 0; 
	for (int i = 0; i < str.size(); i++)
	{
		// 6 letters for each unsigned long long 
		LL bits = str[i] - 'a' + 1;
		serial = serial << 5; 
		serial = serial | bits; 
		if ((i%6 == 0)||(i == str.size() - 1))
		{
			serialize_data.push_back(serial);
			serial = 0; 
		}
	}
	return serialize_data; 
}

//converts bits to char 
// 1 = a, 2 = b, 3 = c, etc...(represented in binary)
std::string Deserialize(std::vector<LL> number)
{
	std::string deserialized_data; 
	for (int i = 0; i < number.size(); i++)
	{
		LL serial = number[i];
		for (int j = 0; j < 5; j++)
		{
			char letter = serial & 0b11111;
		    letter = letter + 'a' - 1;
			deserialized_data.push_back(letter);
			serial = serial >> 5;
			if (serial == 0) break; //I want to test with str ending in 'a'
		}
	}
	return deserialized_data;
}


