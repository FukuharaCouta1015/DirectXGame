#include "KamataEngine.h"
#include <Windows.h>
using namespace KamataEngine;

#include "GameScene.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	// エンジンの初期化
	KamataEngine::Initialize(L"LE3D_21_フクハラ_コウタ");

	// DirectXCommonインスタンスを取得す
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// ゲームのインスタンス生成
	Game* game = new Game();
	// ゲームの初期化
	game->Initialize();

	// メインループ
	while (true) {
		// エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}

		game->Update();

#pragma region 描画

		// 描画開始
		dxCommon->PreDraw();

		game->Draw();

		// 描画終了
		dxCommon->PostDraw();

#pragma endregion
	}

#pragma region 解放

	delete game;
	game = nullptr;

#pragma endregion

	// エンジンの終了処理
	KamataEngine::Finalize();

	return 0;
}