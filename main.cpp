#include <iostream>
#include "dp1.h"

/*
재귀 호출
트리로 표현하면 이해가 쉬움
시간 복잡도 : 전체 노드의 갯수
공간 복잡도 : 트리의 높이

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