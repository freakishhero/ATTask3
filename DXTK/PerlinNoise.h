#pragma once

class PerlinNoise
{
public:
	PerlinNoise(long _seed);
	~PerlinNoise();

	int generateNoise(int _x, int _range);

private:
	int random(int _x, int _range);
	long seed;

};