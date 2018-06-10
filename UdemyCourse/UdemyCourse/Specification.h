#pragma once
#include <vector>
#include "Product.h"

// Specification is an interface which can be inherited by specifying any type
template <typename T>
class Specification
{
public:
	virtual bool is_satisfied(T *) = 0;
};

// We inherit the Specification interface with product as type T
class ColorSpecification : public Specification<product>
{
	color c_;
public:
	explicit ColorSpecification(color c) : c_(c) {}
	bool is_satisfied(product* pr) override
	{
		return pr->color_ == c_;
	}
};

class SizeSpecification : public Specification<product>
{
	size size_;
public:
	explicit SizeSpecification(size s) : size_(s) {}
	bool is_satisfied(product* pr) override
	{
		return pr->size_ == size_;
	}
};

template <typename T>
class AndSpecification : public Specification<T>
{
	Specification<T> & first_spec_;
	Specification<T> & second_spec_;
public:
	AndSpecification(Specification<T> &first, Specification<T> &second) : first_spec_(first), second_spec_(second) {}

	bool is_satisfied(T *obj) override
	{
		return first_spec_.is_satisfied(obj) && second_spec_.is_satisfied(obj);
	}
};