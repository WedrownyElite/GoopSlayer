#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

//THIS IS WRITTEN USING OLC GPE, CHECK OUT onelonecoder.com
//Or else

class GoopSlayer : public olc::PixelGameEngine {
public:
	//Sprites / pngs
	std::unique_ptr<olc::Sprite> GoopRight;	
	std::unique_ptr<olc::Sprite> Grass;
	olc::Decal* GrassDecal;
	olc::Decal* GoopRightDecal;

	float GoopX = 0;
	float GoopY = 50;

	GoopSlayer() {
		sAppName = "GoopSlayer";
	}

	void DrawGrass() {
		for (int x = 0; x < 960; x += 32) {
			for (int y = 0; y < 540; y += 32) {
				DrawDecal({ (float)x, (float)y }, GrassDecal);
			}
		}
	}
	
	void MoveGoop() {
		GoopX += 1;
		DrawDecal({ (float)GoopX, (float)GoopY }, GoopRightDecal, { (float)2, (float)2 });
	}

	bool OnUserUpdate(float fElapsedTime) override {
		Clear(olc::BLACK);
		DrawGrass();
		MoveGoop();
		return true;
	}

private:
	bool OnUserCreate() override {
		Grass = std::make_unique<olc::Sprite>("./Sprites/Fuck.png");
		GoopRight = std::make_unique<olc::Sprite>("./Sprites/GoopRight.png");
		GrassDecal = new olc::Decal(Grass.get());
		GoopRightDecal = new olc::Decal(GoopRight.get());
		return true;
	}
};

int main() {
	GoopSlayer demo;
	if (demo.Construct(960, 540, 1, 1, true))
		demo.Start();
	return 0;
}