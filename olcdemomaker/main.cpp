#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class gra : public olc::PixelGameEngine
{
public:
	gra()
	{
		sAppName = "gra";
	}

private:
	int level = 0;

	float posX = 0.0f;
	float posY = 0.0f;
	float speed = 0.1f / 40.0f;

	int map[16][16];

	float fTargetFrameTime = 1.0f / 100.0f; // Virtual FPS of 100fps
	float fAccumulatedTime = 0.0f;


public:

	void saveLevel() {
		std::ofstream myfile("levels/map" + std::to_string(level)+".txt");
		if (myfile.is_open())
		{
			for (int i = 0; i < 16; i++) {
				for (int j = 0; j < 16; j++) {
					myfile << map[i][j];
				}
				myfile << "\n";
			}
			
			myfile.close();
		}
		return;
	}

	void clearMap() {
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 16; j++) {
				map[i][j] = 0;
			}
		}
		return;
	}

	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		fAccumulatedTime += fElapsedTime;
		if (fAccumulatedTime >= fTargetFrameTime)
		{
			fAccumulatedTime -= fTargetFrameTime;
			fElapsedTime = fTargetFrameTime;
		}
		else

		Clear(olc::BLACK);

		if (GetKey(olc::Key::K1).bHeld) {
			map[GetMouseY()][GetMouseX()] = 1;
		}
		if (GetKey(olc::Key::SPACE).bHeld) {
			map[GetMouseY()][GetMouseX()] = 0;
		}
		if (GetKey(olc::Key::K2).bHeld) {
			map[GetMouseY()][GetMouseX()] = 2;
		}
		if (GetKey(olc::Key::K3).bHeld) {
			map[GetMouseY()][GetMouseX()] = 3;
		}
		if (GetKey(olc::Key::K4).bHeld) {
			map[GetMouseY()][GetMouseX()] = 4;
		}
		if (GetKey(olc::Key::F1).bPressed) {
			saveLevel();
			clearMap();
			level++;
		}

		for (int i = 0; i < 16; i++){
			for (int j = 0; j < 16; j++) {
				if (map[i][j] == 1) {
					Draw(j, i, olc::Pixel(olc::WHITE));
				}
				if (map[i][j] == 2) {
					Draw(j, i, olc::Pixel(olc::BLUE));
				}
				if (map[i][j] == 3) {
					Draw(j, i, olc::Pixel(olc::RED));
				}
				if (map[i][j] == 4) {
					Draw(j, i, olc::Pixel(olc::DARK_RED));
				}
			}
		}

		return true;
	}
};

int main()
{
	gra demo;
	if (demo.Construct(16, 16, 32, 32))
		demo.Start();
	return 0;
}