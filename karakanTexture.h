#pragma once
#include <vector>
#include <string>

enum SpriteTag
{
	//------設定し忘れ-----
	kMissing,
	//-----テスト用--------
	kKinokoGH,			
	kTestLaserGH,
	kTestEnemyGH,
	k8BallGH,
	kArrowGH,
	kTestFrameGH,
	kTestHeartGH,
	kTestClockGH,
	kTestEnemiesGH,
	kTestNumbersGH,
	kTestHaritukeGH,
	kTestGaugeGH,
	kTestBulletGH,
	kTestPlayUIGH,
	kTestOptionUIGH,
	kTestExitUIGH,

	//-------キャラ--------

	//-------マップ--------

	//-------UI------------
	

	//-------背景----------

};

struct Texture
{
	//GraphHandle
	int GH = 0;
	SpriteTag sprTag = kMissing;
	//スプライトの画像サイズ
	float spriteWidth = 0;
	float spriteHeight = 0;
	//スプライトシート切り替える用
	int spriteNum = 0;
	//Texture operator=(Texture src_texture);

};

int const textureSum = 30;

extern Texture global_textureInfos[textureSum];
