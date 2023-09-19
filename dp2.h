#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <list>
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

std::ostream& operator<< (std::ostream& os, std::vector<int>* v)
{
	if (v == nullptr)
	{
		std::cout << "nullptr";
	}
	else
	{
		std::cout << "{";
		for (int i = 0; i < v->size(); i++)
		{
			std::cout << (*v)[i] << ", ";

			if (i < v->size() - 1)
			{
				std::cout << ", ";
			}
		}
		std::cout << "}";
		return os;
	}
}


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

// �ּ��� ũ�� : m = sum, n = numbers�� ũ��
// Tc:  0(m* n)
// // std::copy �ð� ��� 0(m^2 * n)
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


// Decision Problem - brute force
// TC: O( m^2 * n )
// SC:O( m ^ 2),
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

// Memoization
// TC: O( m^2 * n )
// SC:O( m ^ 2)

bool CanGenerate(const std::vector<std::string>& strings, std::string target
	, std::map<std::string, bool>& memo)
{
	if (memo.count(target) == 1)
	{
		return memo[target];
	}

	// base case
	if (target == "")
	{
		return true;
	}

	// recursive
	for (auto e : strings)
	{
		if (target.find(e) == 0)
		{
			if (CanGenerate(strings, target.substr(e.size()), memo))
			{
				memo[target] = true;
				return memo[target];
			}
		}
	}

	memo[target] = false;
	return memo[target];
}
// Combination - brute force
// TC : O(n^m * m)
// SC : O(m^2)
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

using string2d = std::list<std::list<std::string>>;

string2d AllCombination(const std::vector<std::string>& strings, std::string target)
{

	//base case
	if (target=="")
	{
		return string2d{ {} };
	}

	//recursive case
	string2d v;
	for (auto word : strings)
	{
		if (target.find(word) == 0)
		{
			auto r = AllCombination(strings, target.substr(word.size()));
			for (auto s : r)
			{
				s.push_front(word);
				v.push_front(s);
			}
		}
	}
	return v;
}

std::ostream& operator<<(std::ostream& os, string2d& v)
{
	std::cout << "{" << std::endl;
	int i{}, j{};

	for (auto e1 :v)
	{
		std::cout << "    {";
		for (auto e2 : e1)
		{
			std::cout << e2;

			if (j<e1.size()-1)
			{
				std::cout << ",";
			}
			j++;
		}
		std::cout << "}";
		if (j < v.size() - 1)
		{
			std::cout << ",";
		}
		std::cout<<std::endl;
		i++;
	}
	std::cout << "}" << std::endl;

	return os;
}