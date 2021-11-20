#include <iostream>
#include "RSA.h"
#define 无 void
#define 整数 int
#define 小数 float
#define 双小数 double
#define 循环 for
#define 返回 return
#define 主程序 main
#define 使用 using
#define 名字空间 namespace
#define 打印 printf


使用 名字空间 std;

整数 主程序()
{
	/*
	auto p = RSA::EEA(42, 21);
	cout << p.first << ' ' << p.second << '\n';
	*/
	const std::string str = "teachers";
	std::vector<LL> temp = RSA::Serialize(str);
	//for (LL i : temp)
	{
	//	cout << i << " "; 
	}

	//cout << endl;

	//std::string dictionary = RSA::Deserialize(temp);
	//cout << dictionary; 

}


