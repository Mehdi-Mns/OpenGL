#pragma once
#include <iostream>

using namespace std;


class Vector {

private:
	double[] elem;
	int dim;

public:

	Vector(int dim);
	Vector(double[] tab);
	~Vector();
	friend ostream& operator<<(ostream& out, const Vector & v);
};
