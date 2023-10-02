#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <iostream>
#include <vector>

class GoopSlayer : public olc::PixelGameEngine {
public:
    //Sprites
    std::unique_ptr<olc::Sprite> GoopRight;
    std::unique_ptr<olc::Sprite> GoopLeft;
    std::unique_ptr<olc::Sprite> Grass;
    std::unique_ptr<olc::Sprite> ArcherRight;
    std::unique_ptr<olc::Sprite> Arrow;
    //Decals
    olc::Decal* GrassDecal;
    olc::Decal* GoopRightDecal;
    olc::Decal* GoopLeftDecal;
    olc::Decal* ArcherRightDecal;
    olc::Decal* ArrowDecal;
    //Goop variables
    std::vector<olc::vf2d> GoopVel;
    std::vector<olc::vf2d> GoopPos;
    int MaxGoops = 1;
    //Arrow variables
    std::vector<olc::vf2d> arrowPos;
    std::vector<olc::vf2d> arrowVel;
    //Archer variables
    olc::vf2d ArcherPos;
    int score = 0;
    //Menu variables
    int menu = 0;
    enum GameStateEnum { MENU, DEAD, GAME, PAUSE, QUIT };
    GameStateEnum GameState = MENU;
    int Wave = 0;

    GoopSlayer() {
        sAppName = "GoopSlayer";
    }

    void DeadUserInputs() {
        if (GetKey(olc::Key::SPACE).bPressed) {
            GameState = MENU;
        }
        if (GetKey(olc::Key::ESCAPE).bPressed) {
            GameState = QUIT;
        }
    }
    void ArcherDead() {
        Clear(olc::BLACK);
        std::string ScoreString = std::to_string(score);
        DrawString(ScreenWidth() / 5, ScreenHeight() / 9, "You've been slain!", olc::MAGENTA, 4);
        DrawString(ScreenWidth() / 3 + 70, ScreenHeight() / 4, "Score:", olc::GREEN, 4);
        DrawString(ScreenWidth() / 3 + 130, ScreenHeight() / 3, ScoreString, olc::GREEN, 4);
        DrawString(ScreenWidth() / 7, ScreenHeight() / 2, "Press 'SPACE' to retry", olc::BLUE, 4);
    }
    void MainMenu() {
        Clear(olc::BLACK);
        if (menu == 0) {
            DrawDecal({ (float)ScreenWidth() - 220, (float)ScreenHeight() / 5 - 20 }, ArrowDecal, { (float)4, (float)4 });
            DrawDecal({ (float)ScreenWidth() / 8 - 20, (float)ScreenHeight() / 5 - 20 }, GoopRightDecal, { (float)3, (float)3 });
            DrawString(ScreenWidth() / 5 + 30, ScreenHeight() / 4, "Goop Slayer", olc::MAGENTA, 6);
            DrawString(ScreenWidth() / 3, ScreenHeight() / 3 + 70, ">> Play", olc::GREEN, 4);
            DrawString(ScreenWidth() / 3 + 96, ScreenHeight() / 2 + 50, "Quit", olc::RED, 4);
        }
        else if (menu == 1) {
            DrawDecal({ (float)ScreenWidth() - 220, (float)ScreenHeight() / 5 - 20 }, ArrowDecal, { (float)4, (float)4 });
            DrawDecal({ (float)ScreenWidth() / 8 - 20, (float)ScreenHeight() / 5 - 20 }, GoopRightDecal, { (float)3, (float)3 });
            DrawString(ScreenWidth() / 5 + 30, ScreenHeight() / 4, "Goop Slayer", olc::MAGENTA, 6);
            DrawString(ScreenWidth() / 3 + 96, ScreenHeight() / 3 + 70, "Play", olc::GREEN, 4);
            DrawString(ScreenWidth() / 3, ScreenHeight() / 2 + 50, ">> Quit", olc::RED, 4);
        }
        if ((GetKey(olc::Key::DOWN).bPressed || (GetKey(olc::Key::S).bPressed)) && menu < 1) {
            menu++;
        }
        else if ((GetKey(olc::Key::DOWN).bPressed || (GetKey(olc::Key::S).bPressed)) && menu == 1) {
            menu = 0;
        }
        else if ((GetKey(olc::Key::UP).bPressed || (GetKey(olc::Key::W).bPressed)) && menu > 0) {
            menu--;
        }
        else if ((GetKey(olc::Key::UP).bPressed || (GetKey(olc::Key::W).bPressed)) && menu == 0) {
            menu = 1;
        }
        if ((GetKey(olc::Key::ENTER).bPressed) || (GetKey(olc::Key::E).bPressed) && menu == 0) {
            for (int k = 0; k < GoopPos.size(); k++) {
                GoopPos.erase(GoopPos.begin() + k);
            }
            for (int k = 0; k < arrowPos.size(); k++) {
                arrowPos.erase(arrowPos.begin() + k);
                arrowVel.erase(arrowVel.begin() + k);
            }
            ArcherPos.x = 448.0f;
            ArcherPos.y = 238.0f;
            score = 0;

            GameState = GAME;
        }
        else if (GetKey(olc::Key::ENTER).bPressed && menu == 1) {
            GameState = QUIT;
        }
    }
    void DrawGrass() {
        for (int x = 0; x < 960; x += 32) {
            for (int y = 0; y < 540; y += 32) {
                DrawDecal({ (float)x, (float)y }, GrassDecal);
            }
        }
    }
    void SpawnGoop() {
        if (GoopPos.size() == 0) {
            //Random num gen to choose whether goop X or Y is zero
            for (int k = 0; k < MaxGoops; k++) {
                srand(time(NULL));
                int SideGoopNum = rand() % 4;

                if (SideGoopNum == 0) {
                    float GoopYNum = rand() % 539;
                    GoopPos.push_back({ 0, GoopYNum });
                }
                if (SideGoopNum == 1) {
                    float GoopXNum = rand() % 959;
                    GoopPos.push_back({ GoopXNum, 0 });
                }
                if (SideGoopNum == 2) {
                    float GoopXNum = rand() % 959;
                    GoopPos.push_back({ GoopXNum, 540 });
                }
                if (SideGoopNum == 3) {
                    float GoopYNum = rand() % 539;
                    GoopPos.push_back({ 960, GoopYNum });
                }
            }
        }
    }
    void PlayerGoopCheck() {
        olc::vi2d Goop(GoopPos[0]);
        olc::vi2d GoopSize(64, 64);
        olc::vi2d Archer(ArcherPos);
        olc::vi2d ArcherSize(64, 64);

        if (Goop.x < ArcherPos.x + ArcherSize.x &&
            Goop.x + GoopSize.x > Archer.x &&
            Goop.y < Archer.y + ArcherSize.y &&
            Goop.y + GoopSize.y > Archer.y) {
            GameState = DEAD;
        }
    }
    void MoveGoop(float GoopSpeed, float fElapsedTime) {
        // Calculate direction towards the player
        olc::vf2d dir = (ArcherPos - GoopPos[0]).norm();

        // Calculate the new position based on direction and speed
        GoopPos[0] += dir * GoopSpeed;

        // Draw the Goop
        for (int k = 0; k < GoopPos.size(); k++) {
            if (dir.x < 0) {
                DrawDecal({ GoopPos[k] }, GoopLeftDecal, { 2.0f, 2.0f });
            }
            if (dir.x > 0) {
                DrawDecal({ GoopPos[k] }, GoopRightDecal, { 2.0f, 2.0f });
            }
        }

        // Player+Goop Check
        PlayerGoopCheck();
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
                    GoopPos.erase(GoopPos.begin() + o);
                    score++;
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
            olc::vf2d vel = (targetPos - olc::vf2d(ArcherPos)).norm() * 500.0f;


            // Store the arrow's position and velocity
            arrowPos.push_back({ ArcherPos.x + 15, ArcherPos.y + 15 });
            arrowVel.push_back(vel);
        }
        DrawArrow(fElapsedTime);
    }
    void UserInput(float ArcherSpeed) {
        if ((GetKey(olc::Key::LEFT).bHeld || (GetKey(olc::Key::A).bHeld)) && ArcherPos.x < 905 && ArcherPos.x > -5) {
            ArcherPos.x -= ArcherSpeed;
        }
        if ((GetKey(olc::Key::RIGHT).bHeld || (GetKey(olc::Key::D).bHeld)) && ArcherPos.x < 920 && ArcherPos.x > -5) {
            ArcherPos.x += ArcherSpeed;
        }
        if ((GetKey(olc::Key::UP).bHeld || (GetKey(olc::Key::W).bHeld)) && ArcherPos.y < 479 && ArcherPos.y > -5) {
            ArcherPos.y -= ArcherSpeed;
        }
        if ((GetKey(olc::Key::DOWN).bHeld || (GetKey(olc::Key::S).bHeld)) && ArcherPos.y < 479 && ArcherPos.y > -5) {
            ArcherPos.y += ArcherSpeed;
        }
        if (ArcherPos.x > 905) {
            ArcherPos.x = 904;
        }
        if (ArcherPos.x < -5) {
            ArcherPos.x = -4;
        }
        if (ArcherPos.y > 479) {
            ArcherPos.y = 478;
        }
        if (ArcherPos.y < -5) {
            ArcherPos.y = -4;
        }

    }
    bool OnUserUpdate(float fElapsedTime) override {
        if (GameState == MENU) {
            MainMenu();
        }
        if (GameState == QUIT) {
            return false;
        }
        if (GameState == GAME) {
            float ArcherSpeed = 200 * fElapsedTime;
            float GoopSpeed = 250 * fElapsedTime;
            SpawnGoop();
            //Draw Grass
            DrawGrass();
            MoveGoop(GoopSpeed, fElapsedTime);
            //Draw Archer
            DrawDecal({ ArcherPos }, ArcherRightDecal, { (float)2, (float)2 });
            UserInput(ArcherSpeed);
            ShootArrow(fElapsedTime);

            return true;
        }
        if (GameState == DEAD) {
            ArcherDead();
            DeadUserInputs();
            return true;
        }
    }

private:
    bool OnUserCreate() override {
        //Spawn Archer in center
        ArcherPos.x = 448.0f;
        ArcherPos.y = 238.0f;
        //Sprites
        ArcherRight = std::make_unique<olc::Sprite>("./Sprites/ArcherRight.png");
        Grass = std::make_unique<olc::Sprite>("./Sprites/Grass.png");
        GoopRight = std::make_unique<olc::Sprite>("./Sprites/GoopRight.png");
        GoopLeft = std::make_unique<olc::Sprite>("./Sprites/GoopLeft.png");
        Arrow = std::make_unique<olc::Sprite>("./Sprites/Pumpkin.png");
        //Decals
        GrassDecal = new olc::Decal(Grass.get());
        GoopRightDecal = new olc::Decal(GoopRight.get());
        GoopLeftDecal = new olc::Decal(GoopLeft.get());
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
