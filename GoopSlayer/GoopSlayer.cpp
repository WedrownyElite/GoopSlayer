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
    //Goop variables
    std::vector<bool> GoopAlive;
    std::vector<olc::vf2d> GoopPos;
    //Arrow variables
    std::vector<olc::vf2d> arrowPos;
    std::vector<olc::vf2d> arrowVel;
    //Archer variables
    olc::vf2d ArcherPos;
    //User inputs
    enum userInputs {LEFT, RIGHT, UP, DOWN, STOP};
    userInputs Inputs = STOP;

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
        GoopPos[0].x += speed;
        DrawDecal({GoopPos[0]}, GoopRightDecal, {2.0f, 2.0f});
        if (GoopPos[0].x >= 960) {
            GoopPos[0].x = -70;
        }
    }
    void ArrowGoopCheck() {
        //Check if arrow hits goop
        for (int k = 0; k < arrowPos.size(); k++) {
            olc::vi2d Arrow(arrowPos[k]);
            olc::vi2d ArrowSize(30, 30);

            for (int o = 0; o < GoopPos.size(); o++) {
                olc::vi2d Goop(GoopPos[o]);
                olc::vi2d GoopSize(63, 63);

                if (Arrow.x < Goop.x + GoopSize.x &&
                    Arrow.x + ArrowSize.x > Goop.x &&
                    Arrow.y < Goop.y + GoopSize.y &&
                    Arrow.y + ArrowSize.y > Goop.y) {
                    arrowPos.erase(arrowPos.begin() + k);
                    arrowVel.erase(arrowVel.begin() + k);
                    GoopPos[o].x = -30;
                }
            }
        }
    }
    void DrawArrow(float fElapsedTime) {
        // Move and draw the arrows
        for (size_t i = 0; i < arrowPos.size(); i++) {
            arrowPos[i] += arrowVel[i] * fElapsedTime;

            // Check if arrow is off-screen
            if (arrowPos[i].x < 0 || arrowPos[i].x >= ScreenWidth() || arrowPos[i].y < 0 || arrowPos[i].y >= ScreenHeight()) {
                // Remove the arrow
                arrowPos.erase(arrowPos.begin() + i);
                arrowVel.erase(arrowVel.begin() + i);
                i--;
            }
            else {
                // Calculate the angle of rotation based on the arrow's velocity
                float angle = atan2f(arrowVel[i].y, arrowVel[i].x);

                // Draw the rotated arrow
                DrawRotatedDecal(arrowPos[i], ArrowDecal, angle, { 1.0f, 1.0f }, { 1.0f, 1.0f }, olc::WHITE);

                //Arrow+Goop Check
                ArrowGoopCheck();
            }
        }
    }
    void ShootArrow(float fElapsedTime) {
        // User input
        if (GetMouse(0).bPressed && arrowPos.size() < 100) {
            // Get mouse click position
            olc::vf2d targetPos = { (float)GetMouseX(), (float)GetMouseY() };

            // Calculate velocity towards the target
            olc::vf2d vel = (targetPos - olc::vf2d(ArcherPos)).norm() * 300.0f;


            // Store the arrow's position and velocity
            arrowPos.push_back({ (float)ScreenWidth() / 2, (float)ScreenHeight() / 2 });
            arrowVel.push_back(vel);
        }
        DrawArrow(fElapsedTime);
    }
    void UserInput(float fElapsedTime, float speed) {
        if (GetKey(olc::Key::LEFT).bHeld) {
            Inputs = LEFT;
        }
        if (GetKey(olc::Key::RIGHT).bHeld) {
            Inputs = RIGHT;
        }
        if (GetKey(olc::Key::UP).bHeld) {
            Inputs = UP;
        }
        if (GetKey(olc::Key::DOWN).bHeld) {
            Inputs = DOWN;
        }

        switch (Inputs) {
        case LEFT:
            ArcherPos.x -= speed;
        case RIGHT:
            ArcherPos.x += speed;
        case UP:
            ArcherPos.y -= speed;
        case DOWN:
            ArcherPos.y += speed;
        }

    }
    bool OnUserUpdate(float fElapsedTime) override {
        float speed = 200 * fElapsedTime;
        DrawGrass();
        if (GoopAlive[0] == true) {
            MoveGoop(speed);
        }
        DrawDecal({ArcherPos}, ArcherRightDecal, { (float)2, (float)2 });
        UserInput(fElapsedTime, speed);
        ShootArrow(fElapsedTime);

        return true;
    }

private:
    bool OnUserCreate() override {
        ArcherPos.x = 448.0f;
        ArcherPos.y = 238.0f;
        GoopPos.push_back({ -30, (float)ScreenHeight() / 4 });
        GoopAlive.push_back(true);
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
        return true;
    }
};

int main() {
    GoopSlayer demo;
    if (demo.Construct(960, 540, 1, 1, true))
        demo.Start();
    return 0;
}
