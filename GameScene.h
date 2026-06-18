#pragma once
#include "Effect.h"
#include "KamataEngine.h"
#include "Model2.h"

#include <list>

#include "Particle.h"

using namespace KamataEngine;

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

	// パーティクル
	Particle* particle_ = nullptr;

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

#pragma region エフェクト

	KamataEngine::Model* modelEffect_ = nullptr;
	// エフェクト一覧
	std::list<Effect*> effects_;

	uint32_t OFF_Effect = true;
	uint32_t ON_Effect = false;

#pragma endregion

	// パーティクル3Dモデルデータ
	KamataEngine::Model* modelParticle_ = nullptr;
	// std::list<Particle*> particles_;

	uint32_t OFF_Particle = true;
	uint32_t ON_Particle = false;
};