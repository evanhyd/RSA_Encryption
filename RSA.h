#pragma once
#include <vector>
#include <string>


using Key = unsigned long long;
using ULL = unsigned long long;

namespace RSA
{
	
	extern std::vector<ULL> prime_table;
	bool LoadPrimeTable(const std::string& name);
	
	std::pair<ULL, ULL> RSA::EEA(ULL x, ULL y);
	std::vector<ULL> Serialize(const std::string& str);
	std::string Deserialize(const std::vector<ULL>& serialized_data);

	std::pair<Key, Key> GenerateKeys();
	ULL Encrypt(ULL plain, Key e, Key n);
	ULL Decrypt(ULL cypher, Key d, Key n);

}

