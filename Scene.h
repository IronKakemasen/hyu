#pragma once
#include "VectorMatrix.h"
#include <Novice.h>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include"Camera.h"


struct SceneBehavior
{
	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


	enum class nextScene
	{
		kTitle,
		kPlay,


		kCount
	};

	virtual void Update() = 0;
	virtual void Render(const Matrix3x3& VPVMat) = 0;
	virtual void Initiaize() = 0;
	static int const temp = static_cast<int>(nextScene::kCount);
	bool changeScene[temp] = {};
	virtual ~SceneBehavior() {};

};

struct Title:SceneBehavior
{
	virtual void Update()override
	{
		if (Novice::IsTriggerMouse(0))
		{
			int next = static_cast<int>(nextScene::kPlay);
			changeScene[next] = true;
		}

		Matrix3x3 m;
		Render(m);
	}

	virtual void Render(const Matrix3x3& VPVMat)override
	{
		VPVMat;
		Novice::ScreenPrintf(0, 360, "Click");

	}

	virtual void Initiaize() override {};


};

struct InGame:SceneBehavior
{
	Player* p;
	Enemy* e;
	Camera* c;

	virtual void Update()override
	{
		c->VPVmat = c->GetVPVMatrix();

		p->Move(keys);
		p->Shoot(keys);
		p->Render(c->VPVmat);
		Vector3 pPos = p->GetterPos();
		float pRadius = p->GetterRad();

		for (int i = 0; i < 10; ++i)
		{
			Vector3 ePos = e[i].GetterPos();
			float eRadius =e[i].GetterRad();
			bool eIsActive =e[i].GetterIsActive();


			if (eIsActive && CircleCollisionDetection(pPos, pRadius, ePos, eRadius))
			{
				e[i].SetterIsActive(0);
				p->SetterIsActive(0);
				continue;
			}

			for (int k = 0; k < 10; ++k)
			{
				if (eIsActive && p->b[k].isActive &&
					CircleCollisionDetection(p->b[k].pos, p->b[k].rad, ePos, eRadius))
				{
					e[i].SetterIsActive(0);
					p->b[k].isActive = false;
					continue;
				}
			}


			e[i].Move();
			e[i].Render(c->VPVmat);
		}


		for (int i = 0; i < 10; ++i)
		{
			p->b[i].Move();
			p->b[i].Render(c->VPVmat);

		}

		Render(c->VPVmat);

		for (int i = 0; i < 10; ++i)
		{
			if (!e[i].GetterIsActive())
			{
				e[i].SetterPos({ 640,float(rand() & 720) });
				e[i].SetterIsActive(1);

			}
		}


		if (!p->GetterIsActive())
		{
			int next = static_cast<int>(nextScene::kTitle);
			changeScene[next] = true;
		}
	}

	virtual void Render(const Matrix3x3& VPVMat)override
	{
		VPVMat;
	}

	virtual void Initiaize()override
	{
		for (int i = 0; i < 10; ++i)
		{
			e[i].SetterIsActive(1);
			p->SetterIsActive(1);
			p->SetterPos({0,0,1});
			e[i].SetterPos({ 640,float(rand() & 720) });
			p->b[i].isActive = false;
		}

	} 


};

