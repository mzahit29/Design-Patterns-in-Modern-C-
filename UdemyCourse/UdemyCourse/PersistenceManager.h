#pragma once
#include <fstream>
#include "Journal.h"

class persistence_manager
{
public:
	static void save(const journal & j, const std::string & filename)
	{
		std::ofstream ofs(filename);

		if(ofs)
		{
			for (auto &x : j.get_entries())
			{
				ofs << x << std::endl;
			}

			ofs.close();
		} else
		{
			throw std::exception("[ERROR]: File saving failed.");
		}
	}
};
