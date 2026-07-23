#pragma once
#include "KamataEngine.h"
class Stage {
public:
	// デストラクタ
	~Stage();

	// 初期化
	void Initialize(uint32_t TtextureHandle);

	// 更新
	void Update();

	// 描画
	void Draw();

private:
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// スプライト
	KamataEngine::Sprite* sprite_ = nullptr;
	KamataEngine::Sprite* sprite2_ = nullptr;
};