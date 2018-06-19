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
#include "EmployeeFactory.h"

#include <sstream>
#include "Singleton.h"
#include "Person.h"
#include "Shape.h"
#include "GraphicObject.h"
#include "Neuron.h"

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
	cout << "\n\n" << "PROTOTYPE PATTERN" << "___________________________" << endl;
	// Method 1: Creating Contact objects with constructor is time consuming
	Contact_No_Pointers Zahit{ "Zahit Ozcan", Address{"Ankara", "Urankent", "52"} };
	Contact_No_Pointers Betul{ "Betul Ozcan", Address{"Ankara", "Urankent", "44"} };
	cout << Zahit << endl << Betul << endl;

	// Method 2: Create one Contact object as prototype and then create copies from it.
	Contact_No_Pointers Erdem = Zahit;  // Shallow copy but doesn't pose any problems because there are no pointers inside Contact class
	Erdem.name_ = "Erdem Kaymaz";

	cout << Erdem << endl;

	// Method 3: (Assuming no copy constructor exists) This copying is shallow copy so it won't work if Contact has pointers
	Contact Ersin{ "Ersin", new Address{"Ankara", "Galyum", "42"} };
	Contact Hakan = Ersin;   // Shallow copy. If copy constructor is implemented properly this will work

	Hakan.name_ = "Hakan";
	Hakan.address_->number_ = "88";	// ERROR: Modifies Ersin's Address number as well
	Hakan.address_->city_ = "Gazipasa";

	cout << Ersin << endl << Hakan << endl;


	// Method 4: Employee factory which holds a static Contact prototype and uses this prototype to create copies
	unique_ptr<Contact> Employee_1 = EmployeeFactory::new_main_office_employee("Muhammet Zahit Ozcan", "5152");
	cout << *Employee_1 << endl;
	auto Employee_2 = EmployeeFactory::new_istanbul_office_employee("Erdem Kaymaz", "6521");
	cout << *Employee_2 << endl;

	// Method 5: Serialize/Deserialize using boost archive
	// We implement a lambda which serializes and then deserializes the object and returns it
	// This is another way of deep copying. Instead of writing copy constructor code for each class in the class graph
	// you write serialization code (using boost) for each class
	auto clone = [](const Contact & c){
		ostringstream oss;
		archive::text_oarchive oa(oss);
		oa << c;
		string s = oss.str();
		cout << s << endl;

		istringstream iss(s);
		archive::text_iarchive ia(iss);
		Contact result;
		ia >> result;
		return result;
	};

	auto Employee_3 = EmployeeFactory::new_istanbul_office_employee("John Doe", "4124");
	Contact x = clone(*Employee_3);  // Employee_3 is serialized and then deserialized back to x
	x.name_ = "Jane Smith";
	cout << "Serialized obj: " << *Employee_3 << endl;
	cout << "Deserialized obj: " << x << endl;
}

void examples::singleton_run()
{
	cout << "\n\n" << "SINGLETON PATTERN" << "___________________________" << endl;
	cout << "Tokyo population: " << Singleton::GetInstance().get_population("Tokyo") << endl;
}

void examples::pimpl_run()
{
	cout << "\n\n" << "PIMPL IDIOM" << "___________________________" << endl;
	Person p("Zahit");
	p.greet();
}

void examples::bridge_run()
{
	cout << "\n\n" << "BRIDGE PATTERN" << "___________________________" << endl;
	// You can create Circle objects and pass different Renderers to it. This is bridge'ing different components
	// into Circle object.
	RasterRenderer rr;
	Circle c{ rr, 4, 4, 10 };
	c.draw();
	c.resize(2);
	c.draw();

	VectorRenderer vr;
	Circle c2{ vr, 2, 2, 20 };
	c2.draw();
	c2.resize(0.5f);
	c2.draw();
}

void examples::composite_run()
{
	cout << "\n\n" << "COMPOSITE PATTERN" << "___________________________" << endl;
	CircleGraphic cg;
	SquareGraphic sg;
	Group main_group{"main group"};
	Group sub_group{ "sub_group" };


	// Individual objects i.e sg and collection of objects i.e. main_group all behave the same way (they have the same draw() API)
	main_group.add(&cg);
	sub_group.add(&sg);
	main_group.add(&sub_group); // You can add a group to another group since Group inherits from GraphicObject as well.
	main_group.draw();



	// Neuron composite
	Neuron n1, n2, n3, n4;

	// Connecting neuron to neuron
	n1.connect_to(n2);
	n2.connect_to(n4);
	n3.connect_to(n2);

	// Neuron layer composite
	NeuronLayer neuron_layer_1{ 5 }, neuron_layer_2{ 3 };

	// With one connect_to template function we can make all 4 possible connections
	// 1- NeuronLayer -> NeuronLayer, 
	neuron_layer_1.connect_to(neuron_layer_2);
	// 2- NeuronLayer -> Neuron,
	neuron_layer_1.connect_to(n2);
	// 3- Neuron -> NeuronLayer, 
	n1.connect_to(neuron_layer_1);
	// 4- Neuron -> Neuron
	n3.connect_to(n1);

	cout << neuron_layer_1;


}
