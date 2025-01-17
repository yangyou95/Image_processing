/*----------------------------------------------------------------*/
/* Pixel class declaration.                                       */
/* File name: pixel.h                                             */
/* This class implements the concept of a pixel                   */
//#ifndef PIXEL_H
//#define PIXEL_H
#include <iostream> //Required for istream, ostream
using namespace std;

class Pixel
{
  public:
	// constants to enable undeflow/overflow detection in rgb values
	static const int MAXVAL = 255;
	static const short RMASK = 4;
	static const short GMASK = 2;
	static const short BMASK = 1;
	static const short CHECK = 7;

	//Constructors 
	Pixel(); //Default
	Pixel(unsigned ); //Grey scale
	Pixel(unsigned,unsigned,unsigned); //Full color range

	// Accessor Methods
	unsigned getRed() const {return red;}
	unsigned getGreen() const {return green;}
	unsigned getBlue() const {return blue;}


	// Mutator Methods
	Pixel& setPixel(unsigned r, unsigned g, unsigned b);
	Pixel& setRed(unsigned r); 
	Pixel& setGreen(unsigned g);
	Pixel& setBlue(unsigned b);

	//Overloaded operators.
	//Addition.
	Pixel operator+(const Pixel& p) const;

	//Substaction (Yang)
	Pixel operator-(const Pixel& p) const;

	//power(Yang)
	Pixel operator^(double v) const;

	//Multiplication of a Pixel by a floating point value.
	Pixel operator*(double v) const;

	//Division of a Pixel by an integer value.
	Pixel operator/(unsigned int v) const;



	//Input operator.
	friend istream& operator >>(istream& in, Pixel& p);

	//Output operator.
	friend ostream& operator <<(ostream& out, const Pixel& p);

	// assignment
	Pixel& operator=(const Pixel& rhs);

	bool overflow(); //check for overflow 
	void reset();   //reset to MAXVAL 

  private:
	void validate(); //set overflow bits
	unsigned int red, green, blue;
	unsigned short overflowFlag;
};
//#endif
/*----------------------------------------------------------------*/
