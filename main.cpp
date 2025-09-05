#include <Novice.h>
#include<time.h>
const char kWindowTitle[] = "LE2D_07_オオツカ_マモル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) 
{

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
	int timer = 60 * 30;

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
	const int enemyMax = 5;
	int enemyX[enemyMax] = {0};
	int enemyY[enemyMax] = { 0 };
	int enemyFlag[enemyMax] = { 0 };


	//スコア
	int  score = 0;

	// 現在時刻の情報で初期化
	srand((unsigned int)time(NULL));
	//enemyX = rand() % 1100;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		if (timer >= 0)
		{
			//敵の発生
			if (rand() % 20 == 0)
			{
				for (int i = 0; i < enemyMax; i++)
				{
					if (enemyFlag[i] == 0)
					{
						enemyFlag[i] = 1;
						enemyY[i] = 0;
						enemyX[i] = rand() % 1100;
						break;
					}
				}
			}
			//衝突判定
			for (int i = 0; i < enemyMax; i++)
			{
				if (enemyFlag[i] == 1)
				{
					if (abs(enemyX[i] - bulletX) < 50 && abs(enemyY[i] - bulletY) < 50)
					{
						enemyFlag[i] = 0;
					}
				}
			}
			///
			/// ↓更新処理ここから
			///

			//敵が落ちてくるスピード
			for (int i = 0; i < enemyMax; i++)
			{
				if (enemyFlag[i] == 1)
				{
					enemyY[i] += 5;

					//敵が画面下に行ったら上に戻る
					if (enemyY[i] > 720)
					{
						enemyFlag[i] = 0;
					}
				}
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
			for (int i = 0; i < enemyMax; i++)
			{
				if (enemyFlag[i] == 1)
				{
					if (abs(bulletX - enemyX[i]) < 100 && abs(bulletY - enemyY[i]) < 100)
					{
						bulletflag = 0;
						enemyFlag[i] = 0;
						score += 1;
					}
				}
			}
			//タイマー
			timer -= 1;

			//弾
			//弾のスピード
			if (bulletflag == 1)
			{
				bulletY -= 15;
			}
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
		for (int i = 0; i < enemyMax; i++)
		{
			if (enemyFlag[i] == 1)
			{
				Novice::DrawBox(enemyX[i] - 50, enemyY[i] - 50, 100, 100, 0.0f, BLACK, kFillModeSolid);
			}
		}
		Novice::ScreenPrintf(100,100,"score=%d",score);
		if (bulletflag == 1)
		{
			Novice::DrawEllipse(bulletX, bulletY, radius, radius, 0.0f, RED, kFillModeSolid);

		}
		Novice::ScreenPrintf(0, 0, "x=%d", timer);
		Novice::DrawBox(10,10, timer/10, 10, 0.0f, BLACK, kFillModeSolid);
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
