#include "Bullet.h"

using namespace KamataEngine;

// 初期化
void Bullet::Initialize(Model* model, const Vector3& position) {

	model_ = model;

	worldTransform_.Initialize();

	// プレイヤーの位置から発射
	worldTransform_.translation_ = position;

	// 弾を小さくする
	worldTransform_.scale_ = {0.3f, 0.3f, 0.3f};

	worldTransform_.UpdateMatrix();
}

// 更新
void Bullet::Update() {

	// 右方向へ飛ばす
	worldTransform_.translation_.x += speed_;

	// 生存時間
	lifeTime_++;

	// 120フレーム経ったら消す
	if (lifeTime_ >= 120) {
		isDead_ = true;
	}

	worldTransform_.UpdateMatrix();
}

// 描画
void Bullet::Draw(Camera& camera) { model_->Draw(worldTransform_, camera); }