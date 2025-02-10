#include "VectorMatrix.h"
#include <math.h>
#include <string.h>

//===================================================================================================================


//---------------------ベクトルの便利関数------------------------------------------------------------------
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//二つのベクトルの外積からsin(🍆角)を求めて返す関数
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
float Vector3::GetSinThetaFromTwoVector3(Vector3 src1_Vector3, Vector3 src2_Vector3)
{
	float ret_sinTheta = 0.0f;

	//正規化する
	Vector3 normalized1_Vector3 = src1_Vector3.GetNormalizedVec();
	Vector3 normalized2_Vector3 = src2_Vector3.GetNormalizedVec();
	//sin(🍆角)
	ret_sinTheta = normalized1_Vector3.x * normalized2_Vector3.y - normalized2_Vector3.x * normalized1_Vector3.y;

	return ret_sinTheta;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//二つのベクトルの内積からcos(🍆角)を求めて返す関数
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
float Vector3::GetCosThetaFromTwoVector3(Vector3 src1_Vector3, Vector3 src2_Vector3)
{
	float ret_cosTheta = 0.0f;

	//正規化する
	Vector3 normalized1_Vector3 = src1_Vector3.GetNormalizedVec();
	Vector3 normalized2_Vector3 = src2_Vector3.GetNormalizedVec();
	//cos(🍆角)
	ret_cosTheta = normalized1_Vector3.x * normalized2_Vector3.x + normalized1_Vector3.y * normalized2_Vector3.y;

	return ret_cosTheta;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//引数の２点の座標から、my_posからdst_pos方向への単位ベクトルを計算し返す関数(Vector3)
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
Vector3 Vector3::GetNormalizedVector3BetweenTwo(Vector3 my_pos, Vector3 dst_pos)
{
	Vector3 ret_eVector3;
	Vector3 ret_diff;					//差分ベクトル

	//差分を計算
	ret_diff = dst_pos - my_pos;
	//大きさを計算
	ret_diff.SetMagnitutde();
	ret_diff = ret_diff.GetNormalizedVec();

	return ret_diff;
}


//---------------------メンバ関数------------------------------------------------------------------
void Vector3::SetMagnitutde()
{
	magnitude = sqrtf(x * x + y * y);
}

Vector3 Vector3::GetNormalizedVec()
{
	float inv_mag = 0;

	if (magnitude != 0) inv_mag = 1.0f / magnitude;
	Vector3 ret_normalizeVec = { x * inv_mag ,y * inv_mag };
	ret_normalizeVec.magnitude = magnitude;

	return ret_normalizeVec;
}

Vector3 Vector3::Lerp(Vector3 st, Vector3 end, float dt)
{
	return end * dt + st * (1.0f - dt);
}


//---------------------オペランド------------------------------------------------------------------
Vector3 operator-(Vector3 const& vec1, Vector3  const& vec2)
{
	Vector3  ret_vec = { vec1.x - vec2.x,vec1.y - vec2.y ,1 };

	return ret_vec;
}

Vector3 operator+(Vector3 const& vec1, Vector3  const& vec2)
{
	Vector3  ret_vec = { vec1.x + vec2.x,vec1.y + vec2.y ,1 };

	return ret_vec;
}

Vector3 operator*(Vector3  const& vec1, float const multipleNum)
{
	Vector3  ret_vec = { vec1.x * multipleNum,vec1.y * multipleNum ,1 };

	return ret_vec;
}



Vector3 Vector3::operator+=(float const addNum)
{
	x += addNum;
	y += addNum;

	return *this;
}

Vector3 Vector3::operator=(float const num)
{
	x = num;
	y = num;

	return *this;
}



//===================================================================================================================
Vector3 Matrix3x3::GetProductReultOfVectorAndMatrix(Vector3 dest_Vector3, Matrix3x3 src_mat)
{
	Vector3 ret_Vector3 = { 0,0,1 };

	ret_Vector3.x = dest_Vector3.x * src_mat.m[0][0] + dest_Vector3.y * src_mat.m[1][0] + dest_Vector3.w * src_mat.m[2][0];
	ret_Vector3.y = dest_Vector3.x * src_mat.m[0][1] + dest_Vector3.y * src_mat.m[1][1] + dest_Vector3.w * src_mat.m[2][1];

	return ret_Vector3;
}

Matrix3x3 Matrix3x3::GetProductReultOfMatrixes(Matrix3x3* const kSrc_mat1, Matrix3x3* const kSrc_mat2)
{
	Matrix3x3 ret_mat;

	ret_mat.m[0][0] = kSrc_mat1->m[0][0] * kSrc_mat2->m[0][0] + kSrc_mat1->m[0][1] * kSrc_mat2->m[1][0] + kSrc_mat1->m[0][2] * kSrc_mat2->m[2][0];
	ret_mat.m[0][1] = kSrc_mat1->m[0][0] * kSrc_mat2->m[0][1] + kSrc_mat1->m[0][1] * kSrc_mat2->m[1][1] + kSrc_mat1->m[0][2] * kSrc_mat2->m[2][1];
	ret_mat.m[0][2] = kSrc_mat1->m[0][0] * kSrc_mat2->m[0][2] + kSrc_mat1->m[0][1] * kSrc_mat2->m[1][2] + kSrc_mat1->m[0][2] * kSrc_mat2->m[2][2];
	ret_mat.m[1][0] = kSrc_mat1->m[1][0] * kSrc_mat2->m[0][0] + kSrc_mat1->m[1][1] * kSrc_mat2->m[1][0] + kSrc_mat1->m[1][2] * kSrc_mat2->m[2][0];
	ret_mat.m[1][1] = kSrc_mat1->m[1][0] * kSrc_mat2->m[0][1] + kSrc_mat1->m[1][1] * kSrc_mat2->m[1][1] + kSrc_mat1->m[1][2] * kSrc_mat2->m[2][1];
	ret_mat.m[1][2] = kSrc_mat1->m[1][0] * kSrc_mat2->m[0][2] + kSrc_mat1->m[1][1] * kSrc_mat2->m[1][2] + kSrc_mat1->m[1][2] * kSrc_mat2->m[2][2];
	ret_mat.m[2][0] = kSrc_mat1->m[2][0] * kSrc_mat2->m[0][0] + kSrc_mat1->m[2][1] * kSrc_mat2->m[1][0] + kSrc_mat1->m[2][2] * kSrc_mat2->m[2][0];
	ret_mat.m[2][1] = kSrc_mat1->m[2][0] * kSrc_mat2->m[0][1] + kSrc_mat1->m[2][1] * kSrc_mat2->m[1][1] + kSrc_mat1->m[2][2] * kSrc_mat2->m[2][1];
	ret_mat.m[2][2] = kSrc_mat1->m[2][0] * kSrc_mat2->m[0][2] + kSrc_mat1->m[2][1] * kSrc_mat2->m[1][2] + kSrc_mat1->m[2][2] * kSrc_mat2->m[2][2];

	return ret_mat;
}

Matrix3x3 Matrix3x3::GetInversedMat3(Matrix3x3 src_mat3)
{
	float temp =
		(
			(
				src_mat3.m[0][0] * src_mat3.m[1][1] * src_mat3.m[2][2] +
				src_mat3.m[0][1] * src_mat3.m[1][2] * src_mat3.m[2][0] +
				src_mat3.m[0][2] * src_mat3.m[1][0] * src_mat3.m[2][1]
				) -
			(
				src_mat3.m[0][2] * src_mat3.m[1][1] * src_mat3.m[2][0] +
				src_mat3.m[0][1] * src_mat3.m[1][0] * src_mat3.m[2][2] +
				src_mat3.m[0][0] * src_mat3.m[1][2] * src_mat3.m[2][1]
				)
			);

	if (temp != 0)
	{
		float inv_temp = 1.0f / temp;

		float inv_m[3][3] =
		{
			{
				(src_mat3.m[1][1] * src_mat3.m[2][2]) - (src_mat3.m[1][2] * src_mat3.m[2][1]),
				-((src_mat3.m[0][1] * src_mat3.m[2][2]) - (src_mat3.m[0][2] * src_mat3.m[2][1])),
				(src_mat3.m[0][1] * src_mat3.m[1][2]) - (src_mat3.m[0][2] * src_mat3.m[1][1])
			},
			{
				-((src_mat3.m[1][0] * src_mat3.m[2][2]) - (src_mat3.m[1][2] * src_mat3.m[2][0])),
				(src_mat3.m[0][0] * src_mat3.m[2][2]) - (src_mat3.m[0][2] * src_mat3.m[2][0]),
				-((src_mat3.m[0][0] * src_mat3.m[1][2]) - (src_mat3.m[0][2] * src_mat3.m[1][0]))
			},
			{
				(src_mat3.m[1][0] * src_mat3.m[2][1]) - (src_mat3.m[1][1] * src_mat3.m[2][0]),
				-((src_mat3.m[0][0] * src_mat3.m[2][1]) - (src_mat3.m[0][1] * src_mat3.m[2][0])),
				(src_mat3.m[0][0] * src_mat3.m[1][1]) - (src_mat3.m[0][1] * src_mat3.m[1][0])
			},
		};

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				inv_m[i][j] *= inv_temp;
			}
		}

		memcpy(&src_mat3.m, inv_m, sizeof(inv_m));
	}

	return src_mat3;
}
