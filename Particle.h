#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class Particle {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Vector3 position, KamataEngine::Vector3 velocity);
	void Update();
	void Draw(KamataEngine::Camera& camera);

	// 色変更オブジェクト
	KamataEngine::ObjectColor objectColor_;
	// 色の数値
	KamataEngine::Vector4 color_;
	KamataEngine::Vector3 velocity_;

private:
	WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;

	uint32_t MOVE_Particle = false;
};