// UdemyCourse.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Examples.h"


using std::cout;
using std::endl;


int main()
{
	cout << "main() begin" << endl;

	examples::single_responsibility_run();
	examples::open_closed_run();
	examples::builder_run();
	examples::factory_method_run();
	examples::abstract_factory_run();

	cout << "main() end" << endl;
	return 0;
}

