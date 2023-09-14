#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <memory>
// Dnamic Programming ����
/*
 ������ �迭 numbers���� ���ڵ��� �����Ͽ� sum�̶�� ���� ����� �� �� �մ��� Ȯ���ϴ� �Լ��� ��������.
 ���ѻ���
 - numbers�� ����� ���մϴ�.
 0<= numbers[i]
 - sum�� ����� ���� ������ ���Ҹ� ������ ����ص� �˴ϴ�.
 
 ex)
 �Է� : numbers = {2,3,5}, sum = 8
 ��� :true
 ����
 2+3+3 = 8 �̹Ƿ� ���Դϴ�.
 �̿ܿ��� 2+2+2+2 ���� 8�̶� �������� ����� ���� ���� �� �ֽ��ϴ�.

 ex2)
  �Է� : numbers = {8,6}, sum = 7
  ��� : false
*/ 

// brute force
// m : sum, n : numbers�� ũ��
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
