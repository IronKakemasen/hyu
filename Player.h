#pragma once
#include "VectorMatrix.h"
#include "Novice.h"
#include "BaseClass.h"
#include "Bullet.h"

struct Player
{

private:

	bool isActive = true;
	Vector3 pos;
	float rad = 10;
	float t = 0;
	static float constexpr kInv_coolTime = 1.0f / 15.0f;


public: 

	Bullet* b = nullptr;

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


	void Shoot(char* keys)
	{
		if (keys[DIK_SPACE])
		{
			t += kInv_coolTime;
			if (t >= 1.0f)
			{
				for (int i = 0; i < 10; ++i)
				{
					if (!b[i].isActive)
					{
						b[i].isActive = true;
						b[i].pos = pos;
						t = 0.0f;
						break;
					}
				}
				
			}
		}

	}

	void Move(char* keys)
	{
		if (keys[DIK_W])
		{
			pos.y += 2;
		}

		else if (keys[DIK_S])
		{
			pos.y -= 2;
		}

		if (keys[DIK_A])
		{
			pos.x -= 2;
		}

		else if (keys[DIK_D])
		{
			pos.x += 2;
		}

	}

	void Render(Matrix3x3 vpv)
	{
		DrawBox(pos, rad, rad, { 0,0,0,255 }, kFillModeSolid, kBlendModeNormal, vpv);
	}



	Player()
	{
		pos = { 0,0,1 };
	}

};

