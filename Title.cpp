#include "Title.h"
using namespace KamataEngine;

void Title::Initialize() {
	textureHandle_ = TextureManager::Load("uvChecker.png");
	titleSprite_ = KamataEngine::Sprite::Create(textureHandle_, {0, 0});
	titleSprite_->SetSize({1280, 720});

	CreditsHandle_ = TextureManager::Load("Scenes/Credits.png");
	CreditsSprite_ = KamataEngine::Sprite::Create(CreditsHandle_, {768, 518});

	Title_Text_H_ = TextureManager::Load("Scenes/Title_text.png");
	Title_Text_S_ = KamataEngine::Sprite::Create(Title_Text_H_, {290, -100});
	Title_Text_S_->SetSize({700, 212});

	T_StartHandle_ = TextureManager::Load("UI/TitleUI.png");
	T_StartSprite_ = KamataEngine::Sprite::Create(T_StartHandle_, {448, 364});

	T_StartHandle_2 = TextureManager::Load("UI/Pushed_TitleUI.png");
	T_StartSprite_2 = KamataEngine::Sprite::Create(T_StartHandle_2, {448, 364});

	Botan_ = Audio::GetInstance()->LoadWave("Sounds/sound/Decision2.mp3");

	// カメラの初期化
	camera_.Initialize();
	// ワールド変換の初期化
	worldTransform_.Initialize();

	// フェード
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 1.0f);
}

void Title::Update() {

	KamataEngine::Vector2 T_Text_Pos = Title_Text_S_->GetPosition();

	if (t_texMove) {
		T_Text_Pos.y += 1.0f;
	}
	Title_Text_S_->SetPosition(T_Text_Pos);

	if (T_Text_Pos.y == 100.0f) {
		t_texMove = false;
	}

	// タイマーを進める (毎フレーム +1)
	blinkTimer_++;
	if (blinkTimer_ >= 60) {
		blinkTimer_ = 0;
	}

	switch (phase_) {
	case Phase::kMain:

		// タイトルシーンの終了条件
		if (Input::GetInstance()->TriggerKey(DIK_SPACE) || Input::GetInstance()->IsTriggerMouse(0)) {

			Audio::GetInstance()->PlayWave(Botan_);
			// フェードアウト開始
			phase_ = Phase::kFadeOut;
			fade_->Start(Fade::Status::FadeOut, 1.0f);
			finishedTitle_ = true;
		}

		break;
	case Phase::kFadeIn:
		// フェード
		fade_->Update();
		if (fade_->IsFinished()) {
			phase_ = Phase::kMain;
		}
		break;
	case Phase::kFadeOut:
		// フェード
		fade_->Update();
		if (fade_->IsFinished()) {
			finishedTitle_ = true;
		}
		break;
	}
}

void Title::Draw() {
	// DirectXCommonインスタンスの取得
	// DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Sprite::PreDraw();

	// titleSprite_->Draw();

	CreditsSprite_->Draw();

	Title_Text_S_->Draw();

	// 60で割った余りが30以上の場合のみ描画（点滅処理）
	if (blinkTimer_ % 60 >= 30) {
		// マウスが押されている間は押された用の画像、それ以外は通常画像
		if (Input::GetInstance()->IsPressMouse(0)) {
			T_StartSprite_2->Draw();
		} else {
			T_StartSprite_->Draw();
		}
	}

	Sprite::PostDraw();

	// フェード
	fade_->Draw();
}

Title::~Title() {

	//  フェード
	delete fade_;
	// タイトルのスプライト
	delete titleSprite_;
	delete CreditsSprite_;
	delete Title_Text_S_;

	delete T_StartSprite_;
	delete T_StartSprite_2;
}