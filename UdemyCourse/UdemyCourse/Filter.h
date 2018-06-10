#pragma once
#include <vector>
#include "Specification.h"

// Filter is an interface which can be inherited by specifying any type
template <typename T>
class Filter
{
public:
	virtual std::vector<T *> filter(std::vector<T *> items, Specification<T> & spec) = 0;
};

// We inherit the Filter interface with product type as T
class ProductFilter : Filter<product>
{
public:
	virtual std::vector<product *> filter(std::vector<product *> items, Specification<product> & spec) override
	{
		std::vector<product *> result;
		for (auto &item : items)
		{
			if (spec.is_satisfied(item))
			{
				result.push_back(item);
			}
		}

		return result;
	}
};

