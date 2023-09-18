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

result HowAccumulatem(const std::vector<int>& numbers, int sum, std::map<int, result>& memo)
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
		auto r = HowAccumulatem(numbers, sum, memo);
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

result HowAccumulate(const std::vector<int>& numbers, int sum, std::map<int, result>& memo)
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
		auto r = HowAccumulate(numbers, sum - e, memo);
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

// 최소의 크기 : m = sum, n = numbers의 크기
// Tc:  0(m* n)
// // std::copy 시간 고려 0(m^2 * n)
// Sc : 0(m^2)
result OptimizeAccumualte(const std::vector<int>& numbers, int sum, std::map<int, result>& memo)
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

	if (sum<0)
	{
		return nullptr;
	}

	// recursive case
	std::shared_ptr < std::vector<int>> optimized = nullptr; 
	for (const auto e :numbers)
	{
		auto r = OptimizeAccumualte(numbers, sum - e, memo);
		if (r != nullptr)
		{
			std::shared_ptr<std::vector<int>> v = std::make_shared<std::vector<int>>();
			v->resize(r->size());
			std::copy(r->begin(), r->end(), v->begin());
			r->push_back(e);
			if (optimized == nullptr|| v->size() < optimized->size())
			{
				optimized = v;
			}
		}
	}
	memo[sum] = optimized;
	return memo[sum];
}


// Tc:  0(n^m * m)
// Sc : 0(m)
bool CanGenerate(std::vector<std::string>& strings, std::string target)
{

	//base case
	if (target == "")
	{
		return true;
	}
	
	//recursive
	for (auto e : strings)
	{
		if (target.find(e) == 0)
		{
			auto subStr = target.substr(e.size());
			if (CanGenerate(strings, subStr))
			{
				return true;
			}
		}
	}
	return false;
}

// Tc:  0(n^m * m)
// Sc : 0(m^2)

bool CanGenerate(const std::vector<std::string>& strings, std::string target,
	std::map<std::string, bool>& memo)

{

	if (memo.count(target) == 1)
	{
		return memo[target];
	}

	//base case
	if (target == "")
	{
		return true;
	}


	//recursive
	for (auto e : strings)
	{
		if (target.find(e) == 0)
		{
			auto subStr = target.substr(e.size());
			if (CanGenerate(strings, subStr))
			{
				return true;
			}
		}
	}
	memo[target] = false;
	return memo[target];
}

//combination -brute force
// Tc:  0(n^m * m)
// Sc : 0(m^2)
int HowManyGenerate(const std::vector<std::string>& strings, std::string target)
{
	//base case
	if (target == "")
	{
		return 1;
	}

	int count{};
	for (auto e : strings)
	{
		if (target.find(e) == 0)
		{
			count += HowManyGenerate(strings, target.substr(e.size()));
		}
	}

	return count;
}

//combination - memoization
// Tc:  0(n^m * m)
// Sc : 0(m^2)
int HowManyGenerate(const std::vector<std::string>& strings, std::string target,
	std::map<std::string, int>& memo)
{
	if (memo.count(target) == 1)
	{
		return memo[target];
	}
	//base case
	if (target == "")
	{
		return 1;
	}

	int count{};
	for (auto e : strings)
	{
		if (target.find(e) == 0)
		{
			count += HowManyGenerate(strings, target.substr(e.size()));
		}
	}
	memo[target] = count;
	return memo[target];
}