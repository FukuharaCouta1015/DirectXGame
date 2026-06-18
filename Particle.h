#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class Particle {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Vector3 position);
	void Update();
	void Draw(KamataEngine::Camera& camera);

	// 色変更オブジェクト
	KamataEngine::ObjectColor objectColor_;
	// 色の数値
	Vector4 color_;

private:
	WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;

	uint32_t MOVE_Particle = false;
};