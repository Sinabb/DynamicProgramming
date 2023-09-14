#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <memory>
// Dnamic Programming 개념
/*
 정수의 배열 numbers에서 숫자들을 조합하여 sum이라는 값을 만들어 낼 수 잇는지 확인하는 함수를 만들어보세요.
 제한사항
 - numbers는 양수의 집합니다.
 0<= numbers[i]
 - sum을 만들기 위해 동일한 원소를 여러번 사용해도 됩니다.
 
 ex)
 입력 : numbers = {2,3,5}, sum = 8
 출력 :true
 설명
 2+3+3 = 8 이므로 참입니다.
 이외에도 2+2+2+2 역시 8이라서 여러개의 경우의 수가 있을 수 있습니다.

 ex2)
  입력 : numbers = {8,6}, sum = 7
  출력 : false
*/ 

// brute force
// m : sum, n : numbers의 크기
// tc: 0(n^ m)
// sc: 0(m)

bool Combination(std::vector<int> numbers, int sum)
{
	for (auto& e : numbers)
	{
		for (auto& l : numbers)
		{
			if (numbers[e] + numbers[l] == sum)
			{
				return true;
			}
		}
	}
	return false;
}

// Brute Force
bool CanAccumulate(std::vector<int>& numbers, int sum)
{
	// base case
	if (sum == 0)
	{
		return true;
	}
	if (sum < 0)
	{
		return false;
	}

	// recursive
	for (auto e : numbers)
	{
		if (CanAccumulate(numbers, sum - e))
		{
			return true;
		}
	}
	return false;
}

// Memoization
bool CanAccumulate(const std::vector<int>& numbers, int sum, std::map<int, bool>& memo)
{
	if (memo.count(sum) == 1)
	{
		return memo[sum];
	}

	// base case
	if (sum == 0)
	{
		return true;
	}
	if (sum < 0)
	{
		return false;
	}

	// recursive
	for (auto e : numbers)
	{
		if (CanAccumulate(numbers, sum - e, memo))
		{
			memo[sum] = true;
			return true;
		}
	}
	memo[sum] = false;
	return false;
}

//-------------------------

//memoization
// Tc: 0
// Sc : 0

// brute force
using result = std::shared_ptr<std::vector<int>>;

result HowAccumulateb(const std::vector<int>& numbers, int sum, std::map<int, result>& memo)
{
	// base case
	if (sum == 0)
	{
		return std::make_shared<std::vector<int>>();
	}
	if (sum < 0)
	{
		return nullptr;
	}

	// recursive case
	for (const auto e : numbers)
	{
		auto r = HowAccumulateb(numbers, sum, memo);
		if (r != nullptr)
		{
			r->push_back(e);
			return r;
		}
	}
	return nullptr;
}

// Memoization

using result = std::shared_ptr<std::vector<int>>;

result HowAccumulatem(const std::vector<int>& numbers, int sum, std::map<int, result>& memo)
{
	if (memo.count(sum) == 1)
	{
		return memo[sum];
	}

	// base case
	if (sum == 0)
	{
		return std::make_shared<std::vector<int>>();
	}
	if (sum < 0)
	{
		return nullptr;
	}

	// recursive case
	for (const auto e : numbers)
	{
		auto r = HowAccumulatem(numbers, sum - e, memo);
		if (r != nullptr)
		{
			r->push_back(e);
			memo[sum] = r;
			return memo[sum];
		}
	}
	memo[sum] = nullptr;
	return memo[sum];
}
