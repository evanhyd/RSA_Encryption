#include "RSA.h"
#include <iostream>
#include <fstream>
#include <random>


std::vector<LL> RSA::prime_table;

bool RSA::LoadPrimeTable(const std::string& name)
{
	std::ifstream input_file(name);
	if (!input_file.is_open()) return false;

	LL prime_num;
	while (input_file >> prime_num)
	{
		RSA::prime_table.push_back(prime_num);
	}

	return true;
}


//convert string to bits sequence, 5 bit per char
std::vector<LL> RSA::Serialize(const std::string& str)
{
	std::vector<LL> serialized_data;
	LL serial = 0;

	for (int i = 0; i < str.size(); i++)
	{
		// 6 letters for each long long 
		LL bits = str[i] - 'a' + 1;
		serial <<= 5;;
		serial |= bits;

		if (i != 0 && i % 5 == 0 || i == str.size() - 1)
		{
			serialized_data.push_back(serial);
			serial = 0;
		}
	}
	return serialized_data;
}


//convert bits sequence to string
std::string RSA::Deserialize(const std::vector<LL>& serialized_data)
{
	std::string str;

	for (LL serial : serialized_data)
	{
		for (int bit_index = 1; bit_index <= 6; bit_index++)
		{
			//read from left most bit 
			char letter = (serial >> ((6 - bit_index) * 5)) & 0b11111;
			if (letter == 0) continue;
			letter = letter + 'a' - 1;
			str.push_back(letter);
		}
	}

	return str;
}





std::pair<std::pair<Key, Key>, std::pair<Key, Key>> RSA::GenerateKeys()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<LL> gen_prime(0, RSA::prime_table.size() - 1);

	LL p = RSA::prime_table[gen_prime(rng)];
	LL q = RSA::prime_table[gen_prime(rng)];
	LL n = p * q;
	LL n_l = (p - 1) * (q - 1);


	//pick public key, e and n_l are coprime
	LL e = 3;
	for (; e < n_l; ++e)
	{
		if (RSA::GCD(e, n_l) == 1) break;
	}


	//ed = 1 (mod n_l), notice it always have solution by LCDT 1
	std::pair<Key, Key> keys = RSA::EEA(n_l, e);
	if (keys.second < 0) keys.second += n_l;

	//remember to change it later
	return std::make_pair(std::make_pair(e, keys.second), std::make_pair(p, q));
}


LL RSA::GCD(LL a, LL b)
{
	while (b != 0)
	{
		LL temp = b;
		b = a % b;
		a = temp;
	}

	return abs(a);
}

std::pair<LL, LL> RSA::EEA(LL x, LL y)
{
	if (x < y) return std::make_pair(0, 0);

	LL s1 = 1, t1 = 0, r1 = x, q1 = 0;
	LL s2 = 0, t2 = 1, r2 = y, q2 = 0;
	LL s3 = 0, t3 = 0, r3 = 0, q3 = 0;

	while (true)
	{
		q3 = r1 / r2;
		s3 = s1 - s2 * q3;
		t3 = t1 - t2 * q3;
		r3 = r1 - r2 * q3;

		if (r3 == 0) return std::make_pair(s2, t2);

		//update table
		s1 = s2; t1 = t2; r1 = r2; q1 = q2;
		s2 = s3; t2 = t3; r2 = r3; q2 = q3;
	}
}

std::vector<LL> RSA::Encrypt(const std::vector<LL>& plain, std::pair<Key, Key> public_key)
{
	std::vector<LL> cypher;

	for (LL serial : plain)
	{
		LL c = 1;
		for (LL power = 0; power < public_key.first; ++power)
		{
			//prevent overflow
			c *= serial;
			c %= public_key.second;
		}

		cypher.push_back(c);
	}

	return cypher;
}

std::vector<LL> RSA::Decrypt(const std::vector<LL>& cypher, std::pair<Key, Key> private_key)
{
	std::vector<LL> plain;

	for (LL serial : cypher)
	{
		LL r = 1;
		for (LL power = 0; power < private_key.first; ++power)
		{
			//prevent overflow
			r *= serial;
			r %= private_key.second;
		}

		plain.push_back(r);
	}

	return plain;
}


std::vector<LL> RSA::Decrypt(const std::vector<LL>& cypher, std::pair<Key, Key> private_keys, std::pair<Key, Key> primes)
{
	std::vector<LL> plain;

	LL d = private_keys.first;
	LL n = private_keys.second;
	LL p = std::max(primes.first, primes.second);
	LL q = std::min(primes.first, primes.second);

	for (LL serial : cypher)
	{
		//apply SMT to reduce the modulo num
		//applly FLT to reduce the exponents
		LL s1 = 1;
		LL power_1 = d % (p - 1);
		for (LL power = 0; power < power_1; ++power)
		{
			s1 *= serial;
			s1 %= n;
		}

		LL s2 = 1;
		LL power_2 = d % (q - 1);
		for (LL power = 0; power < power_2; ++power)
		{
			s2 *= serial;
			s2 %= n;
		}


		//apply CRT since s1 != s2
		//linear diophantine p*x + q*y = s2 - s1
		LL s_d = s2 - s1;
		LL deciphered = (p * RSA::EEA(p, q).first * (s_d) + s1) % n;
		if (deciphered < 0) deciphered += n;
		plain.push_back(deciphered);
	}

	return plain;
}
