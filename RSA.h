#pragma once
#include <vector>
#include <string>


using Key = unsigned long long;
using ULL = unsigned long long;

namespace RSA
{
	
	extern std::vector<ULL> prime_table;
	void LoadPrimeTable(const std::string& name);

	ULL Serialize(const std::string& str);
	std::string Deserialize(ULL number);


	std::pair<Key, Key> GenerateKeys();
	ULL Encrypt(Key e, Key n);
	ULL Decrypt(Key d, Key n);



	std::pair<ULL, ULL> EEA(int x, int y);
}

