#pragma once
#include "Bullet.h"
#include "KamataEngine.h"

#include <list>
#include <numbers>

class Player {
public:
	// 初期化
	void Initialize(KamataEngine::Model* model);

	// 弾モデル設定
	void SetBulletModel(KamataEngine::Model* model);

	// 更新
	void Update();

	// 描画
	void Draw(KamataEngine::Camera& camera);

	// 弾と敵の当たり判定
	bool CheckBulletCollision(const KamataEngine::Vector3& enemyPosition);

private:
	// モデル
	KamataEngine::Model* model_ = nullptr;

	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

	// テクスチャー
	uint32_t textureHandle_;

	// 弾のモデル
	KamataEngine::Model* bulletModel_ = nullptr;

	// 弾のリスト
	std::list<Bullet*> bullets_;

	// 弾を撃つ間隔
	int shotTimer_ = 0;

	// 連射間隔
	static const int kShotInterval = 10;
};