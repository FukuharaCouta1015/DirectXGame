#include "Player.h"

using namespace KamataEngine;
using namespace MathUtility;

// 初期化
void Player::Initialize(Model* model) {
	model_ = model;
	worldTransform_.scale_ = {3.0f, 3.0f, 3.0f};
	worldTransform_.Initialize();
	// 初期回転
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
	worldTransform_.translation_ = {-12.0f, -5.0f, 0};

}

// 更新
void Player::Update() {
	// 移動入力
	if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_D)) {
		worldTransform_.translation_.x += 0.1f;
	}
	if (Input::GetInstance()->PushKey(DIK_LEFT) || Input::GetInstance()->PushKey(DIK_A)) {
		worldTransform_.translation_.x -= 0.1f;
	}
	if (Input::GetInstance()->PushKey(DIK_UP) || Input::GetInstance()->PushKey(DIK_W)) {
		worldTransform_.translation_.y += 0.1f;
	}
	if (Input::GetInstance()->PushKey(DIK_DOWN) || Input::GetInstance()->PushKey(DIK_S)) {
		worldTransform_.translation_.y -= 0.1f;
	}

	// 範囲制限
	if (worldTransform_.translation_.x > 8.0f) {
		worldTransform_.translation_.x = 8.0f;
	}
	if (worldTransform_.translation_.x < -14.0f) {
		worldTransform_.translation_.x = -14.0f;
	}
	if (worldTransform_.translation_.y > 8.0f) {
		worldTransform_.translation_.y = 8.0f;
	}
	if (worldTransform_.translation_.y < -8.0f) {
		worldTransform_.translation_.y = -8.0f;
	}

	worldTransform_.UpdateMatrix();
}

// 描画
void Player::Draw(Camera& camera) { model_->Draw(worldTransform_, camera); }