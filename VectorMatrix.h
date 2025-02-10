#pragma once

struct Vector3
{
	float x = 0;
	float y = 0;
	float w = 1;
	float magnitude = 0.0f;

	void SetMagnitutde();
	Vector3 GetNormalizedVec();
	Vector3 operator+=(float const addNum);
	Vector3 operator=(float const num);

	static Vector3 Lerp(Vector3 st, Vector3 end, float dt);
	static Vector3 Catmull(Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3, float t);
	//二つのベクトルの外積からsin(🍆角)を求めて返す関数
	static float GetSinThetaFromTwoVector3(Vector3 src1_vec3, Vector3 src2_vec3);
	//二つのベクトルの内積からcos(🍆角)を求めて返す関数
	static float GetCosThetaFromTwoVector3(Vector3 src1_vec3, Vector3 src2_vec3);
	//引数の２点の座標から、my_posからdst_pos方向への単位ベクトルを計算し返す関数
	static Vector3 GetNormalizedVector3BetweenTwo(Vector3 my_pos, Vector3 dst_pos);

};
struct Vector4
{
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 1;

};

struct Matrix3x3
{
	float m[3][3] = {};
	static Vector3 GetProductReultOfVectorAndMatrix(Vector3 dest_Vector3, Matrix3x3 src_mat);
	static Matrix3x3 GetProductReultOfMatrixes(Matrix3x3* const kSrc_mat1, Matrix3x3* const kSrc_mat2);
	static Matrix3x3 GetInversedMat3(Matrix3x3 src_mat3);
};


Vector3 operator+(Vector3 const& vec1, Vector3  const& vec2);
Vector3 operator-(Vector3 const& vec1, Vector3  const& vec2);
Vector3 operator*(Vector3  const& vec1, float const multipleNum);

