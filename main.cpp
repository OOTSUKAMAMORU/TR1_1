#include <Novice.h>
#include<time.h>
const char kWindowTitle[] = "LE2D_07_オオツカ_マモル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
	int timer = 60 * 10;

	//プレイヤー
	int posX = 200;
	int posY = 600;
	int speed = 10;
	int radius = 40;
	int bulletX = 100;
	int bulletY = 100;
	int bulletflag = 0;
	//0は存在しない１は存在する
	
	//敵
	int enemyX=100;
	int enemyY = 100;

	//スコア
	int  score = 0;

	// 現在時刻の情報で初期化
	srand((unsigned int)time(NULL));
	enemyX = rand() % 1100;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		if (timer >= 0)
		{

			//衝突判定
			if (abs(enemyX - bulletX) < 50 && abs(enemyY - bulletY) < 50)
			{
				enemyY = 0;
				enemyX = rand() % 1100;
			}
			///
			/// ↓更新処理ここから
			///

			//敵が落ちてくるスピード
			enemyY += 5;

			//敵が画面下に行ったら上に戻る
			if (enemyY > 720)
			{
				enemyY = 0;
				enemyX = rand() % 1100;
			}
			//プレイヤーの移動
			if (keys[DIK_D]) 
			{
				posX += speed;
			}
			if (keys[DIK_A]) 
			{
				posX -= speed;
			}

			//当たり判定
			if (abs(bulletX - enemyX) < 100 && abs(bulletY - enemyY) < 100)
			{
				enemyY = 0;
				enemyX = rand() % 1100;
				score += 1;
			}
			//タイマー
			timer -= 1;

			//弾
			//弾のスピード
			bulletY -= 15;
			if (bulletflag == 0)
			{
				//スペースを押したら弾が出る
				if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0)
				{
					bulletflag = 1;
					bulletX = posX;
					bulletY = posY;
				}
			}
			//弾の画面外に行くまで弾が打てなくなる処理
			if (bulletY < 0)
			{
				bulletflag = 0;
			}
		}
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		Novice::DrawEllipse(posX, posY, radius, radius, 0.0f, WHITE, kFillModeSolid);
		Novice::DrawBox(enemyX-50,enemyY-50, 100,100,0.0f, BLACK, kFillModeSolid);
		Novice::ScreenPrintf(100,100,"score=%d",score);
		Novice::DrawEllipse(bulletX, bulletY, radius, radius, 0.0f, RED, kFillModeSolid);
		Novice::ScreenPrintf(0, 0, "x=%d", timer);
		//時間制限
		if (timer<0)
		{
			Novice::ScreenPrintf(600,300,"Gameover");
		}
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
