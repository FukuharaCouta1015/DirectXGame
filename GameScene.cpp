#include "GameScene.h"
#include <cstdlib>
#include <ctime>
#include <random>

using namespace KamataEngine;
using namespace MathUtility;

std::random_device seedGenerator;
std::mt19937 randomEngine(seedGenerator());
std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

void Game::Initialize() {
	// デバッグカメラ生成
	debugCamera_ = new DebugCamera(1280, 720);

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

	modelParticle_ = KamataEngine::Model::CreateSphere(4, 4);

	particle_ = new Particle();
	KamataEngine::Vector3 P_position = {0.0f, 0.0f, 0.0f};
	particle_->Initialize(modelParticle_, P_position);
	/*
	for (int i = 0; i < 150; i++)
	{

	    //リストに追加
	    particles_.push_back(particle_);
	}*/

#pragma endregion

#pragma region テクスチャ

	// textureHandle_ = TextureManager::Load("uvChecker.png");
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

	/*
	for (Particle* particle : particles_)
	{
	    particle->Update();
	}*/
	particle_->Update();
}

void Game::Draw() {
	ID3D12GraphicsCommandList* commandList = DirectXCommon::GetInstance()->GetCommandList();

	Model::PreDraw();

#pragma region エフェクト描画

	if (Input::GetInstance()->TriggerKey(DIK_E)) {
		ON_Effect = (ON_Effect == false);
		OFF_Effect = (ON_Effect == false);
	}
	if (ON_Effect) {
		// エフェクト描画
		for (Effect* effect : effects_) {
			effect->Draw(camera_);
		}
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
	particle_->Draw(camera_);

#pragma endregion

	Model::PostDraw();

	Model2::PreDraw(commandList);

	// model2_->Draw(worldTransform_, camera_, textureHandle_Circle_);

	// model2_2_->Draw(worldTransform_, camera_, textureHandle_);

	// model2_3_->Draw(worldTransform_, camera_, textureHandle_);

	// model2_ring_->Draw(worldTransform_, camera_, textureHandle_);

	Model2::PostDraw();
}

#pragma region エフェクト発生
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

#pragma endregion

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

	// パーティクルの解放
	delete modelParticle_;
	delete particle_;
	/*
	for (Particle* particle : particles_)
	{
	    delete particle;
	}
	particles_.clear();
*/

	Model2::StaticFinalize();
}