#pragma once
#include <memory>
#include "Contact.h"

using namespace std;

class EmployeeFactory
{
	static unique_ptr<Contact> new_employee_from_prototype(const string & name, const string & number, const Contact & prototype)
	{
		Contact result{ prototype };
		result.name_ = name;
		result.address_->number_ = number;
		return make_unique<Contact>(result);
	}
public:
	static unique_ptr<Contact> new_main_office_employee(const string & name, const string & number)
	{
		// This static prototype object is created once
		static Contact p_main{"", new Address{"Ankara", "Galyum", "0"} };
		// This prototype is passed as argument to private function and used to create new employees from it by changing the name and number
		return new_employee_from_prototype(name, number, p_main);
	}

	static unique_ptr<Contact> new_istanbul_office_employee(const string & name, const string & number)
	{
		static Contact p_ist{ "", new Address{"Ýstanbul", "Titanium", "0"} };
		return new_employee_from_prototype(name, number, p_ist);
	}
};