#include "RSA.h"
#include <iostream>
#include <fstream>
#include <random>

using namespace std;

std::vector<ULL> RSA::prime_table;

bool RSA::LoadPrimeTable(const std::string& name)
{
	ifstream input_file(name);
	if (!input_file.is_open()) return false;

	ULL prime_num;
	while (input_file >> prime_num)
	{
		RSA::prime_table.push_back(prime_num);
	}

	return true;
}



std::pair<Key, Key> RSA::GenerateKeys()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<unsigned int> gen_prime(0, RSA::prime_table.size() - 1);

	ULL p = RSA::prime_table[gen_prime(rng)];
	ULL q = RSA::prime_table[gen_prime(rng)];
	ULL n = p * q;
	ULL n_l = (p - 1) * (q - 1);


	ULL e = 1;
	for (; e < n_l; ++e)
	{

	}


	


}


ULL Encrypt(Key e, Key n);
ULL Decrypt(Key d, Key n);



std::pair<ULL, ULL> RSA::EEA(ULL x, ULL y)
{

}