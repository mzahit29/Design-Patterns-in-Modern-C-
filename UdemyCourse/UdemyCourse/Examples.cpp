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
#include "Creature.h"
#include "CompositeExercise.h"
#include "Shape_2.h"
#include "Shape_Static_Decorator.h"
#include "Functional_Decorator.h"
#include "User.h"
#include "PropertyProxy.h"
#include "VirtualProxy.h"
#include "ChainOfResponsbility.h"
#include "BrokerChain.h"
#include "BankAccount.h"
#include "Interpreter.h"
#include "Personnn.h"
#include "ChatRoom.h"
#include "EventBroker.h"
#include "Memento.h"
#include "PersonObs.h"

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




	// Array Backed Properties
	// Using array backed properties it is possible to write much tidier code for sum, avg and max
	Creature orc;
	orc.set_agility(10);
	orc.set_strength(20);
	orc.set_intel(5);

	cout << "Orc average stat: " << orc.avg()
		<< "\nOrc max stat: " << orc.max()
		<< "\nOrc sum of stats: " << orc.sum() << endl;


	// Coding Exercise
	SingleValue sv{ 1 };
	ManyValues mv;
	mv.add(4);
	mv.add(3);
	cout << "Sum: " << sum({ &sv, &mv }) << endl;

}

void examples::decorator_run()
{
	cout << "\n\n" << "DECORATOR PATTERN" << "___________________________" << endl;
	cout << "\n\n" << "DYNAMIC DECORATOR" << "___________________________" << endl;

	using namespace Decorator;
	Decorator::Circle circle{ 5 };
	cout << circle.str() << endl;

	ColoredShape red_circle{ circle, "red" };
	// What if you want to resize the decorated circle instance
	// You can not call shape_.resize() since it is not part of base class Shape. Also you can not make resize() virtual
	// because maybe not all Shape's will be resizeable.
	// This is only possible with typeid() operator or dynamic_cast since we have a reference to base class Shape. 
	// This is the downside of decorator pattern
	if (typeid(red_circle.shape_) == typeid(Decorator::Circle))
	{
		static_cast<Decorator::Circle &>(red_circle.shape_).resize(4.f);
	}
	cout << red_circle.str() << endl;

	//OR
	try
	{
		dynamic_cast<Decorator::Circle &>(red_circle.shape_).resize(0.5f);
	} 
	catch (std::bad_cast & e) {
		cout << "[ERROR: " << e.what() << "]" << endl;
	}
	cout << red_circle.str() << endl;

	Decorator::Square square{ 3 };
	ColoredShape red_square{ square, "green" };
	try
	{
		// Bad cast will throw resize not possible shape_ is not a Circle it is a Square
		dynamic_cast<Decorator::Circle &>(red_square.shape_).resize(5.f);
	}
	catch (std::bad_cast & e) {
		cout << "[ERROR: " << e.what() << "]" << endl;
	}
	cout << red_square.str() << endl;


	// We can decorate an already decorated obj like a colored shape
	TransparentShape transparent_circle{ red_circle, 55 };
	cout << transparent_circle.str() << endl;




	// Static decorator
	cout << "\n\n" << "STATIC DECORATOR" << "___________________________" << endl;
	ColoredShape2<Decorator::Circle> cir{ "red", 5 };
	// Now we can call resize on the circle since we have inherited from Circle using template
	cir.resize(2.f);
	cout << cir.str() << endl;

	TransparentShape2<ColoredShape2<Decorator::Circle>> transparent_circle2{ 42.f, "green", 4 };
	transparent_circle2.resize(4);  // You can again resize transparent_circle2 because it is a Circle, it inherited from Circle
	cout << transparent_circle2.str() << endl;




	// Functional decorator
	cout << "\n\n" << "FUNCTIONAL DECORATOR" << "___________________________" << endl;
	// We are giving the function<void()> parameter as a lamdba function that takes no parameters and returns void
	Decorator::Logger logger{ []() {cout << "Hello from Logger function object" << endl; }, "Hello function" };
	logger();

	// The following won't work because you haven't provided the template argument
	// Logger2{ []() {cout << "Hello from Logger2 function object" << endl;}, "Hello Func" }();
	// Now we provide the template argument which is function<void()>
	Logger2<std::function<void()>>{ []() {cout << "Hello from Logger2 function object" << endl; }, "Hello Func" }(); // Note that we invoke operator() on this r-value.

	// Instead of having to provide the template argument we could write a function which itself provides the template argument inside
	// its body
	auto log = make_logger2([]() {cout << "Hello from Logger2 function object created via make_logger" << endl; }, "Hello func");
	log();





	// Logger that takes a function which takes parameters and returns a value
	Logger3<double(double, double)> logger3{ add, "add" };
	logger3(3.0, 5.0);

	// Or you could use the make_logger3 to create the Logger3 instance without having to specify the template arguments
	auto logger3_ = make_logger3(add, "add");
	logger3(4, 8);

}

void examples::flyweight_run()
{
	cout << "\n\n" << "FLYWEIGHT PATTERN" << "___________________________" << endl;
	User u{ "Zahit", "Ozcan" };
	User u2{ "Zahit", "Ozkan" };

	cout << u << endl;
	cout << u2 << endl;

	User2 u3{ "Betül", "Ozcan" };
	User2 u4{ "Zahit", "Ozcan" };

	cout << u3.first_name_ << " " << u3.last_name_ << endl;
	cout << u4.first_name_ << " " << u4.last_name_ << endl;

	cout << boolalpha;
	cout << (u3.first_name_.get() == u4.first_name_.get()) << endl;
	// u3 and u4 last_name_ refer to the same flyweight object
	cout << (u3.last_name_.get() == u4.last_name_.get()) << endl;
}

void examples::proxy_run()
{
	cout << "\n\n" << "PROXY PATTERN" << "___________________________" << endl;
	cout << "\n\n" << "PROPERTY PROXY" << "___________________________" << endl;
	Proxy::Creature c{ 10, 20 };
	c.strength_ = 15;	// Invokes Property class operator==
	cout << c << endl;


	cout << "\n\n" << "VIRTUAL PROXY" << "___________________________" << endl;
	Bitmap pikachu("pikachu_image.png");
	pikachu.draw();

	// VirtualBitmap will only store the filename on construction. Inside draw() method it will create a Bitmap object on heap
	// and call its draw. Therefore we will have accomplished lazy loading
	VirtualBitmap pikachu2("pikachu_image.png");
	Decorator::Logger logged_draw{ [&pikachu2]() { pikachu2.draw(); }, "draw()" }; // Using function decorator for fun
	logged_draw();

}

void examples::chain_of_responsbility_run()
{
	cout << "\n\n" << "CHAIN OF RESPONSIBILITY PATTERN" << "___________________________" << endl;
	cout << "\n\n" << "POINTER CHAIN" << "___________________________" << endl;
	using namespace ChainOfResp;
	ChainOfResp::Creature elf{ 8, 4, 40 };

	// Create the creature modifiers
	CreatureModifier root{ elf };
	DoubleAttackModifier dbl{ elf };
	RageModifier rage{ elf };
	NegateSpells negate{ elf };

	// Link the creature modifiers, thereby creating a chain
	root.add_modifier(&dbl);
	root.add_modifier(&rage);
	// Start the chain reaction
	root.handle();
	cout << elf << endl;
	
	root.add_modifier_beg(&negate);
	DoubleAttackModifier dbl2{ elf };
	root.add_modifier(&dbl2);  // This double attack modifier will not be applied because negate modifier doesn't propagate the handle call
	root.handle();
	cout << elf << endl;


	



	cout << "\n\n" << "BROKER CHAIN" << "___________________________" << endl;
	BrokerChain::Game magic_game;
	BrokerChain::Creature red_goblin{ magic_game, 2, 2, "red_goblin" };
	cout << red_goblin << endl;

	BrokerChain::DoubleAttackModifier dam{ magic_game, red_goblin };
	cout << red_goblin << endl;

	// Now create any other creature with the name "red_goblin", tricking the queries_
	BrokerChain::Creature green_goblin{ magic_game, 3, 3, "red_goblin" }; // Note cheating as a red_goblin
	cout << green_goblin << endl;

	{
		// All the modifiers in the list are applied in the order they are added. Like in the pointer chain example
		// Therefore the plus 10 life is first applied then plus 10 life is applied again then black_hole is applied
		// making the resulting cumulative life 0 for all creatures that are assigned to magic_game that ask what their life
		// is using magic_game.queries_(Query{name_, Query::Argument::life, life_}).
		BrokerChain::AllCreaturesLifeBonusPlus10 plus_10_life{ magic_game };
		BrokerChain::AllCreaturesLifeBonusPlus10 plus_10_life_again{ magic_game };
		BrokerChain::AllCreaturesDie black_hole{ magic_game };

		cout << "Goblins are dead in this scope\n" << green_goblin << endl;
	}

	// When the above scope is finished, the modifiers are destructed. Which means they are disconnected from game.queries_
	// So they are no longer in effect.
	cout << "Goblins are back alive\n" << green_goblin << endl;



}

void examples::command_run()
{
	cout << "\n\n" << "COMMAND PATTERN" << "___________________________" << endl;
	BankAccount ba{ 1000.f, -200.f };
	vector<BankAccountCommand> commands {
		BankAccountCommand{ba, BankAccountCommand::Action::deposit, 200},
		BankAccountCommand{ba, BankAccountCommand::Action::withdraw, 800}
	};

	cout << "Calling the operations____________" << endl;
	for (Command& command : commands)
	{
		command.call();
	}

	// Undoing the operations in reverse order
	cout << "\n\n" << "UNDO OPERATIONS" << "___________________________" << endl;
	for (auto it = commands.rbegin(); it != commands.rend(); ++it)
	{
		it->undo();
	}

	BankAccount ba2{ 1000.f, -200.f };
	cout << ba2 << endl;

	unique_ptr<Command> up{ new BankAccountCommand{ ba2, BankAccountCommand::Action::deposit, 200 } };
	up->call();
	cout << ba2 << endl;

	std::shared_ptr<Command> sp(new BankAccountCommand{ ba2, BankAccountCommand::Action::withdraw, 600 });
	sp->call();
	cout << ba2 << endl;



	// COMPOSITE COMMAND (MACRO)
	cout << "\n\n" << "COMPOSITE COMMAND (MACRO)" << "___________________________" << endl;
	cout << "CompositeBankAccountCommand_______" << endl;
	CompositeBankAccountCommand composite_bank_account_command{
		BankAccountCommand{ba, BankAccountCommand::Action::deposit, 200 },
		BankAccountCommand{ ba, BankAccountCommand::Action::withdraw, 1200 }
	};
	composite_bank_account_command.call();
	cout << ba << endl;
	composite_bank_account_command.undo();
	cout << ba << endl;

	cout << "\nMoneyTransferCommand_______" << endl;
	BankAccount ZahitAcc{ 1000, -200 }, BetulAcc{ 5000, -500 };
	MoneyTransferCommand mtrns{ ZahitAcc, BetulAcc, 5000 }; // This wont work as expected because ZahitAcc doesn't have enough balance to withdraw
	mtrns.call();
	cout << ZahitAcc << endl << BetulAcc << endl;
	mtrns.undo();
	cout << ZahitAcc << endl << BetulAcc << endl;
}

void examples::interpreter_run()
{
	string s = "(8+4)-(9-1)";
	vector<Token> token_vector = lex(s);
	for(auto & t : token_vector)
	{
		cout << t << " ";
	}
}

void examples::mediator_run()
{
	cout << "\n\n" << "MEDIATOR PATTERN" << "___________________________" << endl;
	cout << "\n\n" << "CHATROOM" << "___________________________" << endl;
	vector<unique_ptr<person>> people;
	people.push_back(unique_ptr<person>(new person("Zahit")));
	people.push_back(unique_ptr<person>(new person("Betül")));
	people.push_back(unique_ptr<person>(new person("Erdem")));

	chat_room room;
	for (auto & person : people)
	{
		room.enter(*person);
	}
	people[0]->say("Hello, everybody how is it going?");

	for (auto & person : people)
	{
		cout << *person;
	}

	people[1]->pm("Zahit", "I love you");
	for (auto & person : people)
	{
		cout << *person;
	}



	cout << "\n\n" << "GAME MEDIATOR" << "___________________________" << endl;
	Mediator::Game football_game;
	Player john{ "john", football_game };
	Coach coach{ football_game };

	john.score();


}

void examples::memento_run()
{
	cout << "\n\n" << "MEMENTO PATTERN" << "___________________________" << endl;

	cout << "\n\n" << "PRIMITIVE MEMENTO" << "___________________________" << endl;
	using MementoNS::BankAccount;
	using MementoNS::Memento;
	BankAccount ba{ 100 };
	Memento m_1 = ba.deposit(44);
	cout << ba;
	auto m_2 = ba.deposit(16);
	cout << ba;

	ba.restore(m_1);
	cout << "Bank account restored to m1: " << ba;

	ba.restore(m_2);
	cout << "Bank account restored to m2: " << ba;



	cout << "\n\n" << "MEMENTO VECTOR INSIDE BANKACCOUNT" << "___________________________" << endl;
	using MementoNS::BankAccount2;

	BankAccount2 ba2{ 50 };
	auto m1 = ba2.deposit(40);
	cout << "Deposit: " << ba2;
	auto m2 = ba2.deposit(60);
	cout << "Deposit: " << ba2;
	auto m3 = ba2.redo(); // This should do nothing we are already at the end
	cout << "Redo: " << ba2;
	auto m4 = ba2.undo();
	cout << "Undo: " << ba2;
	auto m5 = ba2.redo();
	cout << "Redo: " << ba2;
	auto m6 = ba2.deposit(29);
	cout << "Deposit: " << ba2;

	ba2.restore(m3);  // This will do nothing since m3 an empty shared_ptr<Memento> and 
					// we have an if(m) check in restore, which returns false for empty shared_ptr
	ba2.restore(m1);
	cout << "Restore: " << ba2;
	ba2.restore(m6);
	cout << "Restore: " << ba2;
}

void examples::observer_run()
{
	cout << "\n\n" << "OBSERVER PATTERN" << "___________________________" << endl;
	using ObserverNS::Person;
	using ObserverNS::PersonObserver;


	Person p{ 6 };
	PersonObserver po;
	p.subscribe(po);
	p.set_age(7);
	p.set_age(11);
	p.unsubscribe(po);
	p.set_age(22);  // this change won't be handled by po because it has unsubscribed from Person and therefore it is not notified.


}
