#include "GameScene.h"
using namespace KamataEngine;

void Game::Initialize() {

	textureHandle_ = TextureManager::Load("uvChecker.png");

	model_ = Model::Create();

	worldTransform_.Initialize();
	camera_.Initialize();

	Model2::StaticInitialize();
}

void Game::Update() {}

void Game::Draw() {

	Model::PreDraw();

	model_->Draw(worldTransform_, camera_, textureHandle_);

	Model::PostDraw();
}

Game::~Game() {
	delete model_;

	Model2::StaticFinalize();
}