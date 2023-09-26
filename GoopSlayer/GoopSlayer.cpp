#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

//THIS IS WRITTEN USING OLC GPE, CHECK OUT onelonecoder.com
//Or else

class GoopSlayer : public olc::PixelGameEngine {
public:
	//Sprites / pngs
	std::unique_ptr<olc::Sprite> GoopRight;
	std::unique_ptr<olc::Sprite> Grass;
	olc::Decal* d = new olc::Decal(Grass.get());

	GoopSlayer() {
		sAppName = "GoopSlayer";
	}

	void DrawGrass() {
		for (int x = 0; x < 800; x += 32) {
			for (int y = 0; y < 600; y += 32) {
				DrawDecal({ (float)x, (float)y }, d);
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
	if (demo.Construct(800, 600, 1, 1, true))
		demo.Start();
	return 0;
}