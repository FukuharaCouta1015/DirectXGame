#include "Model2.h"
using namespace KamataEngine;
using namespace MathUtility;

#include "cassert"
#include <algorithm>
#include <numbers>
#define NOMINMAX


void Model2::Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera) {
	// NULLポインタチェック
	assert(model);

	// 引数の内容をメンバ変数に記録
	camera_ = camera;

	model_ = model;

	textureHandle_ = textureHandle;

	worldTransform_.Initialize();
}

void Model2::Update() {
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Model2::Draw() { model_->Draw(worldTransform_, *camera_, textureHandle_); }