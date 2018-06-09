#pragma once
#include "stdafx.h"
#include <iostream>
#include "Journal.h"
#include "PersistenceManager.h"

class examples
{
public:

	// Relevant classes are in SingleResponsibility folder
	static void single_responsibility_run()
	{
		journal j("My Diary");
		j.add("Today is a shitty day");
		j.add("I watched Roland Garros today");

		std::cout << j;

		// SOLID principles: "S"ingle responsibility: Responsbility of saving a journal object to a file is removed from
		// journal class to persistence_manager class.
		persistence_manager::save(j, "journal_file.txt");
	}
};

