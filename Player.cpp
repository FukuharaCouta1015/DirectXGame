#include "Player.h"

using namespace KamataEngine;
using namespace MathUtility;

// 初期化
void Player::Initialize(Model* model) {

	model_ = model;

	worldTransform_.Initialize();

	// プレイヤーの大きさ
	worldTransform_.scale_ = {3.0f, 3.0f, 3.0f};

	// 初期回転
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

	// 初期位置
	worldTransform_.translation_ = {-12.0f, -5.0f, 0.0f};
}

// 弾モデル設定
void Player::SetBulletModel(Model* model) { bulletModel_ = model; }

// 更新
void Player::Update() {

	// =========================
	// 移動入力
	// =========================

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

	// =========================
	// 範囲制限
	// =========================

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

	// =========================
	// 弾を発射
	// =========================

	if (Input::GetInstance()->PushKey(DIK_SPACE)) {

		// 発射タイマーを進める
		shotTimer_++;

		// 一定時間ごとに発射
		if (shotTimer_ >= kShotInterval) {

			// タイマーをリセット
			shotTimer_ = 0;

			// 弾モデルが存在する場合
			if (bulletModel_) {

				// 弾を生成
				Bullet* bullet = new Bullet();

				// プレイヤーの位置から発射
				bullet->Initialize(bulletModel_, worldTransform_.translation_);

				// 弾リストに追加
				bullets_.push_back(bullet);
			}
		}

	} else {

		// スペースを離したらタイマーをリセット
		shotTimer_ = 0;
	}

	// =========================
	// 弾の更新
	// =========================

	for (auto bullet = bullets_.begin(); bullet != bullets_.end();) {

		// 弾を更新
		(*bullet)->Update();

		// 弾が消滅したら
		if ((*bullet)->IsDead()) {

			delete *bullet;

			bullet = bullets_.erase(bullet);

		} else {

			++bullet;
		}
	}

	// =========================
	// プレイヤーの行列更新
	// =========================

	worldTransform_.UpdateMatrix();
}

// 描画
void Player::Draw(Camera& camera) {

	// プレイヤー描画
	model_->Draw(worldTransform_, camera);

	// 弾描画
	for (Bullet* bullet : bullets_) {

		bullet->Draw(camera);
	}
}

bool Player::CheckBulletCollision(const Vector3& enemyPosition) {

	for (Bullet* bullet : bullets_) {

		// 弾の位置
		Vector3 bulletPosition = bullet->GetPosition();

		// X方向の距離
		float dx = bulletPosition.x - enemyPosition.x;

		// Y方向の距離
		float dy = bulletPosition.y - enemyPosition.y;

		// 距離
		float distance = std::sqrt(dx * dx + dy * dy);

		// 一定距離以内なら当たった
		if (distance < 1.0f) {

			// 弾を消す
			bullet->SetDead();

			return true;
		}
	}

	return false;
}