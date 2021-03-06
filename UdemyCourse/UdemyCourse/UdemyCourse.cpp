// UdemyCourse.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Examples.h"


using std::cout;
using std::endl;


int main()
{
	cout << "main() begin" << "\n\n" << endl;

	//examples::single_responsibility_run();
	//examples::open_closed_run();
	//examples::builder_run();
	//examples::factory_method_run();
	//examples::abstract_factory_run();
	//examples::prototype_run();
	//examples::singleton_run();
	//examples::pimpl_run();
	//examples::bridge_run();
	//examples::composite_run();
	//examples::decorator_run();
	//examples::flyweight_run();
	//examples::proxy_run();
	//examples::chain_of_responsbility_run();
	//examples::command_run();
	//examples::interpreter_run();
	//examples::mediator_run();
	//examples::memento_run();
	//examples::observer_run();
	//examples::state_run();
	//examples::strategy_run();
	//examples::template_run();
	examples::visitor_run();

	cout << "\n\n" << "main() end" << endl;
	return 0;
}
