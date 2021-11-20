#pragma once
#include <vector>
#include <string>


using Key = long long;
using LL = long long;
using ULL = unsigned long long;


namespace RSA
{
	
	extern std::vector<LL> prime_table;
	bool LoadPrimeTable(const std::string& name);
	
	LL GCD(LL a, LL b);
	std::pair<LL, LL> EEA(LL x, LL y);
	std::vector<LL> Serialize(const std::string& str);
	std::string Deserialize(const std::vector<LL>& serialized_data);

	std::pair<std::pair<Key, Key>, std::pair<Key, Key>> GenerateKeys();
	std::vector<LL> Encrypt(const std::vector<LL>& plain, std::pair<Key, Key> public_key);
	std::vector<LL> Decrypt(const std::vector<LL>& cypher, std::pair<Key, Key> private_keys);

}

