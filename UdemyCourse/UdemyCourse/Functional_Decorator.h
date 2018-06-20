#pragma once
#include <iostream>
#include <functional>
#include <string>
using namespace std;

namespace Decorator
{
	class Logger
	{
		function<void()> func_;
		string name_;
	public:
		Logger(const function<void()> &func, const string& name) : func_(func), name_(name) {}

		void operator()()
		{
			cout << "Entering " << name_ << endl;
			func_();
			cout << "Exiting " << name_ << endl;
		}

	};


	// We could also make a template logger class. But calling it like 
	// Logger2{[](){}, "Hello Func"}() is not possible because template type can not be inferred.
	template <typename Func>
	class Logger2
	{
		Func func_;
		string name_;
	public:
		Logger2(const Func &func, const string& name) : func_(func), name_(name) {}
		void operator()()
		{
			cout << "Entering " << name_ << endl;
			func_();
			cout << "Exiting " << name_ << endl;
		}
	};

	template <typename Func>
	auto make_logger2(const Func &func, const string & name)
	{
		// Because we are providing the template argument <Func> compiler can infer the type
		return Logger2<Func>{func, name};
	}





	// --------------------------------------------------------------------------
	// Logger for a function that takes parameters and returns a value
	double add(double a, double b)
	{
		cout << a << " + " << b << " = " << a + b << endl;
		return a + b;
	}

	template <typename> class Logger3;
	template <typename R, typename... Args>
	class Logger3<R(Args...)>
	{
		function<R(Args...)> func_;
		string name_;
	public:
		Logger3(const function<R(Args...)> &func, const string& name) : func_(func), name_(name) {}

		R operator()(Args... args) {
			cout << "Entering " << name_ << endl;
			R result = func_(args...);
			cout << "Exiting " << name_ << endl;
			return result;
		}

	};


	template <typename R, typename... Args>
	auto make_logger3(R(*func)(Args...), const string& name)
	{
		return Logger3<R(Args...)>{
			function<R(Args...)>(func),  // Convert the function pointer to functional
			name
		};
	}
	// --------------------------------------------------------------------------
}