#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class GoopSlayer : public olc::PixelGameEngine {
public:
    //Sprites
    std::unique_ptr<olc::Sprite> GoopRight;
    std::unique_ptr<olc::Sprite> Grass;
    std::unique_ptr<olc::Sprite> ArcherRight;
    std::unique_ptr<olc::Sprite> Arrow;
    //Decals
    olc::Decal* GrassDecal;
    olc::Decal* GoopRightDecal;
    olc::Decal* ArcherRightDecal;
    olc::Decal* ArrowDecal;
    //GoopVariables
    float GoopX = 0;
    float GoopY = 50;
    //Arrow variables
    olc::vf2d arrowPos;
    olc::vf2d arrowVel;
    bool arrowLaunched = false;

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
        DrawDecal({ (float)GoopX, (float)GoopY }, GoopRightDecal, { (float)2, (float)2 });
        if (GoopX == 960) {
            GoopX = 0;
        }
    }

    bool OnUserUpdate(float fElapsedTime) override {
        MoveGoop();
        DrawDecal({ (float)448, (float)238 }, ArcherRightDecal, { (float)2, (float)2 });

        // User input
        if (GetMouse(0).bPressed) {
            // Get mouse click position
            olc::vf2d targetPos = { (float)GetMouseX(), (float)GetMouseY() };

            // Calculate velocity towards the target
            arrowVel = (targetPos - arrowPos).norm() * 200.0f;

            // Set arrow as launched
            arrowLaunched = true;
        }

        // Move the arrow
        if (arrowLaunched) {
            arrowPos += arrowVel * fElapsedTime;

            // Check if arrow is off-screen
            if (arrowPos.x < 0 || arrowPos.x >= ScreenWidth() || arrowPos.y < 0 || arrowPos.y >= ScreenHeight()) {
                // Reset arrow when it's off-screen
                arrowPos = { (float)ScreenWidth() / 2, (float)ScreenHeight() / 2 };
                arrowVel = { 0.0f, 0.0f };
                arrowLaunched = false;
            }
        }

        Clear(olc::BLACK);

        // Draw the arrow using DrawRotateDecal
        if (arrowLaunched) {
            // Calculate the angle of rotation based on the arrow's velocity
            float angle = atan2f(arrowVel.y, arrowVel.x);

            // Draw the rotated arrow
            DrawRotatedDecal(arrowPos, ArrowDecal, angle, { 1.0f, 1.0f }, { 1.0f, 1.0f}, olc::WHITE);
        }

        return true;
    }

private:
    bool OnUserCreate() override {
        //Sprites
        ArcherRight = std::make_unique<olc::Sprite>("./Sprites/ArcherRight.png");
        Grass = std::make_unique<olc::Sprite>("./Sprites/Grass.png");
        GoopRight = std::make_unique<olc::Sprite>("./Sprites/GoopRight.png");
        Arrow = std::make_unique<olc::Sprite>("./Sprites/Arrow.png");
        //Decals
        GrassDecal = new olc::Decal(Grass.get());
        GoopRightDecal = new olc::Decal(GoopRight.get());
        ArcherRightDecal = new olc::Decal(ArcherRight.get());
        ArrowDecal = new olc::Decal(Arrow.get());
        //Set arrow velocity and position
        arrowPos = { (float)ScreenWidth() / 2, (float)ScreenHeight() / 2 };
        arrowVel = { 0.0f, 0.0f };
        return true;
    }
};

int main() {
    GoopSlayer demo;
    if (demo.Construct(960, 540, 1, 1, true))
        demo.Start();
    return 0;
}
