#pragma once
#include "VectorMatrix.h"
#include "BaseClass.h"

class Bullet
{
public:
	Vector3 pos;
	float rad = 10;
	bool isActive = false;

	void Move()
	{
		if (isActive)
		{
			pos.x += 3;
		}
	}

	void Render(Matrix3x3 vpv)
	{
		if (isActive)
		{
			DrawBox(pos, rad, rad, { 200,0,0,255 }, kFillModeSolid, kBlendModeNormal, vpv);
		}
	}

};

