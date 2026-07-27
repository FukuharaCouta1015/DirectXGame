#pragma once
#include "KamataEngine.h"

class DrawNumber {
public:
	// デストラクタ
	~DrawNumber();

	// 初期化
	void Initialize(uint32_t textureHandle);

	// 更新
	void Update(uint32_t number);

	// 描画
	void Draw();

private:
	// テクスチャー
	uint32_t textureHandle_;
	// スプライト
	KamataEngine::Sprite* sprite_[5] = {};
	// サイズ
	KamataEngine::Vector2 size = {32.0f, 64.0f};
};