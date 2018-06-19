#pragma once
#include <vector>
#include <iostream>

using namespace std;


// CRTP : Curiously Recurring Template Pattern
// We want to be able to connect 
// 1- NeuronLayer -> NeuronLayer, 
// 2- NeuronLayer -> Neuron,
// 3- Neuron -> NeuronLayer, 
// 4- Neuron -> Neuron
// But we don't want to implement four different functions

class Neuron;
template <typename Self>
class SomeNeurons
{
public:
	template <typename T>
	void connect_to(T& other)
	{
		// We cast this pointer to derived class type. This type info is given in typename Self
		// Remember Neuron inherits from SomeNeurons<Neuron> whereas 
		// NeuronLayer inherits from SomeNeurons<NeuronLayer>. So with this static_cast to Self we get the actual object.
		// Also note that if Self is a Neuron object, it is not a vector like NeuronLayer (NeuronLayer ISA Vector (bad practice))
		// therefore we can not iterate it with range based for. To be able to use range based for we need to implement begin() and
		// end() methods in Neuron class.
		for (Neuron& from : *static_cast<Self*>(this))
		{
			for (Neuron& to : other)
			{
				from.out_.push_back(&to);
				to.in_.push_back(&from);
			}
		}
	}
};


class Neuron : public SomeNeurons<Neuron>
{
	unsigned int id_;
public:
	vector<Neuron*> in_, out_;
	Neuron()
	{
		static int id = 1;
		id_ = id++;
	}

	Neuron* begin() { return this; }
	Neuron* end() { return this + 1; }

	friend ostream& operator<<(ostream& out, const Neuron& obj)
	{
		for (Neuron* np : obj.in_)
		{
			cout << "[" << obj.id_ << "]\t<---\t[" << np->id_ << "]" << endl;
		}
		for (Neuron* np : obj.out_)
		{
			cout << "[" << obj.id_ << "]\t--->\t[" << np->id_ << "]" << endl;
		}

		return out;
	}
};

// Inheriting from STL types should be AVOIDED! This is just for demonstration purposes
class NeuronLayer : public vector<Neuron>, public SomeNeurons<NeuronLayer>
{
public:
	NeuronLayer(int count)
	{
		while (count -- > 0)
		{
			// Remember this object is a vector
			this->emplace_back(Neuron{});
		}
	}

	friend ostream& operator<<(ostream& out, const NeuronLayer& obj)
	{
		for (const Neuron& n : obj)
		{
			out << n;
		}
		return out;
	}
};
