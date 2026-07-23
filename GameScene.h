#pragma once
#include "KamataEngine.h"

#include "Fade.h"
#include <list>

#include "Model2.h"

#include "Effect.h"
#include "Particle.h"

#include "Stage.h"

class Game {
public:
	void Initialize();
	void Update();
	void Draw();
	~Game();

#pragma region ゲームの状態管理

	bool gameActive = true;

	// 終了フラグ
	bool finishedGAME_ = false;
	// デス(オーバー)フラグのgetter
	bool IsFinishedGAME() const { return finishedGAME_; } // ゲームオーバー

	// 敵を倒した場合の(クリア)フラグ
	bool finishedGAME2_ = false;
	bool IsFinishedGAME2() const { return finishedGAME2_; } ////ゲームクリア

	// タイトルに戻る
	bool finishedGAME3_ = false;
	bool IsFinishedGAME3() const { return finishedGAME3_; } ////ゲームクリア

#pragma endregion

#pragma region 3Dモデルデータ

	// KamataEngine::Model* model_ = nullptr;

	KamataEngine::Model2* model2_ = nullptr;

	KamataEngine::Model2* model2_2_ = nullptr;

	KamataEngine::Model2* model2_3_ = nullptr;

	KamataEngine::Model2* model2_ring_ = nullptr;

#pragma endregion

	// エフェクト生成
	void EffectBorn(KamataEngine::Vector3 position);

	// パーティクル
	Particle* particle_ = nullptr;
	void ParticleBorn(KamataEngine::Vector3 position);
	uint32_t textureHandle_Circle_ = 0;

	// デバッグカメラ
	bool isDebugCameraActive_ = false;
	KamataEngine::DebugCamera* debugCamera_ = nullptr;

private:
	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// カメラ
	KamataEngine::Camera camera_;

#pragma region エフェクト

	KamataEngine::Model* modelEffect_ = nullptr;
	// エフェクト一覧
	std::list<Effect*> effects_;

	uint32_t OFF_Effect = true;
	uint32_t ON_Effect = false;

#pragma endregion

#pragma region パーティクル

	// パーティクル3Dモデルデータ
	KamataEngine::Model* modelParticle_ = nullptr;
	std::list<Particle*> particles_;

	uint32_t OFF_Particle = true;
	uint32_t ON_Particle = false;

#pragma endregion

#pragma region ポーズ画面

	// ESC
	uint32_t ESC_Handle_ = 0;
	KamataEngine::Sprite* ESC_Sprite_ = nullptr;

	// ESC
	uint32_t ESC_Handle_2 = 0;
	KamataEngine::Sprite* ESC_Sprite_2 = nullptr;

	// ポーズ画面時のUI
	uint32_t PoseUI_Handle_ = 0;
	KamataEngine::Sprite* PoseUI_Sprite_ = nullptr;

	uint32_t PoseUI_Handle_2 = 0;
	KamataEngine::Sprite* PoseUI_Sprite_2 = nullptr;

	uint32_t PoseUI2_Handle_ = 0;
	KamataEngine::Sprite* PoseUI2_Sprite_ = nullptr;

	uint32_t PoseUI2_Handle_2 = 0;
	KamataEngine::Sprite* PoseUI2_Sprite_2 = nullptr;

#pragma endregion

	// テクスチャハンドル
	uint32_t textureHandleStage_ = 0;
	// クラス
	Stage* stage_ = nullptr;

#pragma region フェーズ・フェード

	// ゲームのフェーズ(型)
	enum class Phase {
		kFadeIn, // フェードイン
		kPlay,   // ゲームプレイ
		kPose,
		kDeath,      // プレイヤーのデス演出
		kEnemyDeath, // 敵のデス演出
		kFadeOut,    // フェードアウト(オーバー)
		kFadeOut2,   // フェードアウト(クリア)
		kFadeOut3,   // フェードアウト(タイトルに戻る)
	};

	// ゲームの現在フェーズから開始
	Phase phase_;

	// フェーズの切り替え
	// void ChangePhase();

	// フェード
	Fade* fade_ = nullptr;
#pragma endregion
};