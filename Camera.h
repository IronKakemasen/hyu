#pragma once
#include "BaseClass.h"

struct Camera :RectangleObject
{
	Vector3 viewPoint;
	Matrix3x3 VPVmat;												//VPVp行列(スクリーン座標に変換する行列
	Matrix3x3 viewMat;
	Matrix3x3 orthoMat;
	Matrix3x3 viewPortTransformMat;

	Camera()
	{
		trans.pos = { 0,0,1 };
		SetLocalVertex(collisionRect, kWindowWidth, kWindowHeight);
		//SRT行列をセット
		trans.mat = trans.GetAffineMatrix3x3(kSRT);
		SubstituteResultForVertexes(collisionRect);
		viewPortTransformMat = GetViewPortMatrix();
	}

	void Follow(Vector3 follow_pos, float transitionSpeed);
	Matrix3x3 GetOrthographicMatrix();
	Matrix3x3 GetViewPortMatrix();
	//引数のオブジェクトのVPV行列をセットする
	Matrix3x3 GetVPVMatrix();
	Vector3 ConvertToWorldPos(Vector3 dst_Vector3);

};
