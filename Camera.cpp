#include "Camera.h"



Matrix3x3 Camera::GetOrthographicMatrix()
{
	const float inv_W{ 1.0f / (collisionRect.RT.x - collisionRect.LT.x) };
	const float inv_H{ 1.0f / (collisionRect.LT.y - collisionRect.RB.y) };

	Matrix3x3 OrthographicMatrix;
	OrthographicMatrix.m[0][0] = 2.0f * inv_W;
	OrthographicMatrix.m[1][1] = 2.0f * inv_H;
	OrthographicMatrix.m[2][0] = -(collisionRect.LT.x + collisionRect.RB.x) * inv_W;
	OrthographicMatrix.m[2][1] = -(collisionRect.LT.y + collisionRect.RB.y) * inv_H;
	OrthographicMatrix.m[2][2] = 1.0f;

	return OrthographicMatrix;
}

Matrix3x3 Camera::GetViewPortMatrix()
{
	Matrix3x3 viewPortMatrix;

	viewPortMatrix.m[0][0] = kWindowWidth * 0.5f;
	viewPortMatrix.m[1][1] = -kWindowHeight * 0.5f;
	viewPortMatrix.m[2][0] = viewPoint.x + kWindowWidth * 0.5f;
	viewPortMatrix.m[2][1] = viewPoint.y + kWindowHeight * 0.5f;
	viewPortMatrix.m[2][2] = 1.0f;

	return viewPortMatrix;
}

Matrix3x3 Camera::GetVPVMatrix()
{
	//カメラの変形
	//SRT行列をセット
	trans.mat = trans.GetAffineMatrix3x3(kSRT);
	//逆行列
	viewMat = Matrix3x3::GetInversedMat3(trans.mat);
	//正射影行列の作成
	orthoMat = GetOrthographicMatrix();
	//VP行列の作成（正射影行列の作成）
	Matrix3x3 ret_mat = Matrix3x3::GetProductReultOfMatrixes(&viewMat, &orthoMat);
	ret_mat = Matrix3x3::GetProductReultOfMatrixes(&ret_mat, &viewPortTransformMat);

	return ret_mat;
}

Vector3 Camera::ConvertToWorldPos(Vector3 dst_Vector3)
{
	Matrix3x3 inv_viewPortTransformMat = Matrix3x3::GetInversedMat3(viewPortTransformMat);
	Matrix3x3 inv_orthoMat = Matrix3x3::GetInversedMat3(orthoMat);
	Matrix3x3 inv_viewMat = Matrix3x3::GetInversedMat3(viewMat);

	dst_Vector3 = Matrix3x3::GetProductReultOfVectorAndMatrix(dst_Vector3, inv_viewPortTransformMat);
	dst_Vector3 = Matrix3x3::GetProductReultOfVectorAndMatrix(dst_Vector3, inv_orthoMat);
	dst_Vector3 = Matrix3x3::GetProductReultOfVectorAndMatrix(dst_Vector3, inv_viewMat);

	return dst_Vector3;
}

void Camera::Follow(Vector3 follow_pos,float transitionSpeed)
{
	Vector3 dir = follow_pos - trans.pos;
	dir.SetMagnitutde();
	float hoge = dir.magnitude *0.01f;
	if (hoge > 1.0f) hoge = 1;
	Vector3 hage = dir.GetNormalizedVec();
	transitionSpeed *= hoge;

	trans.pos = trans.pos + dir * transitionSpeed;

}