#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <iostream>
#include <vector>

class GoopSlayer : public olc::PixelGameEngine {
public:
    //Sprites
    std::unique_ptr<olc::Sprite> SpookyLogo;
    std::unique_ptr<olc::Sprite> Spiderweb1;
    std::unique_ptr<olc::Sprite> Spiderweb2;
    std::unique_ptr<olc::Sprite> Spiderweb3;
    std::unique_ptr<olc::Sprite> Spiderweb4;
    std::unique_ptr<olc::Sprite> GoopRight;
    std::unique_ptr<olc::Sprite> GoopLeft;
    std::unique_ptr<olc::Sprite> Grass;
    std::unique_ptr<olc::Sprite> ArcherRight;
    std::unique_ptr<olc::Sprite> Arrow;
    //Decals
    olc::Decal* SpookyLogoDecal;
    olc::Decal* Spiderweb1Decal;
    olc::Decal* Spiderweb2Decal;
    olc::Decal* Spiderweb3Decal;
    olc::Decal* Spiderweb4Decal;
    olc::Decal* GrassDecal;
    olc::Decal* GoopRightDecal;
    olc::Decal* GoopLeftDecal;
    olc::Decal* ArcherRightDecal;
    olc::Decal* ArrowDecal;
    //Goop variables
    std::vector<olc::vf2d> GoopVel;
    std::vector<olc::vf2d> GoopPos;
    //Arrow variables
    std::vector<olc::vf2d> arrowPos;
    std::vector<olc::vf2d> arrowVel;
    //Archer variables
    olc::vf2d ArcherPos = { 448.0f, 238.0f };
    int score = 0;
    //Menu variables
    int menu = 0;
    enum GameStateEnum { MENU, DEAD, GAME, PAUSE, QUIT };
    GameStateEnum GameState = MENU;
    //Wave variables
    int Wave = 1;
    float Time = 0;
    bool WaveDisplay = true;
    int KilledGoops = 0;
    int MaxGoops = 1;
    int MaxGoopIncrease = 0;
    int TotalGoops = 3;
    bool GrassDrawn = false;

    GoopSlayer() {
        sAppName = "GoopSlayer";
    }

    void WaveCheck() {
        if (KilledGoops == TotalGoops) {
            KilledGoops = 0;
            Time = 0.0f;
            WaveDisplay = true;
            Wave++;
            TotalGoops += 2;
            if (MaxGoops < 4 && MaxGoopIncrease == 3) {
                MaxGoops++;
                MaxGoopIncrease = 0;
            }
            if (MaxGoopIncrease < 3) {
                MaxGoopIncrease++;
            }
        }
    }
    void DisplayWave() {
        std::string WaveString = std::to_string(Wave);
        DrawStringDecal({ (float)ScreenWidth() / 2 - 134, (float)ScreenHeight() / 3 + 3 }, "Wave", olc::BLACK, { 5.0f, 5.0f });
        DrawStringDecal({ (float)ScreenWidth() / 2 - 130, (float)ScreenHeight() / 3 }, "Wave", olc::WHITE, { 5.0f, 5.0f });
        DrawStringDecal({ (float)ScreenWidth() / 2 + 56, (float)ScreenHeight() / 3 + 3 }, WaveString, olc::BLACK, { 5.0f, 5.0f });
        DrawStringDecal({ (float)ScreenWidth() / 2 + 60, (float)ScreenHeight() / 3 }, WaveString, olc::WHITE, { 5.0f, 5.0f });
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
        std::string ScoreString = std::to_string(score);
        DrawString(ScreenWidth() / 5, ScreenHeight() / 9, "You've been slain!", olc::MAGENTA, 4);
        DrawString(ScreenWidth() / 3 + 70, ScreenHeight() / 4, "Score:", olc::GREEN, 4);
        DrawString(ScreenWidth() / 3 + 130, ScreenHeight() / 3, ScoreString, olc::GREEN, 4);
        DrawString(ScreenWidth() / 7, ScreenHeight() / 2, "Press 'SPACE' to retry", olc::BLUE, 4);
    }
    void DrawSpiderwebs() {
        DrawDecal({ 895.0f, 475.0f }, Spiderweb2Decal, { 2.0f, 2.0f });
        DrawDecal({ 0.0f, 477.0f }, Spiderweb1Decal, { 2.0f, 2.0f });
        DrawDecal({ 0.0f, 0.0f }, Spiderweb3Decal, { 2.0f, 2.0f });
        DrawDecal({ 864.0f, -5.0f }, Spiderweb4Decal, { 3.0f, 3.0f });
    }
    void MainMenu() {
        if (menu == 0) {
            DrawSpiderwebs();
            DrawDecal({ (float)ScreenWidth() / 4 + 30, -30.0f }, SpookyLogoDecal, { 3.0f, 3.0f });
            DrawDecal({ (float)ScreenWidth() - 220, (float)ScreenHeight() / 3 - 50 }, ArrowDecal, { 4.0f, 4.0f });
            DrawDecal({ (float)ScreenWidth() / 8 - 20, (float)ScreenHeight() / 3 - 50 }, GoopRightDecal, { 3.0f, 3.0f });
            DrawString(ScreenWidth() / 5 + 30, ScreenHeight() / 3, "Goop Slayer", olc::MAGENTA, 6);
            DrawString(ScreenWidth() / 3, ScreenHeight() / 3 + 90, ">> Play", olc::GREEN, 4);
            DrawString(ScreenWidth() / 3 + 96, ScreenHeight() / 2 + 70, "Quit", olc::RED, 4);
        }
        else if (menu == 1) {
            DrawSpiderwebs();
            DrawDecal({ (float)ScreenWidth() / 4 + 30, -30.0f }, SpookyLogoDecal, { 3.0f, 3.0f });
            DrawDecal({ (float)ScreenWidth() - 220, (float)ScreenHeight() / 3 - 50 }, ArrowDecal, { 4.0f, 4.0f });
            DrawDecal({ (float)ScreenWidth() / 8 - 20, (float)ScreenHeight() / 3 - 50 }, GoopRightDecal, { 3.0f, 3.0f });
            DrawString(ScreenWidth() / 5 + 30, ScreenHeight() / 3, "Goop Slayer", olc::MAGENTA, 6);
            DrawString(ScreenWidth() / 3 + 96, ScreenHeight() / 3 + 90, "Play", olc::GREEN, 4);
            DrawString(ScreenWidth() / 3, ScreenHeight() / 2 + 70, ">> Quit", olc::RED, 4);
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
            MaxGoops = 1;
            Wave = 1;
            Time = 0;
            KilledGoops = 0;
            TotalGoops = 3;
            WaveDisplay = true;

            GameState = GAME;
        }
        else if (GetKey(olc::Key::ENTER).bPressed && menu == 1) {
            GameState = QUIT;
        }
    }
    bool DrawGrass() {
        for (int x = 0; x < 960; x += 32) {
            for (int y = 0; y < 540; y += 32) {
                DrawDecal({ (float)x, (float)y }, GrassDecal);
            }
        }
        return GrassDrawn = true;
    }
    void SpawnGoop() {
        if (GoopPos.size() == 0) {
            //Goop random coord gen (walls) (spawns max goops)
            for (int k = 0; k < MaxGoops; k++) {
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
        for (int k = 0; k < GoopPos.size(); k++) {
            // Calculate direction towards the player
            olc::vf2d dir = (ArcherPos - GoopPos[k]).norm();

            // Calculate the new position based on direction and speed
            GoopPos[k] += dir * GoopSpeed;

            // Draw the Goop
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
                    KilledGoops++;
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
            Clear(olc::BLACK);
            //Draw Grass
            GrassDrawn = DrawGrass();

            Time += fElapsedTime;
            float ArcherSpeed = 200 * fElapsedTime;
            float GoopSpeed = 210 * fElapsedTime;

            //Draw Archer
            DrawDecal({ ArcherPos }, ArcherRightDecal, { 2.0f, 2.0f });
            if (Time <= 5.0f && WaveDisplay == true) {
                DisplayWave();
            }
            UserInput(ArcherSpeed);
            ShootArrow(fElapsedTime);
            WaveCheck();
            if (Time >= 5.0f && WaveDisplay == true) {
                WaveDisplay = false;
                Time = 0.0f;
            }
            if (Time >= 1.0f && WaveDisplay == false) {
                //SpawnGoop
                SpawnGoop();
                MoveGoop(GoopSpeed, fElapsedTime);
            }
            //Draw webs
            DrawSpiderwebs();
            return true;
        }
        if (GameState == DEAD) {
            DrawSpiderwebs();
            ArcherDead();
            DeadUserInputs();
            return true;
        }
    }

private:
    bool OnUserCreate() override {
        srand(time(NULL));
        //Sprites
        SpookyLogo = std::make_unique<olc::Sprite>("./Sprites/Spooky.png");
        Spiderweb1 = std::make_unique<olc::Sprite>("./Sprites/Spiderweb1.png");
        Spiderweb2 = std::make_unique<olc::Sprite>("./Sprites/Spiderweb2.png");
        Spiderweb3 = std::make_unique <olc::Sprite>("./Sprites/SpiderwebTL_WSpider.png");
        Spiderweb4 = std::make_unique <olc::Sprite>("./Sprites/Brokenweb.png");
        ArcherRight = std::make_unique<olc::Sprite>("./Sprites/ArcherRight.png");
        Grass = std::make_unique<olc::Sprite>("./Sprites/Grass.png");
        GoopRight = std::make_unique<olc::Sprite>("./Sprites/GoopRight.png");
        GoopLeft = std::make_unique<olc::Sprite>("./Sprites/GoopLeft.png");
        Arrow = std::make_unique<olc::Sprite>("./Sprites/Pumpkin.png");
        //Decals
        SpookyLogoDecal = new olc::Decal(SpookyLogo.get());
        Spiderweb1Decal = new olc::Decal(Spiderweb1.get());
        Spiderweb2Decal = new olc::Decal(Spiderweb2.get());
        Spiderweb3Decal = new olc::Decal(Spiderweb3.get());
        Spiderweb4Decal = new olc::Decal(Spiderweb4.get());
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
