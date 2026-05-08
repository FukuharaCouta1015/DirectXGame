#include "GameScene.h"
using namespace KamataEngine;
using namespace MathUtility;
void Game::Initialize() {
	// デバッグカメラ生成
	debugCamera_ = new DebugCamera(1280, 720);

	// model_ = Model::Create();

	Model2::StaticInitialize();
	// model2_ = Model2::Create();
	model2_ = Model2::CreateSquare();

	model2_2_ = Model2::CreateSquare2();

	model2_3_ = Model2::CreateSquare3();

	model2_ring_ = Model2::CreateRing(5.0f, 10.0f, 8);

	textureHandle_ = TextureManager::Load("uvChecker.png");

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
}

void Game::Draw() {
	ID3D12GraphicsCommandList* commandList = DirectXCommon::GetInstance()->GetCommandList();

	Model::PreDraw();
	// model_->Draw(worldTransform_, camera_, textureHandle_);
	Model::PostDraw();

	Model2::PreDraw(commandList);

	// model2_->Draw(worldTransform_, camera_, textureHandle_);

	// model2_2_->Draw(worldTransform_, camera_, textureHandle_);

	// model2_3_->Draw(worldTransform_, camera_, textureHandle_);

	model2_ring_->Draw(worldTransform_, camera_, textureHandle_);

	Model2::PostDraw();
}

Game::~Game() {
	delete debugCamera_;

	// delete model_;
	delete model2_;

	Model2::StaticFinalize();
}