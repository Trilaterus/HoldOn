#include "RandomResource.h"

RandomResource::RandomResource()
{

}

int RandomResource::generateInt(int iMin, int iMax)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(iMin, iMax);
	return dist(mt);
}

float RandomResource::generateFloat(float fMin, float fMax)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(fMin, fMax);
	return dist(mt);
}