#include <iostream>
#include "dp1.h"

/*
��� ȣ��
Ʈ���� ǥ���ϸ� ���ذ� ����
�ð� ���⵵ : ��ü ����� ����
���� ���⵵ : Ʈ���� ����

Brute force
tc : 0(2^n)
sc : 0(n)
*/ 
int f(int n)
{
	if (n <= 1)
	{
		return 1;
	}

	f(n - 1);
	f(n - 1);

	return 0;
}

int main()
{
	////std::cout << Fibonacci(50) << std::endl;
	//std::map<int, int64_t> memo;

	//std::cout << Fibonacci_memo(50,memo) << std::endl;

	std::cout << FindWay(2, 3) << std::endl;
}