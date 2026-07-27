#include "GameScene.h"
#include <random>
#include <ctime>
#include <cstdlib>

using namespace KamataEngine;
using namespace MathUtility;

std::random_device seedGenerator;
std::mt19937 randomEngine(seedGenerator());
std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

void Game::Initialize() {
	// デバッグカメラ生成
	debugCamera_ = new DebugCamera(1280, 720);

#pragma region フェーズ・フェード
	// フェーズインから開始
	phase_ = Phase::kFadeIn;
	// フェード
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 1.0f);
#pragma endregion

#pragma region 背景スクロール
	// ファイル名を指定してテクスチャを読み込む
	textureHandleStage_ = TextureManager::Load("Scenes/stage.png");
	stage_ = new Stage();
	stage_->Initialize(textureHandleStage_);
#pragma endregion

#pragma region プレイヤー

	modelPlayer_ = Model::CreateFromOBJ("player");
	player_ = new Player();
	player_->Initialize(modelPlayer_);

	textureHandleGraph_ = TextureManager::Load("white1x1.png");
	graphBar_ = new GraphBar();
	graphBar_->Initialize(textureHandleGraph_);

#pragma endregion

#pragma region スコア表示
	textureHandleNumber_ = TextureManager::Load("UI/number.png");
	drawNumber_ = new DrawNumber();
	drawNumber_->Initialize(textureHandleNumber_);
#pragma endregion

#pragma region UI

	// ESCのスプライト
	ESC_Handle_ = TextureManager::Load("UI/ESC.png");
	ESC_Sprite_ = KamataEngine::Sprite::Create(ESC_Handle_, {10, 100});

	ESC_Handle_2 = TextureManager::Load("UI/Pushed_ESC.png");
	ESC_Sprite_2 = KamataEngine::Sprite::Create(ESC_Handle_2, {10, 100});

	PoseUI_Handle_ = TextureManager::Load("UI/Pose_UI.png");
	PoseUI_Sprite_ = KamataEngine::Sprite::Create(PoseUI_Handle_, {448, 164});

	PoseUI_Handle_2 = TextureManager::Load("UI/Pushed_Pose_UI.png");
	PoseUI_Sprite_2 = KamataEngine::Sprite::Create(PoseUI_Handle_2, {448, 164});

	PoseUI2_Handle_ = TextureManager::Load("UI/Pose_UI_2.png");
	PoseUI2_Sprite_ = KamataEngine::Sprite::Create(PoseUI2_Handle_, {448, 364});

	PoseUI2_Handle_2 = TextureManager::Load("UI/Pushed_Pose_UI_2.png");
	PoseUI2_Sprite_2 = KamataEngine::Sprite::Create(PoseUI2_Handle_2, {448, 364});

#pragma endregion

#pragma region 四角形_リング
	// model_ = Model::Create();

	Model2::StaticInitialize();
	model2_ = Model2::Create();
	model2_ = Model2::CreateSquare();

	// model2_2_ = Model2::CreateSquare2();

	// model2_3_ = Model2::CreateSquare3();

	// model2_ring_ = Model2::CreateRing(5.0f, 10.0f, 8);

#pragma endregion

#pragma region エフェクト

	// 乱数の初期化
	srand((unsigned)time(NULL));

	// 3Dモデルデータ生成
	modelEffect_ = Model::CreateFromOBJ("plane");

	// 最初のエフェクト生成
	KamataEngine::Vector3 position = {0.0f, 0.0f, 0.0f};
	EffectBorn(position);

#pragma endregion

#pragma region パーティクル

	// 乱数の初期化
	srand((unsigned)time(NULL));

#pragma endregion
	// 効果音ラボ/生活[3]スポーツ・その他/おなら
	// f_h = Audio::GetInstance()->LoadWave("Sounds/sound/Fart.mp3");

#pragma region テクスチャ

	textureHandle_ = TextureManager::Load("uvChecker.png");
	// textureHandle_ = TextureManager::Load("white1x1.png");

#pragma endregion

	worldTransform_.Initialize();
	camera_.Initialize();
}

void Game::Update() {

#pragma region デバッグカメラ
	debugCamera_->Update();

#ifdef _DEBUG
	if (Input::GetInstance()->TriggerKey(DIK_0)) {
		isDebugCameraActive_ = !isDebugCameraActive_;
	}

#endif // DEBUG
	// ChangePhase();
	if (isDebugCameraActive_) {
		debugCamera_->Update();
		camera_.matView = debugCamera_->GetCamera().matView;
		camera_.matProjection = debugCamera_->GetCamera().matProjection;
		camera_.TransferMatrix();
	} else {
		camera_.TransferMatrix();
		camera_.UpdateMatrix();
	}
#pragma endregion

	if (gameActive) {
		stage_->Update();

		player_->Update();
		graphBar_->Update(hp_);
		hp_--;
		if (hp_ < 0) {
			hp_ = 200u;
		}

		gameScore_++;
		drawNumber_->Update(gameScore_);

#pragma region エフェクト

		// エフェクト発生
		if (rand() % 5 == 0) {
			Vector3 position = {distribution(randomEngine), distribution(randomEngine), 0};
			position *= 10;
			EffectBorn(position);
		}

		// エフェクト更新
		// effect_->Update();
		for (Effect* effect : effects_) {
			effect->Update();
		}

		// デスフラグの立ったエフェクトを削除
		effects_.remove_if([](Effect* effect) {
			if (effect->IsFinished()) {
				delete effect;
				return true;
			}
			return false;
		});

#pragma endregion

#pragma region パーティクル

		if (rand() % 20 == 0) {
			KamataEngine::Vector3 P_position = {distribution(randomEngine) * 30.0f, distribution(randomEngine) * 20.0f, 0};
			ParticleBorn(P_position);
		}

		for (Particle* particle : particles_) {
			particle->Update();
		}

		particles_.remove_if([](Particle* particle_) {
			if (particle_->isFinished()) {
				delete particle_;
				return true;
			}
			return false;
		});

#pragma endregion
	}

	switch (phase_) {
	case Phase::kPlay: {

#pragma region 仮設コード

		/**/
		// ゲームクリア(仮)
		if (Input::GetInstance()->TriggerKey(DIK_C)) {
			phase_ = Phase::kEnemyDeath;
		}
		// ゲームオーバー(仮)
		if (Input::GetInstance()->TriggerKey(DIK_O)) {
			phase_ = Phase::kDeath;
		}

#pragma endregion

		if (Input::GetInstance()->TriggerKey(DIK_ESCAPE)) {
			phase_ = Phase::kPose;
		}

		break;
	}

	case Phase::kPose: {

		gameActive = false;
		if (Input::GetInstance()->TriggerKey(DIK_ESCAPE)) {
			phase_ = Phase::kPlay;
			gameActive = true;
		}
		if (Input::GetInstance()->TriggerKey(DIK_T)) {
			phase_ = Phase::kFadeOut3;
		}
		break;
	}

	case Phase::kDeath: {
		// フェードアウト開始
		phase_ = Phase::kFadeOut;
		fade_->Start(Fade::Status::FadeOut, 1.0f);

		break;
	}

	case Phase::kEnemyDeath: {
		// フェードアウト開始
		phase_ = Phase::kFadeOut2;
		fade_->Start(Fade::Status::FadeOut, 1.0f);

		break;
	}
	case Phase::kFadeIn: {
		// フェード
		fade_->Update();
		if (fade_->IsFinished()) {
			phase_ = Phase::kPlay;
		}
		break;
	}
	case Phase::kFadeOut: {
		// フェード
		fade_->Update();
		if (fade_->IsFinished()) {
			finishedGAME_ = true;
		}
		break;
	}
	case Phase::kFadeOut2: {
		// フェード
		fade_->Update();
		if (fade_->IsFinished()) {
			finishedGAME2_ = true;
		}
		break;
	}
	case Phase::kFadeOut3: {
		// フェード
		fade_->Update();
		if (fade_->IsFinished()) {
			finishedGAME3_ = true;
		}
		break;
	}
	}
}

void Game::Draw() {
	ID3D12GraphicsCommandList* commandList = DirectXCommon::GetInstance()->GetCommandList();
	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

#pragma region スプライト(背景)

	Sprite::PreDraw(dxCommon->GetCommandList());

	stage_->Draw();

	Sprite::PostDraw();

	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();

#pragma endregion

#pragma region モデル

	Model::PreDraw();

	// ここに3Dモデルインスタンスの描画処理を記述する
	player_->Draw(camera_);

#pragma region エフェクト描画

	if (Input::GetInstance()->TriggerKey(DIK_E)) {
		ON_Effect = (ON_Effect == false);
		OFF_Effect = (ON_Effect == false);
	}
	if (ON_Effect) {
		/*
		// エフェクト描画
		for (Effect* effect : effects_)
		{
		    effect->Draw(camera_);
		}*/
	}

#pragma endregion

#pragma region パーティクルの描画
	if (Input::GetInstance()->TriggerKey(DIK_P)) {
		ON_Particle = (ON_Particle == false);
		OFF_Particle = (ON_Particle == false);
	}
	if (ON_Particle) {
	}
	/*
	for (Particle* particle : particles_)
	{
	    particle->Draw(camera_);
	}*/

#pragma endregion

	Model::PostDraw();

#pragma endregion

#pragma region モデル2
	Model2::PreDraw(commandList);

	// model2_->Draw(worldTransform_, camera_, textureHandle_Circle_);

	// model2_2_->Draw(worldTransform_, camera_, textureHandle_);

	// model2_3_->Draw(worldTransform_, camera_, textureHandle_);

	// model2_ring_->Draw(worldTransform_, camera_, textureHandle_);

	Model2::PostDraw();
#pragma endregion

#pragma region スプライト(UI)

	// スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	graphBar_->Draw();
	drawNumber_->Draw();

#pragma region UI
	if (phase_ == Phase::kPlay || phase_ == Phase::kFadeIn || phase_ == Phase::kPose || phase_ == Phase::kDeath || phase_ == Phase::kEnemyDeath) {
		ESC_Sprite_->Draw();

		if (Input::GetInstance()->PushKey(DIK_ESCAPE)) {
			ESC_Sprite_2->Draw();
		}
	}

	// ポーズ画面
	if (phase_ == Phase::kPose) {
		PoseUI_Sprite_->Draw();
		PoseUI2_Sprite_->Draw();

		if (Input::GetInstance()->PushKey(DIK_ESCAPE)) {
			PoseUI_Sprite_2->Draw();
		}

		if (Input::GetInstance()->PushKey(DIK_T)) {
			PoseUI2_Sprite_2->Draw();
		}
	}

#pragma endregion

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

// エフェクト発生
void Game::EffectBorn(Vector3 position) {
	Vector3 color = {abs(distribution(randomEngine)), abs(distribution(randomEngine)), abs(distribution(randomEngine))};
	for (int32_t i = 0; i < 15; i++) {
		Effect* effect = new Effect();
		float rotate = distribution(randomEngine) * 3.14f;
		float size = 1.0f + abs(distribution(randomEngine)) * 4;
		effect->Initialize(modelEffect_, rotate, size, position, color);
		effects_.push_back(effect);
	}
}

// パーティクル発生
void Game::ParticleBorn(KamataEngine::Vector3 position) {

	modelParticle_ = KamataEngine::Model::CreateSphere(4, 4);

	for (int i = 0; i < 150; i++) {
		particle_ = new Particle();
		KamataEngine::Vector3 P_position = {0.0f * i, 0.0f, 0.0f};
		KamataEngine::Vector3 P_velocity = {distribution(randomEngine), distribution(randomEngine), 0};
		P_position = position;
		Normalize(P_velocity);
		P_velocity *= distribution(randomEngine);
		P_velocity *= 0.1f;

		particle_->Initialize(modelParticle_, P_position, P_velocity);
		// リストに追加
		particles_.push_back(particle_);
	}
}

Game::~Game() {
	delete debugCamera_;

	// delete model_;
	delete model2_;

#pragma region エフェクトの解放
	// エフェクト
	for (Effect* effect : effects_) {
		delete effect;
	}
	effects_.clear();
	delete modelEffect_;
#pragma endregion

#pragma region パーティクルの解放
	delete modelParticle_;

	for (Particle* particle : particles_) {
		delete particle;
	}
	particles_.clear();
#pragma endregion

#pragma region UI

	delete ESC_Sprite_;
	delete ESC_Sprite_2;

	delete PoseUI_Sprite_;
	delete PoseUI_Sprite_2;

	delete PoseUI2_Sprite_;
	delete PoseUI2_Sprite_2;

#pragma endregion

	delete stage_;

	delete player_;
	delete graphBar_;

	delete drawNumber_;

	Model2::StaticFinalize();
}