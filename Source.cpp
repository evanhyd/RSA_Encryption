#include <iostream>
#include "RSA.h"

int main()
{
	if (!RSA::LoadPrimeTable("prime_list.txt")) std::cout << "Could not find the prime list\n";


	//generate RSA keys
	auto package = RSA::GenerateKeys();
	LL e = package.first.first;
	LL d = package.first.second;
	LL n = package.second.first * package.second.second;
	auto public_keys = std::make_pair(e, n);
	auto private_keys = std::make_pair(d, n);

	std::cout << "Public Keys: " << e << ' ' << n << '\n';
	std::cout << "Private Keys: " << d << ' ' << n << '\n';


	//input text
	std::string plain;
	std::cin >> plain;


	//serialize text
	std::vector<LL> serialized_data = RSA::Serialize(plain);

	for (LL serial : serialized_data)
	{
		std::cout << serial << ' ';
	}
	std::cout << '\n';

	
	//encrypt with public keys
	std::vector<LL> cypher = RSA::Encrypt(serialized_data, public_keys);

	for (LL c : cypher)
	{
		std::cout << c << ' ';
	}
	std::cout << '\n';


	//decrypt with private keys
	std::vector<LL> decyphered = RSA::Decrypt(cypher, private_keys, package.second);

	for (LL serial : decyphered)
	{
		std::cout << serial << ' ';
	}
	std::cout << '\n';


	//checking the text
	std::string deciphered_plain = RSA::Deserialize(decyphered);
	
	std::cout << deciphered_plain << '\n';

}