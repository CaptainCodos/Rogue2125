#include "ExtraMaths.h"
#include <stdlib.h>
#include <cstdlib>

using namespace sf;
using namespace std;

float ExtraMaths::GetRandom(float min, float max)
{
	float diff = max - min;
	float basicRand = std::rand() % (int)diff;
	return (float)(basicRand + min);
	//return (float)rand() / (float)RAND_MAX * (max - min) + min;
}
int ExtraMaths::GetRandomInt(int min, int max)
{
	int diff = max - min;
	int basicRand = std::rand() % diff;
	return (int)(basicRand + min);
	//return (int)rand() / (int)RAND_MAX * (max - min) + min;
}