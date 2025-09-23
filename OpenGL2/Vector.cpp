#include "Vector.h"

class Vector {

	Vector::Vector(int dim) : dim{ dim }, elem{ new double[dim] } {}

	Vector::Vector(double[] liste) : dim{ liste.length }, valeur{ liste } {}

	Vector::~Vector() {};

	/*operator[](int i) {

	}*/

	ostream& operator<<(ostream& out, const Vector& v) {
		for (double i : v) {
			out << i << ", ";
		}
	};