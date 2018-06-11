#include "stdafx.h"
#include <iostream>
#include "Journal.h"
#include "PersistenceManager.h"

#include "Product.h"
#include "Specification.h"
#include "Filter.h"
#include "Examples.h"

#include "HtmlElement.h"
#include "HtmlBuilder.h"
#include "Tag.h"


void examples::single_responsibility_run()
{
	journal j("My Diary");
	j.add("Today is a shitty day");
	j.add("I watched Roland Garros today");

	std::cout << j;

	// SOLID principles: "S"ingle responsibility: Responsbility of saving a journal object to a file is removed from
	// journal class to persistence_manager class.
	persistence_manager::save(j, "journal_file.txt");
}

// Relevant classes are in Open-Closed folder
void examples::open_closed_run()
{
	// Most primitive way two separate functions that filter. They do the same thing and only the condition is different.
	//std::vector<Product &> result = filter_by_color(std::vector<product &> &pr_vector, color::blue);
	//std::vector<Product &> result = filter_by_size(std::vector<product &> &pr_vector, size::large);

	// Function overload, still code duplication
	//product_filter a(std::vector<product &> &pr_vector);
	//std::vector<Product &> result = a.filter(size::large);
	//std::vector<Product &> result = a.filter(color::red);


	//product_filter a;
	//std::vector<Product &> result = a.filter(std::vector<product &> &pr_vector, color::blue);

	// or
	//std::vector<Product &> result = product_filter::filter(std::vector<product &> &pr_vector, size::small);

	// another approach: only one filter function, which just applies each member to the predicate
	//product_filter pr{ &pr1, &pr2, &pr3 };
	//pr.filter(predicate & p);
	////pr.filter([](color c) { return c == color::red; });  // This won't work. It has to be a predicate that takes a product
	//pr.filter([](product & p) { return p.get_color() == color::blue; });

	//vector<product &> filter(bool (*pfn)(const product &pr))
	//{
	//	vector<product &> result;
	//	for (auto &x : pr_vector)
	//	{
	//		if (pfn(x))
	//		{
	//			result.push_back(x);
	//		}
	//	}
	//	return result;
	//}

	product pr1{ "Tshirt", color::red, size::small };
	product pr2("Nike Shorts", color::blue, size::large);
	product pr3("Football", color::blue, size::large);
	product pr4("Basketball", color::green, size::large);

	ProductFilter pfilter;
	ColorSpecification blue_color(color::blue);
	std::vector<product *> items{ &pr1, &pr2, &pr3, &pr4 };

	std::cout << "Blue items are: " << std::endl;
	for (auto &x : pfilter.filter(items, blue_color))
	{
		std::cout << *x;
	}

	SizeSpecification large_size(size::large);

	std::cout << "Large items are: " << std::endl;
	for (auto &x : pfilter.filter(items, large_size))
	{
		std::cout << *x;
	}


	std::cout << "Blue and Large items are: " << std::endl;
	AndSpecification<product> blue_and_large(blue_color, large_size);
	for (auto &x : pfilter.filter(items, blue_and_large))
	{
		std::cout << *x;
	}
}

void examples::builder_run()
{
	HtmlBuilder builder("ul", "");
	builder.add_child("li", "Modern C++").add_child("li", "Concurrency in C++");

	cout << builder.str();

	// static method create returns an HtmlBuilder instance.
	HtmlBuilder builder2 = HtmlElement::create("ul", "").add_child("li", "C98").add_child("li", "STL");

	cout << builder2.str();


	cout << P {
		IMG	{"http://gif.com"
		}
	};


}
