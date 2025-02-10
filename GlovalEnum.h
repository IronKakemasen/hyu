#pragma once

//マップチップの状態
enum ChipStatus
{
	kPlayerCanMove,
	kNormal
};

//マトリックスの処理切り替え用
enum MatrixType
{
	kT,
	kSRT,
	kSTR
};


//プレイシーンの状態
enum class Phase
{
	kStart,
	kPlayerTurn,
	kEnemyTurn,
	kResult,
	kReset,
	kCount
};

//色
enum PrimaryColor
{
	kR,
	kG,
	kB,
	kA
};
//キーの入力ステータス
enum KeyStatus
{
	kPushed,
	kPushing,
	kReleased,
};

//ゲームオブジェクトのタグ
enum ObjectTag
{
	kPlayer,
	kEnemy1,
	kEnemy2,
	kEnemy3,
	kEnemy4,
	kEnemy5,
	kEnemy6,
	kEnemy7,
	kEnemy8,
	kEnemy9,


	kCount
};

enum DrawMode
{
	kWorld,
	kScreen
};


