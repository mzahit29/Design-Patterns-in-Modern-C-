#pragma once
#include <string>
#include <iostream>


using namespace std;

class Image
{
	virtual void draw() = 0;
};

class Bitmap : public Image
{
	string filename_;

public:
	Bitmap(const string & filename) : filename_(filename)
	{
		// Assume the Bitmap class is an API provided by some 3rd party and it is loading the image
		// on constructor. This is not what we want, we want the image to be lazy loaded, meaning loaded when
		// draw() is called. VirtualBitMap will only store the file name on its constructor. On VirtualBitMap::draw() we
		// instantiate the Bitmap instance and call draw. To accomplish this we will create a virtual proxy class around bitmap
		cout << "Loading " << filename_ << endl;
	}

	void draw() override
	{
		cout << "Drawing image " << filename_ << endl;
	}
};

class VirtualBitmap
{
	string filename_;
	Bitmap * bitmap_{nullptr};
public:

	explicit VirtualBitmap(const string& filename)
		: filename_(filename)
	{
	}
	~VirtualBitmap()
	{
		delete bitmap_;
	}

	void draw()
	{
		// Lazy loading
		bitmap_ = new Bitmap(filename_);
		bitmap_->draw();
	}
};