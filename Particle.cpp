#include "Particle.h"
#include <algorithm>
#include <cassert>

using namespace KamataEngine;
using namespace MathUtility;

void Particle::Initialize(KamataEngine::Model* model, KamataEngine::Vector3 position, KamataEngine::Vector3 velocity) {
	assert(model);

	model_ = model;

	velocity_ = velocity;

	worldTransform_.Initialize();

	worldTransform_.translation_ = position;

	worldTransform_.scale_ = {0.5f, 0.5f, 0.5f};

	// 色の設定
	objectColor_.Initialize();
	color_ = {1, 1, 0, 1};
	// color_ = {0.352f, 0.060f, 0.014f, 1.0f};
}

void Particle::Update() {

	// 色変更オブジェクトに色の数値を設定する
	objectColor_.SetColor(color_);

	if (Input::GetInstance()->TriggerKey(DIK_M)) {
		MOVE_Particle = (MOVE_Particle == false);
	}

	if (MOVE_Particle) {
	}
	// 移動
	worldTransform_.translation_ += velocity_;

	// 終了なら何もしない
	if (isFinished_) {
		return;
	}
	// カウンターを1フレーム分の秒数進める
	counter_ += 1.0f / 60.0f;

	// 存続時間の上限に達したら
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		// 終了扱いにする
		isFinished_ = true;
	}

	color_.w = std::clamp(1.0f - counter_ / kDuration, 0.0f, 1.0f);

	// 行列の更新
	worldTransform_.UpdateMatrix();
}

void Particle::Draw(KamataEngine::Camera& camera) { model_->Draw(worldTransform_, camera, &objectColor_); }