#pragma once
#include "Model2.h"
#include "KamataEngine.h"


class Effect {
public:
	void Initialize(KamataEngine::Model* model, float rotate, float size, KamataEngine::Vector3 position, KamataEngine::Vector3 color);

	void Update();

	void Draw(KamataEngine::Camera& camera);

	bool IsFinished() const { return isFinished_; }

private:
	// 存続時間
	const float kDuration = 1.0f;

	// 経過時間
	float counter_ = 0.0f;

	// 終了フラグ
	bool isFinished_ = false;

	// モデル
	KamataEngine::Model* model_ = nullptr;

	// ワールド変換
	KamataEngine::WorldTransform worldTransform_;

	// 色変更
	KamataEngine::ObjectColor objectColor_;

	// RGBAカラー
	KamataEngine::Vector4 color_ = {1, 1, 1, 1};
};