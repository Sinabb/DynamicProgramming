#pragma once

#include <iostream>
#include <map>
#include <string>
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
// 문제를 풀고 결과를 저장한 다음에 재사용
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
// mxn 크기의 사각형 영역이 주어졌을 때 좌상 단에서 출발하여 우 하단으로 이동하는 경우의 수를 구하세요
// 단,
// 시간 복잡도: 0(2^(m+n))
// 공간 복잡도: 0(m+n)
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

// tc : 0(n) / 0 (m* n)
// sc : 0(m+n)

int MovingPath(int m, int n)
{
	if (m == 1 && n == 1)
	{
		return 1;
	}
	if (m == 0 || n == 0)
	{
		return 0;
	}
	return MovingPath(m - 1, n) + MovingPath(m, n - 1);
}

int FindWay(int m, int n, std::map<std::string, int>& memo)
{
	std::string key = std::to_string(m) + "," + std::to_string(n);
	if (memo.count(key) == 1)
	{
		return memo[key];
	}

	std::string rkey = std::to_string(n) + "," + std::to_string(m);

	if (memo.count(rkey) == 1)
	{
		return memo[rkey];
	}

	// base case
	if (m == 1 && n == 1)
	{
		return 1;
	}
	if (m == 0 || n == 0)
	{
		return 0;
	}

	// recursive case
	memo[key] = FindWay(m - 1, n, memo) + FindWay(m, n - 1, memo);
	return memo[key];
}