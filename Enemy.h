#pragma once
#include "VectorMatrix.h"
#include "BaseClass.h"

struct Enemy
{

private:

	Vector3 pos;
	float rad = 10;
	bool isActive = true;

public:

	void SetterIsActive(bool _isActive)
	{
		isActive = _isActive;
	}

	void SetterPos(Vector3 ppos)
	{
		pos = ppos;
	}


	Vector3 GetterPos()
	{
		return pos;
	}

	float GetterRad()
	{
		return rad;
	}

	bool GetterIsActive()
	{
		return isActive;
	}


	void Move()
	{
		if (isActive)
		{
			pos.x -= 3;
		}
	}

	void Render(Matrix3x3 vpv)
	{
		if (isActive)
		{
			DrawBox(pos, rad, rad, { 200,120,0,255 }, kFillModeSolid, kBlendModeNormal, vpv);
		}
	}

	Enemy()
	{
		pos = { 640,float(rand()&720),1};
	}

};

