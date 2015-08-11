#ifndef RANDOMRESOURCE_H
#define RANDOMRESOURCE_H

#include <random>

class RandomResource
{
private:

protected:

public:
	RandomResource();

	int generateInt(int iMin, int iMax);
	float generateFloat(float fMin, float fMax);


};

#endif //RANDOMRESOURCE_H