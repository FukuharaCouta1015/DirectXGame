#pragma once

#include "KamataEngine.h"

class Bullet {
public:
	// 初期化
	void Initialize(KamataEngine::Model* model, const KamataEngine::Vector3& position);

	// 更新
	void Update();

	// 描画
	void Draw(KamataEngine::Camera& camera);

	// 消滅しているか
	bool IsDead() const { return isDead_; }

private:
	// モデル
	KamataEngine::Model* model_ = nullptr;

	// ワールド変換
	KamataEngine::WorldTransform worldTransform_;

	// 消滅フラグ
	bool isDead_ = false;

	// 弾の速度
	float speed_ = 0.5f;

	// 生存時間
	int lifeTime_ = 0;
};