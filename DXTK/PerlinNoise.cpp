#include "PerlinNoise.h"
#include <cmath>

PerlinNoise::PerlinNoise(long _seed)
{
	seed = _seed;
}

PerlinNoise::~PerlinNoise()
{
}

int PerlinNoise::generateNoise(int _x, int _range)
{
	int chunk_size = 16;
	float noise = 0;

	while (chunk_size > 0 && _range > 0)
	{
		int chunk_index = _x / chunk_size;
		float prog = (_x % chunk_size) / chunk_size;

		float left_random = random(chunk_index, _range);
		float right_random = random(chunk_index + 1, _range);

		noise + = (1 - prog) * left_random + prog * right_random;

		chunk_size /= 2;
		_range /= 2;
	}

	return (int)ceil(noise);
}

int PerlinNoise::random(int _x, int _range)
{
	return (int)((_x + seed) ^ 5) % _range;
}
