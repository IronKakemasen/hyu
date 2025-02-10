#pragma once

#include "VectorMatrix.h"
#include "GlovalEnum.h"
#include <Novice.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <string> 
#include "karakanTexture.h"
\
#if defined(_DEBUG)
#include <imgui.h>
#endif

using namespace std;

struct Scene;
struct Player;
struct Enemy;
struct Camera;

//pi
static float const kPi = 3.1415926535f;
//ウィンドウサイズ
static constexpr float kWindowWidth = 1280.0f;
static constexpr float kWindowHeight = 720.0f;
static Vector3 kZeroVec = { 0,0,1 };

//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------
struct PhysicalElements2D
{
	Vector3 velocity = {};										//軸ごとの速度
	Vector3 acceleration = {};									//加速度
	inline static float cor = 0.8f;								//反発係数(もう全部共通で)
	float mass = 1.0f;											//質量
	bool isGrounded = false;									//接地判定。重力を発生させるかどうか。
	inline static float frictionCor = 0.5f;						//動摩擦係数
	inline static float gravity = 0.9f;							//重力
	static float constexpr kAriResistance = 0.00001f;			//空気抵抗係数



	void Initialize(float ini_cor, float ini_mass);
	void Clear();
};
//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------
struct Transform
{
	//行列	
	Matrix3x3 mat;									
	//ベクター
	Vector3 local_pos;								//ローカル座標
	Vector3 pos;									//ワールド座標用
	Vector3 pre_pos;								//前フレームの座標保管用
	Vector3 buff_pos = { 0,0,1 };					//バッファー
	Vector3 scale = { 1.0f, 1.0f ,1.0f };			//スケール
	Vector3 direction{ 1.0f, 1.0f ,1.0f };			//方向
	Vector3 pre_dir = direction;
	//速さ
	float moveSpeed = 0;
	//回転用シータ
	float rotateTheta = 0.0f;
	//移動用シータ
	float movementTheta = 0.0f;

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	Matrix3x3 GetAffineMatrix3x3(MatrixType matType);

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
};
//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------
struct Appearance
{
	//グローバル変数、texturesInfoから値をもらう
	Texture texture;
	//カラー
	Vector4 kOriginal_color = { 255,255,255,200 };							//オリジナルカラー保管用			
	Vector4 current_color = kOriginal_color;								//現在のカラー
	BlendMode blendMode = kBlendModeNormal;								//ブレンドモード

	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	//初期化
	void Initialize(SpriteTag dst_spriteTag,Vector4 ini_color,BlendMode ini_blendMode);
	//カラーをintに変換して取得する
	static int GetIntColor(Vector4 array_color);
	//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
};
//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------
struct RectShape
{
	//T = TOP , L = LEFT , B = BOTTOM , R = RIGHT
	Vector3 local_LT;
	Vector3 local_RT;
	Vector3 local_LB;
	Vector3 local_RB;

	Vector3 LT;
	Vector3 RT;
	Vector3 LB;
	Vector3 RB;
};
//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------
struct RectangleObject
{
	Transform trans;
	Appearance appear;
	//Vertex
	RectShape collisionRect;		//当たり判定用
	RectShape appearanceRect;		//見た目用
	RectShape preRect;				//前フレーム保存用

	bool isActive = true;
	//デバッグUIを表示するかどうか
	bool showIMGUI = false;
	//ローカル座標の設定
	void SetLocalVertex(RectShape &dstRect, float ini_width, float ini_height);
	//スプライトシートに対応したドロー関数
	void DrawRect(const Matrix3x3& VPVMat);
	//AABB当たり判定
	static bool ObjectAABB(RectangleObject* const obj1, RectangleObject* const obj2);
	//[矩形専用]４頂点を行列と計算する
	void SubstituteResultForVertexes(RectShape &dstRect);
};
//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------
struct ObjectBehavior
{
	virtual void Update(Scene& scene) = 0;
	virtual void Render(const Matrix3x3& VPVMat) = 0;
	virtual void Animation(Scene& scene) = 0;
	virtual void Initialize() = 0;
	virtual void TranslatePosition() = 0;

#ifdef _DEBUG
	virtual void ShowIMGUI() = 0;
#endif
};

struct GameObject :ObjectBehavior, RectangleObject, PhysicalElements2D
{
	float radius = 0.0f;
	RectangleObject heartImage;

	//オブジェクトの名前
	string name;
	//更新処理優先度
	int updatePriNo = 0;
	//描画処理優先度
	int renderPriNo = 0;
	//オブジェクトのタグ
	ObjectTag tag; 
	int max_HP = 10;
	int current_HP = max_HP;

	virtual void Update(Scene& scene) override { scene; };
	virtual void Render(const Matrix3x3& VPVMat) override { VPVMat; };
	virtual void Animation(Scene& scene) override { scene; };
	virtual void Initialize()override {};
	virtual void TranslatePosition()override;

	GameObject()
	{
		//ハートイメージの初期化
		heartImage.appear.Initialize(kTestHeartGH, { 255,0,0,255 }, kBlendModeNormal);
		heartImage.SetLocalVertex(heartImage.appearanceRect, 16, 16);
	}

#if defined(_DEBUG)
	bool showIMGUI = true;
	virtual void ShowIMGUI() override {};
#endif

};

inline bool operator==(GameObject* obj, ObjectTag objTag) { return obj->tag == objTag; }
//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------
//プレハブ
struct Prefab
{
	Player* player = nullptr;
	Enemy* enemies[9] = {};

};

//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------
struct GameManager
{
	static inline Phase current_Phase = Phase::kPlayerTurn;
	Phase next_phase = Phase::kPlayerTurn;
	Phase pre_phase= Phase::kPlayerTurn;
	int currentStep = 0;

	enum ReffernceType
	{
		kUpdate,
		kRender
	};

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	//ゲームオブジェクトのプレハブ
	Prefab prefab;
	std::vector<GameObject*>update_data;
	std::vector<GameObject*>render_data;
	bool isUpdating = false;

	//キー入力を受け取る
	bool GetKeyStatus(int dstKey, KeyStatus keyStatus);
	//オブジェクトをソートする
	void SortObject();

	//プレハブの状態をもとにインスタンス化しソートを行う
	template<typename T, typename = enable_if_t<is_base_of_v<GameObject, T>>>
	T* Instantiate2(T prefab,Vector3 start_pos)
	{
		T* ret = nullptr;

		if (!isUpdating)
		{
			decltype(prefab)* newObj = new decltype(prefab);
			*newObj = prefab;
			reinterpret_cast<GameObject*>(newObj)->trans.pos = start_pos;
			update_data.emplace_back(reinterpret_cast<GameObject*>(newObj));
			render_data.emplace_back(reinterpret_cast<GameObject*>(newObj));

			SortObject();

			ret = newObj;
		}

		return ret;
	}

};
//-------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------
inline float GetConvertedDegree(float theta) {
	static float const inv180 = 1.0f / 180.0f;
	return theta * kPi * inv180;
}

//線形補間
template<typename T>
inline T Lerp(const T& st, const T& end, float t) {
	return end * t + st * (1.0f - t);
}

//ラインを描画する
void DrawLine(Vector3 world_stPoint, Vector3 world_endPoint, Vector4 color, BlendMode mode, Matrix3x3 VPVpmat);
//ボックスを描画する
void DrawBox(Vector3 LTPoint, float width, float height, Vector4 color, FillMode mode, BlendMode blendMode,Matrix3x3 VPVpmat);
//円を描画する
void DrawEllipse(Vector3 center, float radiusX, float radiusY, Vector4 color, FillMode mode, BlendMode blendMode, Matrix3x3 VPVpmat);
//うぅつらい
void DrawQuad(Vector3 LTPoint, Vector3 RTPoint, Vector3 LBPoint, Vector3 RBPoint, int GH, float width, float height,
	Vector4 color, BlendMode blendMode, Matrix3x3 VPVpmat);
	//スクリーン座標からワールドへ変換
Vector3 ConvertScreenToWorld(Vector3 dst_Vector3, const Matrix3x3 viewMat, const Matrix3x3 projectionMat, const Matrix3x3 viewport);
//引数が0か正か負か調べる
template<typename T>
int GetSign(T num) {
	return int((num > 0) - (num < 0));
}
//点と矩形の当たり判定
bool VoidTyan(Vector3 dst_pos, RectShape dst_collRect);
//円と円の当たり判定
bool CircleCollisionDetection(Vector3 p1, float r1, Vector3 p2, float r2);