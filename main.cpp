#include <Novice.h>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "BaseClass.h"
#include "Camera.h"
#include"Scene.h"

const char kWindowTitle[] = "Title";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Player p;
	Enemy e[10];
	Bullet bs[10];
	p.b = bs;

	Camera c;

	SceneBehavior* current = new Title;
	


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(current->preKeys, current->keys, 256);
		Novice::GetHitKeyStateAll(current->keys);

		current->Update();


		for (int i = 0; i < 2; ++i)
		{
			if (current->changeScene[i])
			{
				current->changeScene[i] = false;
				delete current;

				switch (i)
				{
				case 0:

					current = new Title;

					break;
				case 1:

					current = new InGame;
					reinterpret_cast<InGame*>(current)->p = &p;
					reinterpret_cast<InGame*>(current)->c= &c;
					reinterpret_cast<InGame*>(current)->e = &e[0];

					break;
				}

				current->Initiaize();

				break;
			}
		}





		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (current->preKeys[DIK_ESCAPE] == 0 && current->keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
