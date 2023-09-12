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

// optimize - 중복 계산 제거
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