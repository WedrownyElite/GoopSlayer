#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

//THIS IS WRITTEN USING OLC GPE, CHECK OUT onelonecoder.com
//Or else

class GoopSlayer : public olc::PixelGameEngine {
public:
	//Sprites
	std::unique_ptr<olc::Sprite> GoopRight;	
	std::unique_ptr<olc::Sprite> Grass;
	std::unique_ptr<olc::Sprite> ArcherRight;
	//Decals
	olc::Decal* GrassDecal;
	olc::Decal* GoopRightDecal;
	olc::Decal* ArcherRightDecal;

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
		if (GoopX == 960) {
			GoopX = 0;
		}
	}

	bool OnUserUpdate(float fElapsedTime) override {
		Clear(olc::BLACK);
		DrawGrass();
		MoveGoop();
		DrawDecal({ (float)448, (float)238 }, ArcherRightDecal, { (float)2, (float)2 });
		return true;
	}

private:
	bool OnUserCreate() override {
		//Sprites
		ArcherRight = std::make_unique<olc::Sprite>("./Sprites/ArcherRight.png");
		Grass = std::make_unique<olc::Sprite>("./Sprites/Grass.png");
		GoopRight = std::make_unique<olc::Sprite>("./Sprites/GoopRight.png");
		//Decals
		GrassDecal = new olc::Decal(Grass.get());
		GoopRightDecal = new olc::Decal(GoopRight.get());
		ArcherRightDecal = new olc::Decal(ArcherRight.get());
		return true;
	}
};

int main() {
	GoopSlayer demo;
	if (demo.Construct(960, 540, 1, 1, true))
		demo.Start();
	return 0;
}