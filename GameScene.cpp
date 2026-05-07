#include "GameScene.h"
using namespace KamataEngine;

void Game::Initialize() {

	textureHandle_ = TextureManager::Load("uvChecker.png");

	model_ = Model::Create();

	worldTransform_.Initialize();
	camera_.Initialize();

	model2_ = new Model2();
	model2_->Initialize(model_, textureHandle_, &camera_);
}

void Game::Update() { model2_->Update(); }

void Game::Draw() {

	Model::PreDraw();

	model_->Draw(worldTransform_, camera_, textureHandle_);
	model2_->Draw();

	Model::PostDraw();
}

Game::~Game() {
	delete model_;
	delete model2_;
}