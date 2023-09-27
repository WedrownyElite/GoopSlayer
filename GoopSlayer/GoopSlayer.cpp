#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <iostream>
#include <vector>

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
    float GoopX = -70;
    float GoopY = 50;
    //Arrow variables
    olc::vf2d arrowPos[99];
    olc::vf2d arrowVel[99];
    int arrowCount = 0;

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

    void MoveGoop(float speed) {
        GoopX += speed;
        DrawDecal({ (float)GoopX, (float)GoopY }, GoopRightDecal, { (float)2, (float)2 });
        if (GoopX >= 960) {
            GoopX = -70;
        }
    }

    bool OnUserUpdate(float fElapsedTime) override {
        float speed = 200 * fElapsedTime;
        DrawGrass();
        MoveGoop(speed);
        DrawDecal({ (float)448, (float)238 }, ArcherRightDecal, { (float)2, (float)2 });

        // User input
        if (GetMouse(0).bPressed) {
            arrowCount++;
            for (int arrows = 1; arrows <= arrowCount; arrows++) {
                // Get mouse click position
                std::array< olc::vf2d, 99 > targetPos = { olc::vf2d{ (float)GetMouseX(), (float)GetMouseY() } };

                // Calculate velocity towards the target
                arrowVel[arrows] = (targetPos[arrows] - arrowPos[arrows]).norm() * 300.0f;
            }
        }

        // Move the arrow
        if (arrowCount > 0) {
            for (int arrows = 1; arrows <= arrowCount; arrows++) {
                arrowPos[arrows] += arrowVel[arrows] * fElapsedTime;

                // Check if arrow is off-screen
                if (arrowPos[arrows].x < 0 || arrowPos[arrows].x >= ScreenWidth() || arrowPos[arrows].y < 0 || arrowPos[arrows].y >= ScreenHeight()) {
                    // Reset arrow when it's off-screen
                    arrowPos[arrows] = { (float)ScreenWidth() / 2, (float)ScreenHeight() / 2 };
                    arrowVel[arrows] = { 0.0f, 0.0f };
                    arrowCount--;
                }
            }
        }

        Clear(olc::BLACK);

        // Draw the arrow using DrawRotateDecal
        if (arrowCount > 0) {
            for (int arrows = 1; arrows <= arrowCount; arrows++) {
                // Calculate the angle of rotation based on the arrow's velocity
                float angle = atan2f(arrowVel[arrows].y, arrowVel[arrows].x);

                // Draw the rotated arrow
                DrawRotatedDecal(arrowPos[arrows], ArrowDecal, angle, { 1.0f, 1.0f }, { 1.0f, 1.0f }, olc::WHITE);
            }
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
        arrowPos[100] = {(float)ScreenWidth() / 2, (float)ScreenHeight() / 2};
        arrowVel[100] = {0.0f, 0.0f};
        return true;
    }
};

int main() {
    GoopSlayer demo;
    if (demo.Construct(960, 540, 1, 1, true))
        demo.Start();
    return 0;
}
