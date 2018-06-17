#include "stdafx.h"
#define _USE_MATH_DEFINES // for C++ 
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

#include <cmath>  
#include "Point.h"
#include "HotDrink.h"
#include "DrinkFactoryMap.h"
#include "Contact.h"

void examples::single_responsibility_run()
{
	cout << "\n\n" << "SINGLE RESPONSIBILITY" << "___________________________" << endl;
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
	cout << "\n\n" << "OPEN CLOSED PRINCIPLE" << "___________________________" << endl;
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
	cout << "\n\n" << "BUILDER PATTERN" << "___________________________" << endl;
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

void examples::factory_method_run()
{
	cout << "\n\n" << "FACTORY METHOD" << "___________________________" << endl;
	//Point p0{ 5, 5 };	// ERROR: private constructor. Has to be constructed through the static factory method of the class itself like below
	//Point p = Point::NewPolar(5.0f, M_PI_4);  // Use PointFactory instead of factory method.
	//Point p = PointFactory::NewPolar(5.0f, M_PI_4);  // InnerFactory: PointFactory is defined inside Point class.
	Point p = Point::PointFactory::NewCartesian(10.5f, 25.4f);
	cout << p;
}

void examples::abstract_factory_run()
{
	cout << "\n\n" << "ABSTRACT FACTORY METHOD" << "___________________________" << endl;

	// 1- OK! Creating an object directly on stack
	Tea t;
	t.prepare();
	// 2- BAD! Creating an object on heap, drawback is you have to delete later (manual memory management)
	Tea *tp = new Tea();
	tp->prepare();
	delete tp;
	// 3- WRONG! Creating an object on stack but storing it in a unique ptr (ERROR will result in program crash)
	//Coffee c88;
	//unique_ptr<Coffee> uc(&c88);	// ERROR: Program crashes trying to delete a local object.
	//uc->prepare();
	// 4- BEST PRACTICE! Creating an object on heap and storing it in a unique ptr (CORRECT, no manual memory management required)
	unique_ptr<Coffee> uc2(new Coffee());
	uc2->prepare();
	unique_ptr<Coffee> uc3 = make_unique<Coffee>();
	uc3->prepare();
	// 5- Using Factory class to create a coffee object
	CoffeFactory cf;
	unique_ptr<HotDrink> uc4 = cf.make();  // Create a hot drink using factory's make method, we can do this because we have a HotDrink base class.
	uc4->prepare();
	TeaFactory tf;
	auto ut = tf.make();
	ut->prepare();
	// 6- In method 5 you have to create each distinct factory (tea or coffee) separately, instead we use a mapper class which has TeaFactory and CoffeeFactory created in a map
	// Here polymorphism is in effect since the factory_map is map<string, unique_ptr<HotDrinkFactory>>, meaning it is mapping to the base class of both TeaFactory and CoffeeFactory
	DrinkFactoryMap dmap;
	dmap.make_drink("Tea");
	// OR simply call it fluently
	dmap.make_drink("Coffee");

	// 7- Using Functional Factory
	DrinkFactoryFunctionalMap dfmap;
	dfmap.make_drink("Tea");
}

void examples::prototype_run()
{
	// Method 1: Creating Contact objects with constructor is time consuming
	Contact Zahit{ "Zahit Ozcan", Address{"Ankara", "Urankent", "52"} };
	Contact Betul{ "Betul Ozcan", Address{"Ankara", "Urankent", "44"} };
	cout << Zahit << endl << Betul << endl;

	// Method 2: Create one Contact object as prototype and then create copies from it.
	Contact Erdem = Zahit;  // Shallow copy but doesn't pose any problems because there are no pointers inside Contact class
	Erdem.name_ = "Erdem Kaymaz";

	cout << Erdem << endl;

	// Method 3: (Assuming no copy constructor exists) This copying is shallow copy so it won't work if Contact has pointers
	Contact_With_Pointer Ersin{ "Ersin", new Address{"Ankara", "Galyum", "42"} };
	Contact_With_Pointer Hakan = Ersin;   // If copy constructor is implemented properly this will work

	Hakan.name_ = "Hakan";   // Shallow copy
	Hakan.address_->number_ = "88";	// ERROR: Modifies Ersin's Address number as well
	Hakan.address_->city_ = "Gazipasa";

	cout << Ersin << endl << Hakan << endl;
}
