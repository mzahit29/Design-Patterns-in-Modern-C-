#pragma once
#include <map>
#include <fstream>
#include <string>
#include <iostream>
#include <boost/lexical_cast.hpp>

using namespace std;

class Singleton
{
	// Making constructor private to block instance creation manually
	Singleton()
	{
		cout << "Singleton()" << endl;
		std::ifstream ifs("Capitals.txt");
		std::string s1, s2;
		while(std::getline(ifs, s1))
		{
			std::getline(ifs, s2);
			int population = lexical_cast<int>(s2);
			populations[s1] = population;
		}
	}

	map<string, int> populations;
public:
	// Deleting copy constructor and copy assignment operator to block instance creation via copying.
	Singleton(const Singleton &) = delete;
	Singleton & operator=(const Singleton &) = delete;

	static Singleton & GetInstance()
	{
		// This is the only instance created, it is static so only one instance exists.
		// It is also thread safe (C++11)
		static Singleton sng;
		return sng;
	}

	int get_population(const string & city)
	{
		return populations[city];
	}
};
