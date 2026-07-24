#pragma once
#include "KamataEngine.h"
#include <numbers>

class Player {
public:
	// 初期化
	void Initialize(KamataEngine::Model* model);

	// 更新
	void Update();

	// 描画
	void Draw(KamataEngine::Camera& camera);

private:
	// モデル
	KamataEngine::Model* model_ = nullptr;
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;
	// テクスチャー
	uint32_t textureHandle_;
};