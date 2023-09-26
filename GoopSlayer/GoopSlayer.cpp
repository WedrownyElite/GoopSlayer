#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

//THIS IS WRITTEN USING OLC GPE, CHECK OUT onelonecoder.com
//Or else

class GoopSlayer : public olc::PixelGameEngine {
public:
	//Sprites / pngs
	std::unique_ptr<olc::Sprite> GoopRight;
	std::unique_ptr<olc::Sprite> Grass;

	GoopSlayer() {
		sAppName = "GoopSlayer";
	}

	void DrawGrass() {
		for (int x = 0; x < 1920; x += 32) {
			DrawSprite(x, 0, Grass.get(), 1);
			for (int y = 0; y < 1080; y += 32) {
				DrawSprite(0, y, Grass.get(), 1);
				DrawSprite(x, y, Grass.get(), 1);
			}
		}
	}

	bool OnUserUpdate(float fElapsedTime) override {
		DrawGrass();
		return true;
	}

private:
	bool OnUserCreate() override {
		Grass = std::make_unique<olc::Sprite>("./Sprites/Fuck.png");
		GoopRight = std::make_unique<olc::Sprite>("./Sprites/GoopRight.png");
		return true;
	}
};

int main() {
	GoopSlayer demo;
	if (demo.Construct(1920, 1080, 1, 1))
		demo.Start();
	return 0;
}