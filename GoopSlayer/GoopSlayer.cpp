#define OLC_PGE_APPLICATION
#define _USE_MATH_DEFINES
#include "olcPixelGameEngine.h"
#include <iostream>
#include <vector>
#include <cmath>

class GoopSlayer : public olc::PixelGameEngine {
public:
    //Sprites
    std::unique_ptr<olc::Sprite> SkeletonLeft;
    std::unique_ptr<olc::Sprite> SkeletonRight;
    std::unique_ptr<olc::Sprite> PoisonGoopLeft;
    std::unique_ptr<olc::Sprite> PoisonGoopRight;
    std::unique_ptr<olc::Sprite> PoisonBallLeft;
    std::unique_ptr<olc::Sprite> PoisonBallRight;
    std::unique_ptr<olc::Sprite> PoinsonSplatter;
    std::unique_ptr<olc::Sprite> Flashlight;
    std::unique_ptr<olc::Sprite> MenuBackground;
    std::unique_ptr<olc::Sprite> MenuArrow;
    std::unique_ptr<olc::Sprite> Quit;
    std::unique_ptr<olc::Sprite> Play;
    std::unique_ptr<olc::Sprite> Cooldown;
    std::unique_ptr<olc::Sprite> ArrowBarrage;
    std::unique_ptr<olc::Sprite> SkillUI;
    std::unique_ptr<olc::Sprite> GoopSlayerLogo;
    std::unique_ptr<olc::Sprite> SpookyLogo;
    std::unique_ptr<olc::Sprite> Spiderweb1;
    std::unique_ptr<olc::Sprite> Spiderweb2;
    std::unique_ptr<olc::Sprite> Spiderweb3;
    std::unique_ptr<olc::Sprite> Spiderweb4;
    std::unique_ptr<olc::Sprite> GoopRight;
    std::unique_ptr<olc::Sprite> GoopLeft;
    std::unique_ptr<olc::Sprite> Grass;
    std::unique_ptr<olc::Sprite> ArcherLeft;
    std::unique_ptr<olc::Sprite> ArcherRight;
    std::unique_ptr<olc::Sprite> PumpkinArrow;
    std::unique_ptr<olc::Sprite> Arrow;
    //Decals
    olc::Decal* SkeletonLeftDecal;
    olc::Decal* SkeletonRightDecal;
    olc::Decal* PoisonGoopLeftDecal;
    olc::Decal* PoisonBallLeftDecal;
    olc::Decal* PoisonBallRightDecal;
    olc::Decal* PoisonSplatterDecal;
    olc::Decal* PoisonGoopRightDecal;
    olc::Decal* SkeletonTestDecal;
    olc::Decal* FlashlightDecal;
    olc::Decal* MenuBackgroundDecal;
    olc::Decal* MenuArrowDecal;
    olc::Decal* QuitDecal;
    olc::Decal* PlayDecal;
    olc::Decal* CooldownDecal;
    olc::Decal* ArrowBarrageDecal;
    olc::Decal* SkillUIDecal;
    olc::Decal* GoopSlayerLogoDecal;
    olc::Decal* SpookyLogoDecal;
    olc::Decal* Spiderweb1Decal;
    olc::Decal* Spiderweb2Decal;
    olc::Decal* Spiderweb3Decal;
    olc::Decal* Spiderweb4Decal;
    olc::Decal* GrassDecal;
    olc::Decal* GoopRightDecal;
    olc::Decal* GoopLeftDecal;
    olc::Decal* ArcherLeftDecal;
    olc::Decal* ArcherRightDecal;
    olc::Decal* PumpkinArrowDecal;
    olc::Decal* ArrowDecal;
    //PoisonGoop variables
    std::vector<olc::vf2d> PoisonGoopVel;
    std::vector<olc::vf2d> PoisonGoopPos;
    std::vector<int> PoisonBallShootBool;
    std::vector<float> PoisonBallTimer;
    int KilledPoison;
    //PoisonGoop Ball variables
    std::vector<olc::vf2d> PoisonBallVel;
    std::vector<olc::vf2d> PoisonBallPos;
    std::vector<int> PoisonBallSplash;
    std::vector<olc::vf2d> PoisonBallSplashPos;
    std::vector<float> PoisonBallSplashTimer;
    std::vector<olc::vf2d> PoisonBallArcherPos;
    std::vector<int> PoisonBallArcherPosBool;
    //Goop variables
    std::vector<olc::vf2d> GoopVel;
    std::vector<olc::vf2d> GoopPos;
    int KilledGoops = 0;
    //Skeleton variables
    std::vector<olc::vf2d> SkeleVel;
    std::vector<olc::vf2d> SkelePos;
    int KilledSkeles = 0;
    //Skeleton arrow variables
    std::vector<olc::vf2d> SkeleArrowPos;
    std::vector<olc::vf2d> SkeleArrowVel;
    std::vector<int> SkeleShoot;
    std::vector<float> SkeleShootTimer;
    //Player Arrow variables
    std::vector<olc::vf2d> arrowPos;
    std::vector<olc::vf2d> arrowVel;
    //Archer variables
    olc::vf2d ArcherPos = { 448.0f, 238.0f };
    //True = ArcherRight, False = ArcherLeft
    bool ArcherDir = true;
    //Menu variables
    int score = 0;
    int menu = 0;
    enum GameStateEnum { MENU, DEAD, GAME, PAUSE, QUIT, DEBUG };
    GameStateEnum GameState = MENU;
    //Wave variables
    //MaxEnemies/TotalEnemies [0] = Goop, [1] = Skeleton, [2] = PoisonGoop
    std::vector<int> MaxEnemies;
    std::vector<int> TotalEnemies;
    int Wave = 1;
    float Time = 0;
    bool WaveDisplay = true;
    std::vector<int> WaveCounter;
    //Skill variables
    bool SkillUsed = false;
    float CooldownNum = 0;
    float SkillCooldownTimer = 0;
    //General variables
    bool GrassDrawn = false;

    GoopSlayer() {
        sAppName = "GoopSlayer";
    }
    //Enemies
    void SpawnSkeleton() {
        if (SkelePos.size() == 0 && KilledSkeles < TotalEnemies[1]) {
            //Goop random coord gen (walls) (spawns max skeletons)
            for (int k = 0; k < MaxEnemies[1]; k++) {
                int SideSkeleNum = rand() % 4;

                if (SideSkeleNum == 0) {
                    float SkeleYNum = rand() % 575;
                    SkelePos.push_back({ 0.f, SkeleYNum });
                }
                if (SideSkeleNum == 1) {
                    float SkeleXNum = rand() % 1023;
                    SkelePos.push_back({ SkeleXNum, 0 });
                }
                if (SideSkeleNum == 2) {
                    float SkeleXNum = rand() % 1023;
                    SkelePos.push_back({ SkeleXNum, 575 });
                }
                if (SideSkeleNum == 3) {
                    float SkeleYNum = rand() % 575;
                    SkelePos.push_back({ 1023, SkeleYNum });
                }
                SkeleShoot.push_back(0);
                SkeleShootTimer.push_back(0);
            }
        }
    }
    void SpawnGoop() {
        if (GoopPos.size() == 0 && KilledGoops < TotalEnemies[0]) {
            //Goop random coord gen (walls) (spawns max goops)
            for (int k = 0; k < MaxEnemies[0]; k++) {
                int SideGoopNum = rand() % 4;

                if (SideGoopNum == 0) {
                    float GoopYNum = rand() % 575;
                    GoopPos.push_back({ 0.f, GoopYNum });
                }
                if (SideGoopNum == 1) {
                    float GoopXNum = rand() % 1023;
                    GoopPos.push_back({ GoopXNum, 0 });
                }
                if (SideGoopNum == 2) {
                    float GoopXNum = rand() % 1023;
                    GoopPos.push_back({ GoopXNum, 575 });
                }
                if (SideGoopNum == 3) {
                    float GoopYNum = rand() % 575;
                    GoopPos.push_back({ 1023, GoopYNum });
                }
            }
        }
    }
    void SpawnPoisonGoop() {
        if (PoisonGoopPos.size() == 0 && KilledPoison < TotalEnemies[2]) {
            //Goop random coord gen (walls) (spawns max goops)
            for (int k = 0; k < MaxEnemies[2]; k++) {
                int SideGoopNum = rand() % 4;

                if (SideGoopNum == 0) {
                    float GoopYNum = rand() % 575;
                    PoisonGoopPos.push_back({ 0.f, GoopYNum });
                }
                if (SideGoopNum == 1) {
                    float GoopXNum = rand() % 1023;
                    PoisonGoopPos.push_back({ GoopXNum, 0 });
                }
                if (SideGoopNum == 2) {
                    float GoopXNum = rand() % 1023;
                    PoisonGoopPos.push_back({ GoopXNum, 575 });
                }
                if (SideGoopNum == 3) {
                    float GoopYNum = rand() % 575;
                    PoisonGoopPos.push_back({ 1023, GoopYNum });
                }
                PoisonBallShootBool.push_back(0);
                PoisonBallTimer.push_back(4.0f);
            }
        }
    }
    void MoveSkeleton(float SkeletonSpeed, float fElapsedTime) {
        //Iterates through all Skeletons
        for (int k = 0; k < SkelePos.size(); k++) {
            // Calculate direction towards the player
            olc::vf2d dir = olc::vf2d(ArcherPos - SkelePos[k]);

            float distance = dir.mag();
            //If Skeleton is outside 200 pixel range of user (add 5f to stop vibrating)
            if (distance > 205.0f) {
                //Calc new position
                SkelePos[k] += dir.norm() * SkeletonSpeed;
                SkeleShoot[k] = 0;
            }
            //If within 200 pixel range of user (remove 5f to stop vibrating)
            else if (distance <= 195.0f && distance > 5.0f) {
                //Calc new position
                SkelePos[k] -= dir.norm() * SkeletonSpeed;
                SkeleShoot[k] = 1;
            }
            if (distance <= 220.0f) {
                SkeleShoot[k] = 1;
            }
            // Draw the Skeleton
            if (dir.x < 0) {
                DrawDecal({ SkelePos[k] }, SkeletonLeftDecal, { 2.0f, 2.0f });
            }
            if (dir.x > 0) {
                DrawDecal({ SkelePos[k] }, SkeletonRightDecal, { 2.0f, 2.0f });
            }
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
    }
    void MovePoisonGoop(float PoisonGoopSpeed, float fElapsedTime) {
        for (int k = 0; k < PoisonGoopPos.size(); k++) {
            // Calculate direction towards the player
            olc::vf2d dir = (ArcherPos - PoisonGoopPos[k]);

            float distance = dir.mag();
            //If PoisonGoop is outside 200 pixel range of user (add 5f to stop vibrating)
            if (distance > 305.0f) {
                //Calc new position
                PoisonGoopPos[k] += dir.norm() * PoisonGoopSpeed;
                PoisonBallShootBool[k] = 0;
            }
            if (distance <= 325.0f) {
                PoisonBallShootBool[k] = 1;
            }

            // Draw the PoisonGoop
            if (dir.x < 0) {
                DrawDecal({ PoisonGoopPos[k] }, PoisonGoopLeftDecal, { 2.0f, 2.0f });
            }
            if (dir.x > 0) {
                DrawDecal({ PoisonGoopPos[k] }, PoisonGoopRightDecal, { 2.0f, 2.0f });
            }
        }
    }
    void DrawSkeleArrow(float fElapsedTime) {
        for (size_t i = 0; i < SkeleArrowPos.size(); i++) {
            SkeleArrowPos[i] += SkeleArrowVel[i] * fElapsedTime;

            //Arrow off-screen
            if (SkeleArrowPos[i].x < 0 || SkeleArrowPos[i].x >= ScreenWidth() || SkeleArrowPos[i].y < 0 || SkeleArrowPos[i].y >= ScreenHeight()) {
                SkeleArrowPos.erase(SkeleArrowPos.begin() + i);
                SkeleArrowVel.erase(SkeleArrowVel.begin() + i);
                i--;
            }
            else {
                //Angle of roation
                float angle = atan2f(SkeleArrowVel[i].y, SkeleArrowVel[i].x);
                //Draw arrow
                DrawRotatedDecal(SkeleArrowPos[i], ArrowDecal, angle, { 1.0f, 1.0f }, { 1.0f, 1.0f }, olc::WHITE);
            }
        }
    }
    void DrawPoisonBall(float fElapsedTime) {
        for (int i = 0; i < PoisonBallPos.size(); i++) {
            PoisonBallPos[i] += PoisonBallVel[i] * fElapsedTime;
            olc::vf2d dir = (ArcherPos - PoisonBallPos[i]);

            //When ball first thrown, save ArcherPos
            if (PoisonBallArcherPosBool[i] == 0) {
                PoisonBallArcherPos.push_back(ArcherPos);
                PoisonBallArcherPosBool[i] = 1;
            }
            //Arrow off-screen
            if (PoisonBallPos[i].x < 0 || PoisonBallPos[i].x >= ScreenWidth() || PoisonBallPos[i].y < 0 || PoisonBallPos[i].y >= ScreenHeight()) {
                PoisonBallPos.erase(PoisonBallPos.begin() + i);
                PoisonBallVel.erase(PoisonBallVel.begin() + i);
                i--;
            }
            else {
                //Draw arrow
                if (dir.x < 0) {
                    DrawDecal(PoisonBallPos[i], PoisonBallLeftDecal, { 1.0f, 1.0f });
                }
                if (dir.x > 0) {
                    DrawDecal(PoisonBallPos[i], PoisonBallRightDecal, { 1.0f, 1.0f });
                }
            }
        }
    }
    void PoisonBallShoot(float fElapsedTime) {
        for (int k = 0; k < PoisonGoopPos.size(); k++) {
            if (PoisonBallShootBool[k] == true && PoisonBallTimer[k] >= 4.0f) {
                olc::vf2d UpdatedArcherPos = { ArcherPos.x + 8, ArcherPos.y + 8 };

                // Calculate velocity towards the target
                olc::vf2d vel = (UpdatedArcherPos - olc::vf2d(PoisonGoopPos[k])).norm() * 400.0f;

                // Store the arrow's position and velocity
                PoisonBallPos.push_back({ PoisonGoopPos[k].x + 24, PoisonGoopPos[k].y + 24 });
                PoisonBallVel.push_back(vel);
                PoisonBallTimer[k] = 0;
                PoisonBallArcherPosBool.push_back(0); 
                PoisonBallSplash.push_back(0);
            }
            DrawPoisonBall(fElapsedTime);
        }
    }
    void doPoisonBallSplash() {
        for (int i = 0; i < PoisonBallPos.size(); i++) {
            //Archer variables
            olc::vi2d Archer(PoisonBallArcherPos[i]);
            olc::vi2d ArcherSize(64, 64);
            //Ball variables
            olc::vi2d Ball(PoisonBallPos[i]);
            olc::vi2d BallSize(64, 64);

            //Check if Poison balls hit player

            if (Ball.x < ArcherPos.x + ArcherSize.x &&
                Ball.x + BallSize.x > Archer.x &&
                Ball.y < Archer.y + ArcherSize.y &&
                Ball.y + BallSize.y > Archer.y) {
                PoisonBallSplash[i] = 1;
                PoisonBallSplashPos.push_back(PoisonBallPos[i]);
                PoisonBallSplashTimer.push_back(0);
                PoisonBallPos.erase(PoisonBallPos.begin() + i);
                PoisonBallVel.erase(PoisonBallVel.begin() + i);
                PoisonBallArcherPosBool.erase(PoisonBallArcherPosBool.begin() + i);
                PoisonBallArcherPos.erase(PoisonBallArcherPos.begin() + i);
            }
        }
    }
    void SkeletonShoot(float fElapsedTime) {
        for (int k = 0; k < SkelePos.size(); k++) {
            if (SkeleShoot[k] == true && SkeleShootTimer[k] >= 1.5f) {
                olc::vf2d UpdatedArcherPos = { ArcherPos.x + 8, ArcherPos.y + 8 };
                // Calculate velocity towards the target
                olc::vf2d vel = (UpdatedArcherPos - olc::vf2d(SkelePos[k])).norm() * 400.0f;

                // Store the arrow's position and velocity
                SkeleArrowPos.push_back({ SkelePos[k].x + 24, SkelePos[k].y + 24 });
                SkeleArrowVel.push_back(vel);
                SkeleShootTimer[k] = 0;
            }
            DrawSkeleArrow(fElapsedTime);
        }
    }
    void MoveEnemies(float PoisonGoopSpeed, float GoopSpeed, float SkeletonSpeed, float fElapsedTime) {
        SpawnGoop();
        SpawnSkeleton();
        SpawnPoisonGoop();
        MoveGoop(GoopSpeed, fElapsedTime);
        MoveSkeleton(SkeletonSpeed, fElapsedTime);
        SkeletonShoot(fElapsedTime);
        MovePoisonGoop(PoisonGoopSpeed, fElapsedTime);
        PoisonBallShoot(fElapsedTime);
        doPoisonBallSplash();
    }
    void ArrowEnemyCheck() {
        //Iterates through all arrows
        for (int k = 0; k < arrowPos.size(); k++) {
            olc::vi2d Arrow(arrowPos[k]);
            olc::vi2d ArrowSize(30, 30);
            //Checks if arrows hit any goops
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
            //Checks if arrows hit any skeletons
            for (int o = 0; o < SkelePos.size(); o++) {
                olc::vi2d Skeleton(SkelePos[o]);
                olc::vi2d SkeleSize(63, 63);

                if (Arrow.x < Skeleton.x + SkeleSize.y &&
                    Arrow.x + ArrowSize.x > Skeleton.x &&
                    Arrow.y < Skeleton.y + SkeleSize.y &&
                    Arrow.y + ArrowSize.y > Skeleton.y) {
                    arrowPos.erase(arrowPos.begin() + k);
                    arrowVel.erase(arrowVel.begin() + k);
                    SkelePos.erase(SkelePos.begin() + o);
                    SkeleShoot.erase(SkeleShoot.begin() + o);
                    SkeleShootTimer.erase(SkeleShootTimer.begin() + o);
                    score++;
                    KilledSkeles++;
                }
            }
            //If arrow hit Poison Goop
            for (int o = 0; o < PoisonGoopPos.size(); o++) {
                olc::vi2d PoisonGoop(PoisonGoopPos[o]);
                olc::vi2d PoisonSize(63, 63);

                if (Arrow.x < PoisonGoop.x + PoisonSize.y &&
                    Arrow.x + ArrowSize.x > PoisonGoop.x &&
                    Arrow.y < PoisonGoop.y + PoisonSize.y &&
                    Arrow.y + ArrowSize.y > PoisonGoop.y) {
                    arrowPos.erase(arrowPos.begin() + k);
                    arrowVel.erase(arrowVel.begin() + k);
                    PoisonGoopPos.erase(PoisonGoopPos.begin() + o);
                    PoisonBallShootBool.erase(PoisonBallShootBool.begin() + o);
                    score++;
                    KilledPoison++;
                }
            }
        }
    }
    //Player
    void ResetVariables() {
        //Remove poison goops
        for (int k = 0; k < PoisonGoopPos.size(); k++) {
            PoisonGoopPos.erase(PoisonGoopPos.begin() + k);
            PoisonBallShootBool.erase(PoisonBallShootBool.begin() + k);
            PoisonBallTimer.erase(PoisonBallTimer.begin() + k);
        }
        //Remove goops
        for (int k = 0; k < GoopPos.size(); k++) {
            GoopPos.erase(GoopPos.begin() + k);
        }
        //Remove player arrows
        for (int k = 0; k < arrowPos.size(); k++) {
            arrowPos.erase(arrowPos.begin() + k);
            arrowVel.erase(arrowVel.begin() + k);
        }
        //Remove Skeletons
        for (int k = 0; k < SkelePos.size(); k++) {
            SkelePos.erase(SkelePos.begin() + k);
            SkeleShoot.erase(SkeleShoot.begin() + k);
            SkeleShootTimer.erase(SkeleShootTimer.begin() + k);
        }
        //Remove Poison Balls
        for (int k = 0; k < PoisonBallPos.size(); k++) {
            PoisonBallPos.erase(PoisonBallPos.begin() + k);
            PoisonBallVel.erase(PoisonBallVel.begin() + k);
            for (int o = 0; o < PoisonBallArcherPos.size(); o++) {
                PoisonBallArcherPos.erase(PoisonBallArcherPos.begin() + k);
            }
            for (int i = 0; i < PoisonBallSplash.size(); i++) {
                PoisonBallSplash.erase(PoisonBallSplash.begin() + i);
            }
            for (int u = 0; u < PoisonBallSplashTimer.size(); u++) {
                PoisonBallSplashTimer.erase(PoisonBallSplashTimer.begin() + u);
            }
            for (int y = 0; y < PoisonBallSplashPos.size(); y++) {
                PoisonBallSplashPos.erase(PoisonBallSplashPos.begin() + y);
            }
        }
        //Remove Skeleton arrows
        for (int k = 0; k < SkeleArrowPos.size(); k++) {
            SkeleArrowPos.erase(SkeleArrowPos.begin() + k);
            SkeleArrowVel.erase(SkeleArrowVel.begin() + k);
        }
        ArcherPos.x = 448.0f;
        ArcherPos.y = 238.0f;
        score = 0;
        Wave = 1;
        Time = 0;
        KilledGoops = 0;
        KilledSkeles = 0;
        KilledPoison = 0;
        MaxEnemies[0] = 1;
        MaxEnemies[1] = 0;
        MaxEnemies[2] = 1;
        TotalEnemies[0] = 3;
        TotalEnemies[1] = 0;
        TotalEnemies[2] = 1;
        WaveDisplay = true;
        SkillCooldownTimer = 0;
        SkillUsed = false;
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
    void PlayerDeadCheck() {
        //Archer variables
        olc::vi2d Archer(ArcherPos);
        olc::vi2d ArcherSize(60, 60);
        //Goop check
        for (int k = 0; k < GoopPos.size(); k++) {
            //Goop variables
            olc::vi2d Goop(GoopPos[k]);
            olc::vi2d GoopSize(64, 64);

            if (Goop.x < ArcherPos.x + ArcherSize.x &&
                Goop.x + GoopSize.x > Archer.x &&
                Goop.y < Archer.y + ArcherSize.y &&
                Goop.y + GoopSize.y > Archer.y) {
                GameState = DEAD;
            }
        }
        //PoisonGoop Check
        for (int k = 0; k < PoisonGoopPos.size(); k++) {
            //Poison Goop variables
            olc::vi2d Poison(PoisonGoopPos[k]);
            olc::vi2d PoisonSize(64, 64);

            if (Poison.x < ArcherPos.x + ArcherSize.x &&
                Poison.x + PoisonSize.x > Archer.x &&
                Poison.y < Archer.y + ArcherSize.y &&
                Poison.y + PoisonSize.y > Archer.y) {
                GameState = DEAD;
            }
        }
        //Check if Poison balls hit player
        for (int k = 0; k < PoisonBallPos.size(); k++) {
            //Ball variables
            olc::vi2d Ball(PoisonBallPos[k]);
            olc::vi2d BallSize(32, 32);

            if (Ball.x < ArcherPos.x + ArcherSize.x &&
                Ball.x + BallSize.x > Archer.x &&
                Ball.y < Archer.y + ArcherSize.y &&
                Ball.y + BallSize.y > Archer.y) {
                GameState = DEAD;
            }
        }
        //Check if skeleton arrow hits player
        for (int k = 0; k < SkeleArrowPos.size(); k++) {
            //Skele variables
            olc::vi2d SkeleArrow(SkeleArrowPos[k]);
            olc::vi2d SkeleArrowSize(32, 32);

            if (SkeleArrow.x < ArcherPos.x + ArcherSize.x &&
                SkeleArrow.x + SkeleArrowSize.x > Archer.x &&
                SkeleArrow.y < Archer.y + ArcherSize.y &&
                SkeleArrow.y + SkeleArrowSize.y > Archer.y) {
                GameState = DEAD;
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
                DrawRotatedDecal(arrowPos[i], PumpkinArrowDecal, angle, { 1.0f, 1.0f }, { 1.0f, 1.0f }, olc::WHITE);

                //Arrow+Goop Check
                ArrowEnemyCheck();
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
            arrowPos.push_back({ ArcherPos.x + 32, ArcherPos.y + 32 });
            arrowVel.push_back(vel);
        }
        DrawArrow(fElapsedTime);
    }
    void SpawnArrowRing(float fElapsedTime) {
        float angleIncrement = 360.0f / 12.0f; // Divide 360 degrees into 12 directions

        for (int i = 0; i < 12; i++) {
            // Calculate the direction vector for each arrow
            float angle = i * angleIncrement;
            olc::vf2d direction = { cosf(M_PI * angle / 180.0f), sinf(M_PI * angle / 180.0f) };

            // Calculate the velocity of the arrow
            olc::vf2d vel = direction * 500.0f;

            // Store the arrow's position and velocity
            arrowPos.push_back({ ArcherPos.x + 15, ArcherPos.y + 15 });
            arrowVel.push_back(vel);
        }
    }
    void UserInput(float ArcherSpeed, float fElapsedTime) {
        if ((GetKey(olc::Key::LEFT).bHeld || (GetKey(olc::Key::A).bHeld)) && ArcherPos.x < 1024 && ArcherPos.x > -5) {
            ArcherPos.x -= ArcherSpeed;
            ArcherDir = false;
        }
        if ((GetKey(olc::Key::RIGHT).bHeld || (GetKey(olc::Key::D).bHeld)) && ArcherPos.x < 1024 && ArcherPos.x > -5) {
            ArcherPos.x += ArcherSpeed;
            ArcherDir = true;
        }
        if ((GetKey(olc::Key::UP).bHeld || (GetKey(olc::Key::W).bHeld)) && ArcherPos.y < 575 && ArcherPos.y > -5) {
            ArcherPos.y -= ArcherSpeed;
        }
        if ((GetKey(olc::Key::DOWN).bHeld || (GetKey(olc::Key::S).bHeld)) && ArcherPos.y < 575 && ArcherPos.y > -5) {
            ArcherPos.y += ArcherSpeed;
        }
        if (ArcherPos.x > 960) {
            ArcherPos.x = 959;
        }
        if (ArcherPos.x < -5) {
            ArcherPos.x = -4;
        }
        if (ArcherPos.y > 512) {
            ArcherPos.y = 511;
        }
        if (ArcherPos.y < -5) {
            ArcherPos.y = -4;
        }
        if (GetKey(olc::Key::E).bPressed && SkillUsed == false && Wave >= 1) {
            SpawnArrowRing(fElapsedTime);
            SkillUsed = true;
        }
    }
    //Wave
    void WaveCheckDebug() {
        if (KilledGoops >= TotalEnemies[0] && KilledSkeles >= TotalEnemies[1] && KilledPoison >= TotalEnemies[2]) {
            KilledGoops = 0;
            TotalEnemies[2]++;
            MaxEnemies[2]++;

            Time = 0.0f;
            for (int k = 0; k < SkeleArrowPos.size(); k++) {
                SkeleArrowPos.erase(SkeleArrowPos.begin() + k);
                SkeleArrowVel.erase(SkeleArrowVel.begin() + k);
            }
            WaveDisplay = true;
            Wave++;
            TotalEnemies[0] += 2;
            WaveCounter[0]++;
        }
        if (WaveCounter[0] == 4 && MaxEnemies[0] < 4) {
            MaxEnemies[0]++;
            WaveCounter[0] = 0;
        }
    }
    void WaveCheck() {
        if (KilledGoops >= TotalEnemies[0] && KilledSkeles >= TotalEnemies[1] && KilledPoison >= TotalEnemies[2]) {
            KilledGoops = 0;
            KilledSkeles = 0;
            Time = 0.0f;
            //Remove any skeleton arrows when wave ends
            for (int k = 0; k < SkeleArrowPos.size(); k++) {
                SkeleArrowPos.erase(SkeleArrowPos.begin() + k);
                SkeleArrowVel.erase(SkeleArrowVel.begin() + k);
            }
            //Remove any PoisonBalls when wave ends
            for (int k = 0; k < PoisonBallPos.size(); k++) {
                PoisonBallPos.erase(PoisonBallPos.begin() + k);
                PoisonBallVel.erase(PoisonBallVel.begin() + k);
            }
            WaveDisplay = true;
            WaveCounter[0]++;
            WaveCounter[1]++;
            Wave++;
            //Goop
            //Increase total by 2 every wave until Total == 16
            if (TotalEnemies[0] < 4) {
                TotalEnemies[0] += 2;
            }
            //Skeletons
            //Increase max by one every 2 waves until Max ==  4
            //Increase total by 1 every wave until Total == 14
            //Starting on Wave 3
            if (Wave >= 3) {
                if (MaxEnemies[1] < 4) {
                    WaveCounter[1]++;
                }
                if (TotalEnemies[1] < 14) {
                    TotalEnemies[1]++;
                }
                if (TotalEnemies[1] == 1) {
                    TotalEnemies[1]++;
                    MaxEnemies[1]++;
                }
                if (WaveCounter[1] == 2) {
                    MaxEnemies[1]++;
                    WaveCounter[1] = 0;
                }
            }
        }
        //Goops
        //Increase max by one every 4 waves until Max == 4
        if (WaveCounter[0] == 4 && MaxEnemies[0] < 4) {
            TotalEnemies[0]++;
            WaveCounter[0] = 0;
        }
    }
    void DisplayWave() {
        std::string WaveString = std::to_string(Wave);
        DrawStringDecal({ (float)ScreenWidth() / 2 - 134, (float)ScreenHeight() / 3 + 3 }, "Wave", olc::BLACK, { 5.0f, 5.0f });
        DrawStringDecal({ (float)ScreenWidth() / 2 - 130, (float)ScreenHeight() / 3 }, "Wave", olc::WHITE, { 5.0f, 5.0f });
        DrawStringDecal({ (float)ScreenWidth() / 2 + 56, (float)ScreenHeight() / 3 + 3 }, WaveString, olc::BLACK, { 5.0f, 5.0f });
        DrawStringDecal({ (float)ScreenWidth() / 2 + 60, (float)ScreenHeight() / 3 }, WaveString, olc::WHITE, { 5.0f, 5.0f });
        if (Wave == 6) {
            DrawStringDecal({ (float)ScreenWidth() / 5 - 14, (float)ScreenHeight() / 2 + 3 }, "Unlocked arrow ring!", olc::BLACK, { 4.0f, 4.0f });
            DrawStringDecal({ (float)ScreenWidth() / 5 - 10, (float)ScreenHeight() / 2 }, "Unlocked arrow ring!", olc::WHITE, { 4.0f, 4.0f });
        }
    }
    //UI/Graphics
    void MenuFlashlight() {
        float FlashlightX = GetMouseX();
        float FlashlightY = GetMouseY();
        DrawDecal({ 0.0f, 0.0f }, MenuBackgroundDecal, { 1.0f, 1.0f });
        DrawDecal({ FlashlightX - 128, FlashlightY - 128 }, FlashlightDecal, { 4.0f, 4.0f });
        FillRectDecal({ 0.0f, 0.0f }, { 1024.0f, (float)FlashlightY - 128 }, olc::BLACK);
        FillRectDecal({ 0.0f, 0.0f }, { (float)FlashlightX - 128, 576 }, olc::BLACK);
        FillRectDecal({ (float)FlashlightX + 128, 0.0f }, { (float)ScreenWidth() - (float)FlashlightX + 32, 576.0f }, olc::BLACK);
        FillRectDecal({ 0.0f, (float)FlashlightY + 128 }, { 1024.0f, (float)ScreenHeight() - (float)FlashlightY + 32 }, olc::BLACK);
    }
    void MainMenu() {
        const bool play_hovered = (GetMouseX() >= 440 && GetMouseY() >= 300 && GetMouseX() <= 570 && GetMouseY() <= 365);
        const bool quit_hovered = (GetMouseX() >= 440 && GetMouseY() >= 400 && GetMouseX() <= 570 && GetMouseY() <= 460);
        const olc::vf2d scale = { 1.0f, 1.0f };
        const float play_zoom = play_hovered ? 1.15f : 1.0f;
        const float quit_zoom = quit_hovered ? 1.15f : 1.0f;
        const float play_XCoord = play_hovered ? ScreenWidth() / 3 + 80 : ScreenWidth() / 3 + 90;
        const float play_YCoord = play_hovered ? ScreenHeight() / 3 + 105 : ScreenHeight() / 3 + 110;
        const float quit_XCoord = quit_hovered ? ScreenWidth() / 3 + 85 : ScreenWidth() / 3 + 95;
        const float quit_YCoord = quit_hovered ? ScreenHeight() / 2 + 105 : ScreenHeight() / 2 + 110;

        DrawSpiderwebs();
        DrawDecal({ (float)ScreenWidth() / 4 + 60, (float)ScreenHeight() / 10 - 83 }, SpookyLogoDecal, { 3.0f, 3.0f });
        DrawDecal({ (float)ScreenWidth() - 250, (float)ScreenHeight() / 3 - 30 }, PumpkinArrowDecal, { 4.0f, 4.0f });
        DrawDecal({ (float)ScreenWidth() / 8 - 10, (float)ScreenHeight() / 3 - 30 }, GoopRightDecal, { 3.0f, 3.0f });
        DrawDecal({ (float)ScreenWidth() / 4 - 10, (float)ScreenHeight() / 4 }, GoopSlayerLogoDecal, { 2.0f, 2.0f });
        DrawDecal({ play_XCoord, play_YCoord }, PlayDecal, scale * play_zoom);
        DrawDecal({ quit_XCoord, quit_YCoord }, QuitDecal, scale * quit_zoom);

        int MouseCoordX = GetMouseX();
        int MouseCoordY = GetMouseY();
        std::string MouseCoordXS = std::to_string(MouseCoordX);
        std::string MouseCoordYS = std::to_string(MouseCoordY);
        DrawStringDecal({ 5.0f, 5.0f }, MouseCoordXS, olc::WHITE, { 2.0f, 2.0f });
        DrawStringDecal({ 5.0f, 20.0f }, MouseCoordYS, olc::WHITE, { 2.0f, 2.0f });
        if (GetMouseX() >= 440 && GetMouseY() >= 300 && GetMouseX() <= 570 && GetMouseY() <= 365 && (GetMouse(0).bPressed)) {
            ResetVariables();
            GameState = GAME;
        }
        if (GetMouseX() >= 440 && GetMouseY() >= 400 && GetMouseX() <= 570 && GetMouseY() <= 460 && (GetMouse(0).bPressed)) {
            WaveDisplay = false;
            GameState = QUIT;
        }
        if (GetMouseX() >= 200 && GetMouseY() >= 105 && GetMouseX() <= 240 && GetMouseY() <= 130 && (GetMouse(0).bPressed)) {
            ResetVariables();
            GameState = DEBUG;
        }
    }
    bool DrawGrass() {
        for (int x = 0; x < 1024; x += 32) {
            for (int y = 0; y < 576; y += 32) {
                DrawDecal({ (float)x, (float)y }, GrassDecal);
            }
        }
        return GrassDrawn = true;
    }
    void DrawSpiderwebs() {
        DrawDecal({ 960.0f, 515.0f }, Spiderweb2Decal, { 2.0f, 2.0f });
        DrawDecal({ 0.0f, 515.0f }, Spiderweb1Decal, { 2.0f, 2.0f });
        DrawDecal({ 0.0f, 0.0f }, Spiderweb3Decal, { 2.0f, 2.0f });
        DrawDecal({ 928.0f, -5.0f }, Spiderweb4Decal, { 3.0f, 3.0f });
    }
    void DrawSkillUI(float fElapsedTime) {
        DrawDecal({ (float)ScreenWidth() / 2 - 32, (float)ScreenHeight() - 80 }, SkillUIDecal, { 2.0f, 2.0f });
        DrawDecal({ (float)ScreenWidth() / 2 - 32, (float)ScreenHeight() - 80 }, ArrowBarrageDecal, { 2.0f, 2.0f });
        if (SkillUsed == true) {
            if (CooldownNum < 64.0f) {
                DrawPartialDecal({ (float)ScreenWidth() / 2 - 32, (float)ScreenHeight() - 80 + CooldownNum },
                    { 64.0f, 64.0f - CooldownNum }, CooldownDecal, { (float)ScreenWidth() / 2 - 32, (float)ScreenHeight() - 80 }, { 64.0f, 64.0f });
                CooldownNum += 0.10f;
            }
        }
        if (CooldownNum >= 64.0f) {
            CooldownNum = 0;
            SkillUsed = false;
        }
    }
    //GameStates
    void GameGameState(float fElapsedTime) {
        Clear(olc::BLACK);
        //Draw Grass
        GrassDrawn = DrawGrass();
        //Timers
        for (int k = 0; k < SkelePos.size(); k++) {
            if (SkeleShoot[k] == 1) {
                SkeleShootTimer[k] += fElapsedTime;
            }
        }
        for (int k = 0; k < PoisonGoopPos.size(); k++) {
            if (PoisonBallShootBool[k] == 1) {
                PoisonBallTimer[k] += fElapsedTime;
            }
        }
        Time += fElapsedTime;
        float ArcherSpeed = 200 * fElapsedTime;
        float GoopSpeed = 220 * fElapsedTime;
        float SkeletonSpeed = 240 * fElapsedTime;
        float PoisonGoopSpeed = 180 * fElapsedTime;

        //Draw Archer
        if (ArcherDir == true) {
            DrawDecal({ ArcherPos }, ArcherRightDecal, { 2.0f, 2.0f });
        }
        if (ArcherDir == false) {
            DrawDecal({ ArcherPos }, ArcherLeftDecal, { 2.0f, 2.0f });
        }

        UserInput(ArcherSpeed, fElapsedTime);

        if (Time <= 5.0f && WaveDisplay == true) {
            DisplayWave();
        }
        ShootArrow(fElapsedTime);
        WaveCheck();
        if (Time >= 5.0f && WaveDisplay == true) {
            WaveDisplay = false;
            Time = 0.0f;
        }
        if (Time >= 1.0f && WaveDisplay == false) {
            //Spawn/Move Enemies
            MoveEnemies(PoisonGoopSpeed, GoopSpeed, SkeletonSpeed, fElapsedTime);
            PlayerDeadCheck();
        }
        if (Wave >= 1) {
            DrawSkillUI(fElapsedTime);
        }

        //Draw webs
        DrawSpiderwebs();
    }
    void DebugGameState(float fElapsedTime) {
        Clear(olc::BLACK);
        //Draw Grass
        GrassDrawn = DrawGrass();
        //Timers
        for (int k = 0; k < SkelePos.size(); k++) {
            if (SkeleShoot[k] == 1) {
                SkeleShootTimer[k] += fElapsedTime;
            }
        }
        for (int k = 0; k < PoisonGoopPos.size(); k++) {
            if (PoisonBallShootBool[k] == 1) {
                PoisonBallTimer[k] += fElapsedTime;
            }
        }
        Time += fElapsedTime;
        float ArcherSpeed = 200 * fElapsedTime;
        float GoopSpeed = 220 * fElapsedTime;
        float SkeletonSpeed = 240 * fElapsedTime;
        float PoisonGoopSpeed = 180 * fElapsedTime;

        //Draw Archer
        if (ArcherDir == true) {
            DrawDecal({ ArcherPos }, ArcherRightDecal, { 2.0f, 2.0f });
        }
        if (ArcherDir == false) {
            DrawDecal({ ArcherPos }, ArcherLeftDecal, { 2.0f, 2.0f });
        }
        if (Time <= 5.0f && WaveDisplay == true) {
            DisplayWave();
        }
        UserInput(ArcherSpeed, fElapsedTime);
        ShootArrow(fElapsedTime);
        WaveCheckDebug();
        if (Time >= 5.0f && WaveDisplay == true) {
            WaveDisplay = false;
            Time = 0.0f;
        }
        if (Time >= 1.0f && WaveDisplay == false) {
            //Spawn/Move Enemies
            MoveEnemies(PoisonGoopSpeed, GoopSpeed, SkeletonSpeed, fElapsedTime);
            //PlayerDeadCheck();
        }
        if (Wave >= 6) {
            DrawSkillUI(fElapsedTime);
        }

        //Draw webs
        DrawSpiderwebs();
    }
    bool OnUserUpdate(float fElapsedTime) override {
        //fElapsedTime = std::max(fElapsedTime, 0.16667f);
        if (GameState == MENU) {
            MenuFlashlight();
            MainMenu();
            return true;
        }
        if (GameState == QUIT) {
            return false;
        }
        if (GameState == GAME) {
            GameGameState(fElapsedTime);
            return true;
        }
        if (GameState == DEBUG) {
            DebugGameState(fElapsedTime);
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
        TotalEnemies.push_back(3);
        TotalEnemies.push_back(0);
        TotalEnemies.push_back(1);
        MaxEnemies.push_back(1);
        MaxEnemies.push_back(0);
        MaxEnemies.push_back(1);
        WaveCounter.push_back(0);
        WaveCounter.push_back(0);
        WaveCounter.push_back(0);
        srand(time(NULL));
        //Sprites
        PoisonGoopLeft = std::make_unique<olc::Sprite>("./Sprites/PoisonGoopLeft.png");
        PoisonGoopRight = std::make_unique<olc::Sprite>("./Sprites/PoisonGoopRight.png");
        PoisonBallLeft = std::make_unique<olc::Sprite>("./Sprites/PoisonBallLeft.png");
        PoisonBallRight = std::make_unique<olc::Sprite>("./Sprites/PoisonBallRight.png");
        SkeletonLeft = std::make_unique<olc::Sprite>("./Sprites/SkeletonLeft.png");
        SkeletonRight = std::make_unique<olc::Sprite>("./Sprites/SkeletonRight.png");
        Flashlight = std::make_unique <olc::Sprite>("./Sprites/Flashlight1.png");
        MenuBackground = std::make_unique<olc::Sprite>("./Sprites/AtticFinal.png");
        Quit = std::make_unique<olc::Sprite>("./Sprites/Quit.png");
        Play = std::make_unique<olc::Sprite>("./Sprites/Play.png");
        Cooldown = std::make_unique<olc::Sprite>("./Sprites/Cooldown.png");
        ArrowBarrage = std::make_unique < olc::Sprite>("./Sprites/ArrowBarrageSkill.png");
        SkillUI = std::make_unique<olc::Sprite>("./Sprites/SkillBox.png");
        GoopSlayerLogo = std::make_unique<olc::Sprite>("./Sprites/GoopSlayer.png");
        SpookyLogo = std::make_unique<olc::Sprite>("./Sprites/Spooky.png");
        Spiderweb1 = std::make_unique<olc::Sprite>("./Sprites/Spiderweb1.png");
        Spiderweb2 = std::make_unique<olc::Sprite>("./Sprites/Spiderweb2.png");
        Spiderweb3 = std::make_unique <olc::Sprite>("./Sprites/SpiderwebTL_WSpider.png");
        Spiderweb4 = std::make_unique <olc::Sprite>("./Sprites/Brokenweb.png");
        ArcherLeft = std::make_unique <olc::Sprite>("./Sprites/ArcherLeft.png");
        ArcherRight = std::make_unique<olc::Sprite>("./Sprites/ArcherRight.png");
        Grass = std::make_unique<olc::Sprite>("./Sprites/Grass.png");
        GoopRight = std::make_unique<olc::Sprite>("./Sprites/GoopRightPumpkin.png");
        GoopLeft = std::make_unique<olc::Sprite>("./Sprites/GoopLeftPumpkin.png");
        PumpkinArrow = std::make_unique<olc::Sprite>("./Sprites/Pumpkin.png");
        Arrow = std::make_unique<olc::Sprite>("./Sprites/Arrow.png");
        //Decals
        PoisonGoopLeftDecal = new olc::Decal(PoisonGoopLeft.get());
        PoisonGoopRightDecal = new olc::Decal(PoisonGoopRight.get());
        PoisonBallLeftDecal = new olc::Decal(PoisonBallLeft.get());
        PoisonBallRightDecal = new olc::Decal(PoisonBallRight.get());
        SkeletonLeftDecal = new olc::Decal(SkeletonLeft.get());
        SkeletonRightDecal = new olc::Decal(SkeletonRight.get());
        FlashlightDecal = new olc::Decal(Flashlight.get());
        MenuBackgroundDecal = new olc::Decal(MenuBackground.get());
        MenuArrowDecal = new olc::Decal(MenuArrow.get());
        QuitDecal = new olc::Decal(Quit.get());
        PlayDecal = new olc::Decal(Play.get());
        CooldownDecal = new olc::Decal(Cooldown.get());
        ArrowBarrageDecal = new olc::Decal(ArrowBarrage.get());
        SkillUIDecal = new olc::Decal(SkillUI.get());
        GoopSlayerLogoDecal = new olc::Decal(GoopSlayerLogo.get());
        SpookyLogoDecal = new olc::Decal(SpookyLogo.get());
        Spiderweb1Decal = new olc::Decal(Spiderweb1.get());
        Spiderweb2Decal = new olc::Decal(Spiderweb2.get());
        Spiderweb3Decal = new olc::Decal(Spiderweb3.get());
        Spiderweb4Decal = new olc::Decal(Spiderweb4.get());
        GrassDecal = new olc::Decal(Grass.get());
        GoopRightDecal = new olc::Decal(GoopRight.get());
        GoopLeftDecal = new olc::Decal(GoopLeft.get());
        ArcherLeftDecal = new olc::Decal(ArcherLeft.get());
        ArcherRightDecal = new olc::Decal(ArcherRight.get());
        PumpkinArrowDecal = new olc::Decal(PumpkinArrow.get());
        ArrowDecal = new olc::Decal(Arrow.get());
        return true;
    }
};

int main() {
    GoopSlayer demo;
    if (demo.Construct(1024, 576, 1, 1, true))
        demo.Start();
    return 0;
}