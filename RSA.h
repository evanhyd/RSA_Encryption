#pragma once
#include <vector>
#include <string>


using Key = unsigned long long;
using ULL = unsigned long long;
using LL = long long;

namespace RSA
{
	
	extern std::vector<LL> prime_table;
	bool LoadPrimeTable(const std::string& name);
	
	std::pair<LL, LL> EEA(LL x, LL y);
	std::vector<LL> Serialize(const std::string& str);
	std::string Deserialize(const std::vector<LL>& serialized_data);

	std::pair<Key, Key> GenerateKeys();
	LL Encrypt(LL plain, Key e, Key n);
	LL Decrypt(LL cypher, Key d, Key n);

}

