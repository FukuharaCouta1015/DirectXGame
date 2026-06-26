#include "Particle.h"
#include <cassert>
using namespace MathUtility;

void Particle::Initialize(KamataEngine::Model* model, KamataEngine::Vector3 position) {
	assert(model);

	model_ = model;

	worldTransform_.Initialize();

	worldTransform_.translation_ = position;

	// 色の設定
	objectColor_.Initialize();
	color_ = {1, 1, 0, 1};
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
	worldTransform_.translation_ += {0.0f, 0.1f, 0.0f};

	// 行列の更新
	worldTransform_.UpdateMatrix();
}

void Particle::Draw(KamataEngine::Camera& camera) { model_->Draw(worldTransform_, camera, &objectColor_); }