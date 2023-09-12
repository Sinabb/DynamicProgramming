#pragma once

#include <iostream>
#include <map>
//time complexity:
//space complexity:

int64_t Fibonacci(int n)
{
	//base case
	if (n <= 2)
	{
		return 1;
	}
	// recursive
	return Fibonacci(n - 1) + Fibonacci(n - 2);
}

// optimize - �ߺ� ��� ����
// ������ Ǯ�� ����� ������ ������ ����
// tc : 0(n)
// sc : 0(n)
int64_t Fibonacci_memo(int n, std::map<int, int64_t>& memo)
{
	if (memo.count(n) ==1)
	{
		return memo[n];
	}
	//base case
	if (n <= 2)
	{
		return 1;
	}
	// recursive
	memo[n] = Fibonacci_memo(n - 1,memo) + Fibonacci_memo(n - 2, memo);
	return memo[n];
}
// mxn ũ���� �簢�� ������ �־����� �� �»� �ܿ��� ����Ͽ� �� �ϴ����� �̵��ϴ� ����� ���� ���ϼ���
// ��,
// �ð� ���⵵: 0(2^(m+n))
// ���� ���⵵: 0(m+n)
int FindWay(int m, int n)
{
	//base case
	if (m == 1 && n==1)
	{
		return  1;
	}

	if (m == 0 || n == 0)
	{
		return 0;
	}
	//recursive case
	return FindWay(m - 1, n) + FindWay(m, n-1);
}