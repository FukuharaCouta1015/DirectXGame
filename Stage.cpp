#include "Stage.h"
using namespace KamataEngine;
using namespace MathUtility;

Stage::~Stage() {
	delete sprite_;
	delete sprite2_;
}

// 初期化
void Stage::Initialize(uint32_t TtextureHandle) {
	textureHandle_ = TtextureHandle;

	// スプライトインスタンスの生成
	sprite_ = KamataEngine::Sprite::Create(textureHandle_, {0, 0});
	sprite2_ = KamataEngine::Sprite::Create(textureHandle_, {1280, 0});
}

// 更新
void Stage::Update() {
	// 移動
	KamataEngine::Vector2 position = sprite_->GetPosition();
	position.x -= 2;
	if (position.x < -1280) {
		position.x += 1280;
	}
	sprite_->SetPosition(position);
	position.x += 1280;
	sprite2_->SetPosition(position);
}

// 描画
void Stage::Draw() {
	sprite_->Draw();
	sprite2_->Draw();
}