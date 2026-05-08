#pragma once
#include "KamataEngine.h"
#include "Model2.h"

class Game {
public:
	void Initialize();
	void Update();
	void Draw();
	~Game();

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;

	// カメラ
	KamataEngine::Camera camera_;

	// 3Dモデルデータ
	// KamataEngine::Model* model_ = nullptr;

	KamataEngine::Model2* model2_ = nullptr;

	KamataEngine::Model2* model2_2_ = nullptr;

	KamataEngine::Model2* model2_3_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

private:
};