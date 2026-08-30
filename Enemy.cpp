#include "Enemy.h"
#include <numbers>
using namespace KamataEngine;

// 初期化
void Enemy::Initialize(Model* model, const Vector3& position) {

	model_ = model;

	worldTransform_.Initialize();

	// 敵の向き
	worldTransform_.rotation_.y = -std::numbers::pi_v<float> / 2.0f;

	// 初期位置
	worldTransform_.translation_ = position;

	
	worldTransform_.scale_ = {2.0f, 2.0f, 2.0f};

	worldTransform_.UpdateMatrix();
}

// 更新
void Enemy::Update() {

	// 左方向へ移動
	worldTransform_.translation_.x -= speed_;

	// 画面左側まで行ったら消す
	if (worldTransform_.translation_.x < -40.0f) {
		isDead_ = true;
	}

	worldTransform_.UpdateMatrix();
}

// 描画
void Enemy::Draw(Camera& camera) { model_->Draw(worldTransform_, camera); }