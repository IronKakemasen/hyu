#include "BaseClass.h"

//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------

Matrix3x3 Transform::GetAffineMatrix3x3(MatrixType matType)
{
	Matrix3x3 make_Mat;

	switch (matType)
	{
	case kT:

		make_Mat.m[0][0] = 1;
		make_Mat.m[1][1] = 1;
		make_Mat.m[2][0] = pos.x;
		make_Mat.m[2][1] = pos.y;
		make_Mat.m[2][2] = 1;

		break;

	case kSRT:
	{
		float rotateRadian = GetConvertedDegree(rotateTheta);

		make_Mat.m[0][0] = scale.x * cosf(rotateRadian);
		make_Mat.m[0][1] = scale.x * sinf(rotateRadian);
		make_Mat.m[1][0] = -scale.y * sinf(rotateRadian);
		make_Mat.m[1][1] = scale.y * cosf(rotateRadian);
		make_Mat.m[2][0] = pos.x;
		make_Mat.m[2][1] = pos.y;
		make_Mat.m[2][2] = 1;

		break;
	}
	case kSTR:
	{
		float movementRadian = GetConvertedDegree(movementTheta);

		make_Mat.m[0][0] = scale.x * cosf(movementRadian);
		make_Mat.m[0][1] = scale.x * sinf(movementRadian);
		make_Mat.m[1][0] = -scale.y * sinf(movementRadian);
		make_Mat.m[1][1] = scale.y * cosf(movementRadian);
		make_Mat.m[2][0] = pos.x * cosf(movementRadian) - sinf(movementRadian) * pos.y;
		make_Mat.m[2][1] = pos.x * sinf(movementRadian) + cosf(movementRadian) * pos.y;
		make_Mat.m[2][2] = 1;

		break;
	}
	}

	return make_Mat;
}


//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------
void Appearance::Initialize(SpriteTag dst_spriteTag, Vector4 ini_color, BlendMode ini_blendMode)
{
	for (int i = 0;i<textureSum;++i)
	{
		dst_spriteTag;
		//if (global_textureInfos[i].sprTag == dst_spriteTag)
		//{
		//	texture = global_textureInfos[i];
		//	break;
		//}
	}

	blendMode = ini_blendMode;
	kOriginal_color = ini_color;
	current_color = kOriginal_color;
}
int Appearance::GetIntColor(Vector4 src_color)
{
	src_color.x = roundf(src_color.x);
	src_color.y = roundf(src_color.y);
	src_color.z = roundf(src_color.z);
	src_color.w = roundf(src_color.w);

	return (0x01000000 * (int)src_color.x + 0x00010000 * (int)src_color.y +
		0x00000100 * (int)src_color.z + 0x00000001 * (int)src_color.w);
}
//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------
void PhysicalElements2D::Initialize(float ini_cor, float ini_mass)
{
	cor = ini_cor;
	mass = ini_mass;
}

void PhysicalElements2D::Clear()
{
	//gravity = 0;
	velocity = kZeroVec;
}

//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------
void RectangleObject::SetLocalVertex(RectShape &dstRect, float ini_width, float ini_height)
{
	//左上の頂点
	dstRect.local_LT.x = -ini_width / 2.0f + trans.local_pos.x;
	dstRect.local_LT.y = ini_height / 2.0f + trans.local_pos.y;
	//右上の頂点
	dstRect.local_RT.x= ini_width / 2.0f + trans.local_pos.x;
	dstRect.local_RT.y= ini_height / 2.0f + trans.local_pos.y;
	//左下の頂点
	dstRect.local_LB.x = -ini_width / 2.0f + trans.local_pos.x;
	dstRect.local_LB.y = -ini_height / 2.0f + trans.local_pos.y;
	//右下の頂点
	dstRect.local_RB.x= ini_width / 2.0f + trans.local_pos.x;
	dstRect.local_RB.y= -ini_height / 2.0f + trans.local_pos.y;
}
void RectangleObject::DrawRect( const Matrix3x3& VPVMat)
{
	if (isActive)
	{
		int color = appear.GetIntColor(appear.current_color);

		RectShape tempShape;
		tempShape.LT = Matrix3x3::GetProductReultOfVectorAndMatrix(appearanceRect.LT, VPVMat);
		tempShape.RT = Matrix3x3::GetProductReultOfVectorAndMatrix(appearanceRect.RT, VPVMat);
		tempShape.LB = Matrix3x3::GetProductReultOfVectorAndMatrix(appearanceRect.LB, VPVMat);
		tempShape.RB = Matrix3x3::GetProductReultOfVectorAndMatrix(appearanceRect.RB, VPVMat);

		Novice::SetBlendMode(appear.blendMode);

		Novice::DrawQuad(
			static_cast<int>(roundf(tempShape.LT.x)),
			static_cast<int>(roundf(tempShape.LT.y)),
			static_cast<int>(roundf(tempShape.RT.x)),
			static_cast<int>(roundf(tempShape.RT.y)),
			static_cast<int>(roundf(tempShape.LB.x)),
			static_cast<int>(roundf(tempShape.LB.y)),
			static_cast<int>(roundf(tempShape.RB.x)),
			static_cast<int>(roundf(tempShape.RB.y)),
			int(appear.texture.spriteWidth * appear.texture.spriteNum), 0,
			int(appear.texture.spriteWidth), int(appear.texture.spriteHeight),
			appear.texture.GH, unsigned int(color));
	}
}
bool RectangleObject::ObjectAABB(RectangleObject* const obj1, RectangleObject* const obj2)
{
	bool ret = false;

	if ((obj1->collisionRect.LT.x < obj2->collisionRect.RB.x) && 
		(obj1->collisionRect.RB.x > obj2->collisionRect.LT.x))
	{
		if ((obj1->collisionRect.LT.y > obj2->collisionRect.RB.y) && 
			(obj1->collisionRect.RB.y < obj2->collisionRect.LT.y))
		{
			ret = true;
		}
	}

	return ret;
}

//[矩形専用]４頂点を行列と計算する
void RectangleObject::SubstituteResultForVertexes(RectShape &dstRect)
{
	dstRect.LT = Matrix3x3::GetProductReultOfVectorAndMatrix(dstRect.local_LT, trans.mat);
	dstRect.RT = Matrix3x3::GetProductReultOfVectorAndMatrix(dstRect.local_RT, trans.mat);
	dstRect.LB = Matrix3x3::GetProductReultOfVectorAndMatrix(dstRect.local_LB, trans.mat);
	dstRect.RB = Matrix3x3::GetProductReultOfVectorAndMatrix(dstRect.local_RB, trans.mat);
}

//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------

void GameObject::TranslatePosition()
{
	//速度を徐々に減速させる
	velocity.x *= 0.925f;
	velocity.y *= 0.925f;

	//速度が０に近くなったら0にする
	if (velocity.x <= 0.25f&& velocity.x >= -0.25f)
	{
		velocity.x = 0.0f;
	}

	if (velocity.y <= 0.25f && velocity.y >= -0.25f)
	{
		velocity.y = 0.0f;
	}

	//座標移動
	trans.pos.x += velocity.x;
	trans.pos.y += velocity.y;
}

//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------
bool GameManager::GetKeyStatus(int dstKey, KeyStatus keyStatus)
{
	bool ret = false;

	switch (keyStatus)
	{
	case kPushed:

		if (keys[dstKey] && !preKeys[dstKey])
		{
			ret = true;
		}

		break;

	case kPushing:

		if (keys[dstKey])
		{
			ret = true;
		}

		break;

	case kReleased:

		if (preKeys[dstKey] && !keys[dstKey])
		{
			ret = true;
		}

		break;
	}

	return ret;
}

void GameManager::SortObject()
{
	//更新処理順で並び変える
	std::sort(update_data.begin(), update_data.end(),
		[](const GameObject* lhs, const GameObject* rhs) { return lhs->updatePriNo < rhs->updatePriNo; });
	//描画優先度で並び変える
	std::sort(render_data.begin(), render_data.end(),
		[](const GameObject* lhs, const GameObject* rhs) { return lhs->renderPriNo < rhs->renderPriNo; });
}


//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------
//ラインを描画する
void DrawLine(Vector3 world_stPoint, Vector3 world_endPoint, Vector4 color, BlendMode mode, Matrix3x3 VPVpmat)
{
	Transform point[2];

	point[0].pos = Matrix3x3::GetProductReultOfVectorAndMatrix(world_stPoint, VPVpmat);
	point[1].pos = Matrix3x3::GetProductReultOfVectorAndMatrix(world_endPoint, VPVpmat);

	int tempColor = Appearance::GetIntColor(color);

	Novice::SetBlendMode(mode);
	Novice::DrawLine((int)point[0].pos.x, (int)point[0].pos.y,
		(int)point[1].pos.x, (int)point[1].pos.y, tempColor);
}

//ボックスを描画する
void DrawBox(Vector3 LTPoint, float width, float height, Vector4 color, FillMode mode,BlendMode blendMode, Matrix3x3 VPVpmat)
{
	Vector3 screen_LTPoint = Matrix3x3::GetProductReultOfVectorAndMatrix(LTPoint, VPVpmat);
	int tempColor = Appearance::GetIntColor(color);
	Novice::SetBlendMode(blendMode);
	Novice::DrawBox(int(screen_LTPoint.x), int(screen_LTPoint.y), (int)width, (int)height, 0, tempColor, mode);
}

void DrawEllipse(Vector3 center, float radiusX, float radiusY, Vector4 color, FillMode mode, BlendMode blendMode, Matrix3x3 VPVpmat)
{
	Vector3 screen_center = Matrix3x3::GetProductReultOfVectorAndMatrix(center,VPVpmat);
	int tempColor = Appearance::GetIntColor(color);
	Novice::SetBlendMode(blendMode);
	Novice::DrawEllipse(int(screen_center.x), int(screen_center.y), (int)radiusX, (int)radiusY, 0, tempColor, mode);

}

//スクリーン座標からワールドへ変換
Vector3 ConvertScreenToWorld(Vector3 dst_Vector3, const Matrix3x3 viewMat, const Matrix3x3 projectionMat, const Matrix3x3 viewport)
{
	
	

	Matrix3x3 inv_viewMat = Matrix3x3::GetInversedMat3(viewMat);
	Matrix3x3 inv_projectionMat = Matrix3x3::GetInversedMat3(projectionMat);
	Matrix3x3 inv_viewport = Matrix3x3::GetInversedMat3(viewport);

	dst_Vector3 = Matrix3x3::GetProductReultOfVectorAndMatrix(dst_Vector3, inv_viewport);
	dst_Vector3 = Matrix3x3::GetProductReultOfVectorAndMatrix(dst_Vector3, inv_projectionMat);
	dst_Vector3 = Matrix3x3::GetProductReultOfVectorAndMatrix(dst_Vector3, inv_viewport);

	return dst_Vector3;

}

void DrawQuad(Vector3 LTPoint, Vector3 RTPoint, Vector3 LBPoint, Vector3 RBPoint, int GH,float width, float height,
	Vector4 color, BlendMode blendMode, Matrix3x3 VPVpmat)
{
	int tempColor = Appearance::GetIntColor(color);

	Vector3 LT  = Matrix3x3::GetProductReultOfVectorAndMatrix( LTPoint, VPVpmat);
	Vector3 RT  = Matrix3x3::GetProductReultOfVectorAndMatrix( RTPoint, VPVpmat);
	Vector3 LB  = Matrix3x3::GetProductReultOfVectorAndMatrix( LBPoint, VPVpmat);
	Vector3 RB  = Matrix3x3::GetProductReultOfVectorAndMatrix( RBPoint, VPVpmat);


	Novice::SetBlendMode(blendMode);

	Novice::DrawQuad(
		static_cast<int>(roundf(LT.x)),
		static_cast<int>(roundf(LT.y)),
		static_cast<int>(roundf(RT.x)),
		static_cast<int>(roundf(RT.y)),
		static_cast<int>(roundf(LB.x)),
		static_cast<int>(roundf(LB.y)),
		static_cast<int>(roundf(RB.x)),
		static_cast<int>(roundf(RB.y)),
		0, 0,
		int(width), int(height),
		GH, unsigned int(tempColor));
}

bool VoidTyan(Vector3 dst_pos, RectShape dst_collRect)
{
	bool ret = false;

	if (dst_pos.x >= dst_collRect.LT.x && dst_pos.x <= dst_collRect.RT.x &&
		dst_pos.y <= dst_collRect.LT.y && dst_pos.y >= dst_collRect.LB.y)
	{
		ret = true;
	}

	return ret;
}

bool CircleCollisionDetection(Vector3 p1, float r1, Vector3 p2, float r2)
{
	bool ret = false;

	Vector3 diff = p1 - p2;
	diff.SetMagnitutde();
	if (diff.magnitude <= r1 + r2)
	{
		ret = true;
	}

	return ret;
}