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



std::pair<Key, Key> RSA::GenerateKeys()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> gen_prime(0, RSA::prime_table.size() - 1);

	LL p = RSA::prime_table[gen_prime(rng)];
	LL q = RSA::prime_table[gen_prime(rng)];
	LL n = p * q;
	LL n_l = (p - 1) * (q - 1);


	LL e = 1;
	for (; e < n_l; ++e)
	{

	}


	//remember to change it later
	return std::make_pair(e, e);
	


}


LL Encrypt(Key e, Key n);
LL Decrypt(Key d, Key n);



std::pair<LL, LL> RSA::EEA(LL x, LL y)
{
	if (x < y) return std::make_pair(0, 0);

	LL s1 = 1, t1 = 0, r1 = x, q1 = 0;
	LL s2 = 0, t2 = 1, r2 = y, q2 = 0;
	LL s3 = 0, t3 = 0, r3 = 0, q3 = 0;

	while (true)
	{

		std::cout << s3 << ' ' << t3 << ' ' << r3 << ' ' << q3 << '\n';

		q3 = r1 / r2;
		std::cout << q3 << '\n';


		s3 = s1 - s2 * q3;
		std::cout << s3 << '\n';

		t3 = t1 - t2 * q3;
		std::cout << t3 << '\n';
		
		
		r3 = r1 - r2 * q3;
		std::cout << r3 << '\n';

		std::cout << s3 << ' ' << t3 << ' ' << r3 << ' ' << q3 <<'\n';

		if (r3 == 0) return std::make_pair(s2, t2);



		//update table
		s1 = s2;
		t1 = t2;
		r1 = r2;
		q1 = q2;


		s2 = s3;
		t2 = t3;
		r2 = r3;
		q2 = q3;
	}
}