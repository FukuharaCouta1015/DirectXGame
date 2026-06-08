#pragma once
#include "Effect.h"
#include "KamataEngine.h"
#include "Model2.h"

#include <list>

class Game {
public:
	void Initialize();
	void Update();
	void Draw();
	~Game();

	uint32_t textureHandle_Circle_ = 0;

	// 3Dモデルデータ

	// KamataEngine::Model* model_ = nullptr;

	KamataEngine::Model2* model2_ = nullptr;

	KamataEngine::Model2* model2_2_ = nullptr;

	KamataEngine::Model2* model2_3_ = nullptr;

	KamataEngine::Model2* model2_ring_ = nullptr;

	// エフェクト生成
	void EffectBorn(KamataEngine::Vector3 position);

	// デバッグカメラ
	bool isDebugCameraActive_ = false;
	KamataEngine::DebugCamera* debugCamera_ = nullptr;

private:
	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// カメラ
	KamataEngine::Camera camera_;

	KamataEngine::Model* modelEffect_ = nullptr;
	// エフェクト一覧
	std::list<Effect*> effects_;
};