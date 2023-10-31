#define OLC_PGE_APPLICATION
#define _USE_MATH_DEFINES
#include "olcPixelGameEngine.h"
#include <iostream>
#include <vector>
#include <cmath>

class GoopSlayer : public olc::PixelGameEngine {
public:
    //Sprites
    std::unique_ptr<olc::Sprite> Poop;
    std::unique_ptr<olc::Sprite> LeavesTest;
    std::unique_ptr<olc::Sprite> SkeletonLeft;
    std::unique_ptr<olc::Sprite> SkeletonRight;
    std::unique_ptr<olc::Sprite> PoisonGoopLeft;
    std::unique_ptr<olc::Sprite> PoisonGoopRight;
    std::unique_ptr<olc::Sprite> PoisonBallLeft;
    std::unique_ptr<olc::Sprite> PoisonBallRight;
    std::unique_ptr<olc::Sprite> PoisonSplatter;
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
    std::unique_ptr<olc::Sprite> ArrowHitBoxPos;
    //Decals
    olc::Decal* PoopDecal;
    olc::Decal* LeavesTestDecal;
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
    std::vector<olc::vf2d> PoisonSplashPos;
    std::vector<float> PoisonSplashTimer;
    std::vector<olc::vf2d> PoisonBallDistance;
    std::vector<olc::vf2d> PoisonArcherPos;
    std::vector<int> PoisonBallDistanceBool;
    //Goop variables
    std::vector<olc::vf2d> GoopVel;
    std::vector<olc::vf2d> GoopPos;
    std::vector<int> ChargeCooldownBool;    //After completed charge
    std::vector<float> ChargeCooldownTimer; //After completed charge
    std::vector<float> ChargingTimer;       //Charging back (before)
    std::vector<int> ChargingTimerBool;     //Charging back (before)
    std::vector<int> ChargeTimerBool;       //Currently charging
    std::vector<float> ChargeTimer;         //Currently charging
    std::vector<int> CanCharge;             //Once cooldown is over, 
    int KilledGoops = 0;
    //Skeleton variables
    std::vector<olc::vf2d> SkeleVel;
    std::vector<olc::vf2d> SkelePos;
    int KilledSkeles = 0;
    //Skeleton ArrowHitBoxPos variables
    std::vector<olc::vf2d> SkeleArrowPos;
    std::vector<olc::vf2d> SkeleArrowVel;
    std::vector<int> SkeleShoot;
    std::vector<float> SkeleShootTimer;
    //Player ArrowHitBoxPos variables
    std::vector<olc::vf2d> arrowPos;
    std::vector<olc::vf2d> arrowVel;
    //Archer variables
    bool ArcherSlowed = false;
    olc::vf2d ArcherPos = { 448.0f, 238.0f };
    //True = ArcherRight, False = ArcherLeft
    bool ArcherDir = true;
    //Menu variables
    int score = 0;
    int menu = 0;
    enum GameStateEnum { MENU, DEAD, GAME, QUIT };
    GameStateEnum GameState = MENU;
    //Wave variables
    //MaxEnemies/TotalEnemies [0] = Goop, [1] = Skeleton, [2] = PoisonGoop [3] = 2nd PoisonGoopd
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
    //Poop variables
    std::vector<olc::vf2d> PoopPos;
    std::vector<int> PoopBool;
    std::vector<float> PoopTimer;
    bool CanPoopBool = true;
    float CanPoopTimer = 0;

    GoopSlayer() {
        sAppName = "GoopSlayer";
    }
    //Math shit EW
    //Function to rotate a point around another point by a given angle
    olc::vf2d RotatePoint(const olc::vf2d& point, const olc::vf2d& center, float angle) {
        float s = sin(angle);
        float c = cos(angle);

        //Translate point back to the origin
        olc::vf2d translated = point - center;

        //Rotate point
        olc::vf2d rotated;
        rotated.x = translated.x * c - translated.y * s;
        rotated.y = translated.x * s + translated.y * c;

        //Translate point back
        return rotated + center;
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
                ChargeTimerBool.push_back(0);
                ChargeCooldownBool.push_back(0);
                ChargeTimer.push_back(0);
                ChargeCooldownTimer.push_back(0);
                ChargingTimer.push_back(0);
                ChargingTimerBool.push_back(0);
                CanCharge.push_back(1);
            }
        }
    }
    void SpawnPoisonGoop() {
        if (PoisonGoopPos.size() == 0 && KilledPoison < TotalEnemies[2]) {
            //Goop random coord gen (walls) (spawns max goops)
            for (int k = 0; k < MaxEnemies[2]; k++) {
                int SideGoopNum = rand() % 4;

                //Left Wall
                if (SideGoopNum == 0) {
                    float GoopYNum = rand() % 575;
                    PoisonGoopPos.push_back({ 0.f, GoopYNum });
                }
                //Top Wall
                if (SideGoopNum == 1) {
                    float GoopXNum = rand() % 1023;
                    PoisonGoopPos.push_back({ GoopXNum, 0 });
                }
                //Right Wall
                if (SideGoopNum == 2) {
                    float GoopXNum = rand() % 1023;
                    PoisonGoopPos.push_back({ GoopXNum, 575 });
                }
                //Bottom Wall
                if (SideGoopNum == 3) {
                    float GoopYNum = rand() % 575;
                    PoisonGoopPos.push_back({ 1023, GoopYNum });
                }
                PoisonBallShootBool.push_back(0);
                PoisonBallTimer.push_back(0);
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
            olc::vf2d dir = (ArcherPos - GoopPos[k]);
            float distance = dir.mag();
            //If within 200 pixels, start charging
            if (distance <= 200.0f && CanCharge[k] == 1) {
                ChargeTimerBool[k] = 1;
            }

            if ((ChargeTimerBool[k] == 0 && CanCharge[k] == 1) || ChargeCooldownBool[k] == 1) {
                // Calculate the new position based on direction and speed
                GoopPos[k] += dir.norm() * GoopSpeed;
                // Draw the Goop
                if (dir.x < 0) {
                    DrawDecal({ GoopPos[k] }, GoopLeftDecal, { 2.0f, 2.0f });
                }
                if (dir.x > 0) {
                    DrawDecal({ GoopPos[k] }, GoopRightDecal, { 2.0f, 2.0f });
                }
            }
        }
    }
    void doChargeGoop(float GoopSpeed, float fElapsedTime) {
        for (int k = 0; k < ChargeTimerBool.size(); k++) {
            // Calculate direction towards the player
            olc::vf2d distance = (ArcherPos - GoopPos[k]);
            //Speeds
            float ChargeGoopSpeed;
            float BoostedGoopSpeed;
            if (Wave < 25) {
                ChargeGoopSpeed = 60 * fElapsedTime;
                BoostedGoopSpeed = 400 * fElapsedTime;
            }
            if (Wave >= 25) {
                ChargeGoopSpeed = 40 * fElapsedTime;
                BoostedGoopSpeed = 600 * fElapsedTime;
            }
            //Charging
            if (ChargeTimerBool[k] == 1) {

                //Calculate the new position based on direction and speed
                //Charge back
                if (ChargeTimer[k] < 2.5f && ChargeTimerBool[k] == 1) {
                    GoopPos[k] -= distance.norm() * ChargeGoopSpeed;
                }
                if (ChargeTimer[k] >= 2.5f) {
                    ChargingTimerBool[k] = 1;
                    ChargeTimerBool[k] = 0;
                }
            }
            //Charging into player
            if (ChargingTimerBool[k] == 1) {
                //Charging into player
                if (ChargingTimer[k] == 0.0f) {
                    ChargeTimerBool[k] = 0;
                    ChargeTimer[k] = 0;
                    CanCharge[k] = 0;
                }
                if (ChargingTimerBool[k] == 1 && ChargingTimer[k] < 1.5f) {
                    GoopPos[k] += distance.norm() * BoostedGoopSpeed;
                }
                //When done charging (1.5 seconds) charge cooldown started
                if (ChargingTimer[k] >= 1.5f) {
                    ChargeCooldownBool[k] = 1;
                    ChargeTimerBool[k] = 0;
                    ChargeTimer[k] = 0;
                    ChargingTimer[k] = 0;
                    ChargingTimerBool[k] = 0;
                    CanCharge[k] = 0;
                }
            }
            //Cooldown checker
            if (ChargeCooldownTimer[k] >= 6.0f && ChargeCooldownBool[k] == 1) {
                ChargeCooldownBool[k] = 0;
                ChargeCooldownTimer[k] = 0;
                CanCharge[k] = 1;
            }

            // Draw the Goop
            if (distance.x < 0) {
                DrawDecal({ GoopPos[k] }, GoopLeftDecal, { 2.0f, 2.0f });
            }
            if (distance.x > 0) {
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
            else {
                DrawDecal({ PoisonGoopPos[k] }, PoisonGoopRightDecal, { 2.0f, 2.0f });
            }
        }
    }
    void DrawSkeleArrow(float fElapsedTime) {
        for (size_t i = 0; i < SkeleArrowPos.size(); i++) {
            SkeleArrowPos[i] += SkeleArrowVel[i] * fElapsedTime;

            //ArrowHitBoxPos off-screen
            if (SkeleArrowPos[i].x < 0 || SkeleArrowPos[i].x >= ScreenWidth() || SkeleArrowPos[i].y < 0 || SkeleArrowPos[i].y >= ScreenHeight()) {
                SkeleArrowPos.erase(SkeleArrowPos.begin() + i);
                SkeleArrowVel.erase(SkeleArrowVel.begin() + i);
                i--;
            }
            else {
                //Angle of roation
                float angle = atan2f(SkeleArrowVel[i].y, SkeleArrowVel[i].x);
                //Draw ArrowHitBoxPos
                DrawRotatedDecal(SkeleArrowPos[i], ArrowDecal, angle, { 1.0f, 1.0f }, { 1.0f, 1.0f }, olc::WHITE);
            }
        }
    }
    void DrawPoisonBall(float fElapsedTime) {
        for (int i = 0; i < PoisonBallPos.size(); i++) {
            PoisonBallPos[i] += PoisonBallVel[i] * fElapsedTime;
            olc::vf2d distance = (ArcherPos - PoisonBallPos[i]);

            // When ball first thrown, save positions and calculate distance
            if (PoisonBallDistanceBool[i] == 0) {
                PoisonBallDistance.push_back(ArcherPos - PoisonBallPos[i]);
                PoisonArcherPos.push_back(ArcherPos);
                PoisonBallDistanceBool[i] = 1;
            }

            // If bool already true, calculate distance with recorded positions
            if (PoisonBallDistanceBool[i] == 1) {
                PoisonBallDistance[i] = (PoisonArcherPos[i] - PoisonBallPos[i]);
            }

            // Check if Ball hits Archer's last known position
            if (PoisonBallDistance[i].mag() <= 55.0f) {
                PoisonSplashTimer.push_back(0);
                PoisonSplashPos.push_back(PoisonBallPos[i]);
                PoisonBallPos.erase(PoisonBallPos.begin() + i);
                PoisonBallVel.erase(PoisonBallVel.begin() + i);
                PoisonBallDistanceBool.erase(PoisonBallDistanceBool.begin() + i);
                PoisonArcherPos.erase(PoisonArcherPos.begin() + i);
            }

            else {
                // Draw ArrowHitBoxPos
                if (distance.x < 0) {
                    DrawDecal(PoisonBallPos[i], PoisonBallLeftDecal, { 1.0f, 1.0f });
                }
                if (distance.x > 0) {
                    DrawDecal(PoisonBallPos[i], PoisonBallRightDecal, { 1.0f, 1.0f });
                }
            }
        }
    }
    void DrawPoisonSplash() {
        //Iterate through PoisonSplashs
        for (int k = 0; k < PoisonSplashTimer.size(); k++) {
            if (PoisonSplashTimer[k] < 5.0f) {
                DrawDecal(PoisonSplashPos[k], PoisonSplatterDecal, { 3.0f, 3.0f });
            }
            if (PoisonSplashTimer[k] >= 5.0f) {
                PoisonSplashTimer.erase(PoisonSplashTimer.begin() + k);
                PoisonSplashPos.erase(PoisonSplashPos.begin() + k);
            }
        }
    }
    void PoisonBallShoot(float fElapsedTime) {
        for (int k = 0; k < PoisonGoopPos.size(); k++) {
            if (PoisonBallShootBool[k] == true && PoisonBallTimer[k] >= 2.5f) {
                olc::vf2d UpdatedArcherPos = { ArcherPos.x + 8, ArcherPos.y + 8 };

                // Calculate velocity towards the target
                olc::vf2d vel = (UpdatedArcherPos - olc::vf2d(PoisonGoopPos[k])).norm() * 300.0f;

                // Store the ArrowHitBoxPos's position and velocity
                PoisonBallPos.push_back({ PoisonGoopPos[k].x + 24, PoisonGoopPos[k].y + 24 });
                PoisonBallVel.push_back(vel);
                PoisonBallTimer[k] = 0;
                PoisonBallDistanceBool.push_back(0);
            }
            DrawPoisonBall(fElapsedTime);
        }
    }
    void SkeletonShoot(float fElapsedTime) {
        for (int k = 0; k < SkelePos.size(); k++) {
            if (SkeleShoot[k] == true && SkeleShootTimer[k] >= 1.5f) {
                olc::vf2d UpdatedArcherPos = { ArcherPos.x + 8, ArcherPos.y + 8 };
                // Calculate velocity towards the target
                olc::vf2d vel = (UpdatedArcherPos - olc::vf2d(SkelePos[k])).norm() * 400.0f;

                // Store the ArrowHitBoxPos's position and velocity
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
        doChargeGoop(GoopSpeed, fElapsedTime);
        MoveSkeleton(SkeletonSpeed, fElapsedTime);
        SkeletonShoot(fElapsedTime);
        MovePoisonGoop(PoisonGoopSpeed, fElapsedTime);
        PoisonBallShoot(fElapsedTime);
    }
    void ArrowEnemyCheck() {
        //Iterates through all arrows
        for (int k = 0; k < arrowPos.size(); k++) {
            olc::vi2d ArrowHitBoxPos(arrowPos[k]);
            olc::vi2d ArrowSize(30, 30);

            float angle = atan2f(arrowVel[k].y, arrowVel[k].x);

            // Calculate the position and size of the ArrowHitBoxPos hitbox
            olc::vf2d ArrowHitboxPos = arrowPos[k];
            olc::vf2d ArrowHitboxSize = ArrowSize;

            // Apply rotation to the hitbox position
            ArrowHitboxPos -= ArrowHitboxSize * 0.5f; // Center the hitbox
            ArrowHitboxPos = RotatePoint(ArrowHitboxPos, arrowPos[k], angle);

            //Apply rotation to the hitbox size
            float maxDimension = std::max(ArrowHitboxSize.x, ArrowHitboxSize.y);
            ArrowHitboxSize = { maxDimension, maxDimension };

            //Checks if arrows hit any goops
            for (int o = 0; o < GoopPos.size(); o++) {
                olc::vf2d dir = (ArcherPos - GoopPos[o]);

                //Goop facing left hitbox
                if (dir.x < 0) {
                    olc::vf2d Goop({ GoopPos[o].x + 1, GoopPos[o].y + 6 });
                    olc::vf2d GoopSize(60.0f, 56.0f);

                    if (ArrowHitBoxPos.x < Goop.x + GoopSize.x &&
                        ArrowHitBoxPos.x + ArrowHitboxSize.x > Goop.x &&
                        ArrowHitBoxPos.y < Goop.y + GoopSize.y &&
                        ArrowHitBoxPos.y + ArrowHitboxSize.y > Goop.y) {
                        arrowPos.erase(arrowPos.begin() + k);
                        arrowVel.erase(arrowVel.begin() + k);
                        GoopPos.erase(GoopPos.begin() + o);
                        ChargeCooldownBool.erase(ChargeCooldownBool.begin() + o);
                        ChargingTimer.erase(ChargingTimer.begin() + o);
                        ChargingTimerBool.erase(ChargingTimerBool.begin() + o);
                        ChargeTimerBool.erase(ChargeTimerBool.begin() + o);
                        ChargeTimer.erase(ChargeTimer.begin() + o);
                        CanCharge.erase(CanCharge.begin() + o);
                        score++;
                        KilledGoops++;
                    }
                }
                //Goop facing right hitbox
                if (dir.x > 0) {
                    olc::vf2d Goop({ GoopPos[o].x + 3, GoopPos[o].y + 6 });
                    olc::vf2d GoopSize(60.0f, 56.0f);

                    if (ArrowHitBoxPos.x < Goop.x + GoopSize.x &&
                        ArrowHitBoxPos.x + ArrowHitboxSize.x > Goop.x &&
                        ArrowHitBoxPos.y < Goop.y + GoopSize.y &&
                        ArrowHitBoxPos.y + ArrowHitboxSize.y > Goop.y) {
                        arrowPos.erase(arrowPos.begin() + k);
                        arrowVel.erase(arrowVel.begin() + k);
                        GoopPos.erase(GoopPos.begin() + o);
                        ChargeCooldownBool.erase(ChargeCooldownBool.begin() + o);
                        ChargingTimer.erase(ChargingTimer.begin() + o);
                        ChargingTimerBool.erase(ChargingTimerBool.begin() + o);
                        ChargeTimerBool.erase(ChargeTimerBool.begin() + o);
                        ChargeTimer.erase(ChargeTimer.begin() + o);
                        CanCharge.erase(CanCharge.begin() + o);
                        score++;
                        KilledGoops++;
                    }
                }
            }
            //Checks if arrows hit any skeletons
            for (int o = 0; o < SkelePos.size(); o++) {
                olc::vf2d dir = olc::vf2d(ArcherPos - SkelePos[o]);
                //Skele facing left hitbox
                if (dir.x < 0) {
                    olc::vf2d Skeleton(SkelePos[o].x + 10, SkelePos[o].y + 5);
                    olc::vf2d SkeleSize(39.0f, 59.0f);

                    if (ArrowHitBoxPos.x < Skeleton.x + SkeleSize.y &&
                        ArrowHitBoxPos.x + ArrowHitboxSize.x > Skeleton.x &&
                        ArrowHitBoxPos.y < Skeleton.y + SkeleSize.y &&
                        ArrowHitBoxPos.y + ArrowHitboxSize.y > Skeleton.y) {
                        arrowPos.erase(arrowPos.begin() + k);
                        arrowVel.erase(arrowVel.begin() + k);
                        SkelePos.erase(SkelePos.begin() + o);
                        SkeleShoot.erase(SkeleShoot.begin() + o);
                        SkeleShootTimer.erase(SkeleShootTimer.begin() + o);
                        score++;
                        KilledSkeles++;
                    }
                }
                //Skele facing right hitbox
                if (dir.x > 0) {
                    olc::vf2d Skeleton(SkelePos[o].x + 15, SkelePos[o].y + 5);
                    olc::vf2d SkeleSize( 39.0f, 59.0f );

                    if (ArrowHitBoxPos.x < Skeleton.x + SkeleSize.y &&
                        ArrowHitBoxPos.x + ArrowHitboxSize.x > Skeleton.x &&
                        ArrowHitBoxPos.y < Skeleton.y + SkeleSize.y &&
                        ArrowHitBoxPos.y + ArrowHitboxSize.y > Skeleton.y) {
                        arrowPos.erase(arrowPos.begin() + k);
                        arrowVel.erase(arrowVel.begin() + k);
                        SkelePos.erase(SkelePos.begin() + o);
                        SkeleShoot.erase(SkeleShoot.begin() + o);
                        SkeleShootTimer.erase(SkeleShootTimer.begin() + o);
                        score++;
                        KilledSkeles++;
                    }
                }

            }
            //If ArrowHitBoxPos hit Poison Goop
            for (int o = 0; o < PoisonGoopPos.size(); o++) {
                olc::vf2d dir = (ArcherPos - PoisonGoopPos[o]);

                //PoisonGoop facing left hitbox
                if (dir.x < 0) {
                    olc::vf2d PoisonGoop(PoisonGoopPos[o].x + 3, PoisonGoopPos[o].y + 5);
                    olc::vf2d PoisonSize(48.0f, 60.0f);

                    if (ArrowHitBoxPos.x < PoisonGoop.x + PoisonSize.y &&
                        ArrowHitBoxPos.x + ArrowHitboxSize.x > PoisonGoop.x &&
                        ArrowHitBoxPos.y < PoisonGoop.y + PoisonSize.y &&
                        ArrowHitBoxPos.y + ArrowHitboxSize.y > PoisonGoop.y) {
                        arrowPos.erase(arrowPos.begin() + k);
                        arrowVel.erase(arrowVel.begin() + k);
                        PoisonGoopPos.erase(PoisonGoopPos.begin() + o);
                        PoisonBallShootBool.erase(PoisonBallShootBool.begin() + o);
                        score++;
                        KilledPoison++;
                    }
                }
                //PoisonGoop facing right hitbox
                if (dir.x > 0) {
                    olc::vf2d PoisonGoop(PoisonGoopPos[o].x + 12, PoisonGoopPos[o].y + 5);
                    olc::vf2d PoisonSize(48.0f, 60.0f);

                    if (ArrowHitBoxPos.x < PoisonGoop.x + PoisonSize.y &&
                        ArrowHitBoxPos.x + ArrowHitboxSize.x > PoisonGoop.x &&
                        ArrowHitBoxPos.y < PoisonGoop.y + PoisonSize.y &&
                        ArrowHitBoxPos.y + ArrowHitboxSize.y > PoisonGoop.y) {
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
    }
    //Player
    void ResetVariables() {
        //Remove poops
        PoopPos.clear();
        PoopTimer.clear();
        PoopBool.clear();
        CanPoopTimer = 0;
        CanPoopBool = true;

        //Remove poison goops
        PoisonGoopPos.clear();
        PoisonBallShootBool.clear();
        PoisonBallTimer.clear();

        //Remove goops
        GoopPos.clear();
        ChargeCooldownBool.clear();
        ChargeCooldownTimer.clear();
        ChargingTimer.clear();
        ChargingTimerBool.clear();
        ChargeTimerBool.clear();
        ChargeTimer.clear();
        CanCharge.clear();

        //Remove player arrows
        arrowPos.clear();
        arrowVel.clear();

        //Remove Skeletons
        SkelePos.clear();
        SkeleShoot.clear();
        SkeleShootTimer.clear();

        //Remove Poison Balls
        PoisonBallPos.clear();
        PoisonBallVel.clear();
        PoisonBallDistance.clear();
        PoisonBallDistanceBool.clear();

        //Remove Poison splatters
        PoisonSplashPos.clear();
        PoisonSplashTimer.clear();

        //Remove Skeleton arrows
        SkeleArrowPos.clear();
        SkeleArrowVel.clear();

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
        MaxEnemies[2] = 0;
        TotalEnemies[0] = 1;
        TotalEnemies[1] = 0;
        TotalEnemies[2] = 0;
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
        DrawGrass();
        DrawSpiderwebs();
        std::string ScoreString = std::to_string(score);
        DrawStringDecal({ (float)ScreenWidth() / 7 + 4, (float)ScreenHeight() / 5 + 3 }, "You've been slain!", olc::BLACK, { 5.0f, 5.0f });
        DrawStringDecal({ (float)ScreenWidth() / 7, (float)ScreenHeight() / 5 }, "You've been slain!", olc::RED, { 5.0f, 5.0f });
        DrawStringDecal({ (float)ScreenWidth() / 3 + 64, (float)ScreenHeight() / 2 - 37 }, "Score", olc::BLACK, { 4.0f, 4.0f });
        DrawStringDecal({ (float)ScreenWidth() / 3 + 60, (float)ScreenHeight() / 2 - 40}, "Score:", olc::GREEN, { 4.0f, 4.0f });
        DrawStringDecal({ (float)ScreenWidth() / 3 + 134, (float)ScreenHeight() / 2 + 13 }, ScoreString, olc::BLACK, { 4.0f, 4.0f });
        DrawStringDecal({ (float)ScreenWidth() / 3 + 130, (float)ScreenHeight() / 2 + 10 }, ScoreString, olc::GREEN, { 4.0f, 4.0f });
        DrawStringDecal({ (float)ScreenWidth() / 7 + 4, (float)ScreenHeight() / 2 + 107 }, "Press 'SPACE' to retry", olc::BLACK, {4.0f, 4.0f});
        DrawStringDecal({ (float)ScreenWidth() / 7, (float)ScreenHeight() / 2 + 105 }, "Press 'SPACE' to retry", olc::WHITE, { 4.0f, 4.0f });
    }
    void PlayerDeadCheck() {
        //Archer variables
        olc::vf2d Archer;
        olc::vf2d ArcherSize;
        //Archer facing right
        if (ArcherDir == true) {
            Archer = { ArcherPos.x + 14.0f, ArcherPos.y + 6.0f };
            ArcherSize = { 44.0f, 58.0f };
        }
        //Archer facing left
        else {  
            Archer = { ArcherPos.x + 6.0f, ArcherPos.y + 6.0f };
            ArcherSize = { 44.0f, 58.0f };
        }
        //Goop check
        for (int k = 0; k < GoopPos.size(); k++) {
            olc::vf2d dir = (ArcherPos - GoopPos[k]);

            //Goop facing left hitbox
            if (dir.x > 0) {
                olc::vf2d Goop({ GoopPos[k].x + 1, GoopPos[k].y + 6 });
                olc::vf2d GoopSize(60.0f, 56.0f);

                if (Goop.x < Archer.x + ArcherSize.x &&
                    Goop.x + GoopSize.x > Archer.x &&
                    Goop.y < Archer.y + ArcherSize.y &&
                    Goop.y + GoopSize.y > Archer.y) {
                    GameState = DEAD;
                }
            }
            //Goop facing right hitbox
            else {
                olc::vf2d Goop({ GoopPos[k].x + 3, GoopPos[k].y + 6 });
                olc::vf2d GoopSize(60.0f, 56.0f);

                if (Goop.x < Archer.x + ArcherSize.x &&
                    Goop.x + GoopSize.x > Archer.x &&
                    Goop.y < Archer.y + ArcherSize.y &&
                    Goop.y + GoopSize.y > Archer.y) {
                    GameState = DEAD;
                }
            }
        }
        //PoisonGoop Check
        for (int k = 0; k < PoisonGoopPos.size(); k++) {
            //Poison Goop variables
            olc::vi2d Poison(PoisonGoopPos[k]);
            olc::vi2d PoisonSize(64, 64);

            olc::vf2d dir = (ArcherPos - PoisonGoopPos[k]);

            //PoisonGoop facing left hitbox
            if (dir.x < 0) {
                olc::vf2d PoisonGoop(PoisonGoopPos[k].x + 3, PoisonGoopPos[k].y + 5);
                olc::vf2d PoisonSize(48.0f, 60.0f);

                if (Poison.x < Archer.x + ArcherSize.x &&
                    Poison.x + PoisonSize.x > Archer.x &&
                    Poison.y < Archer.y + ArcherSize.y &&
                    Poison.y + PoisonSize.y > Archer.y) {
                    GameState = DEAD;
                }
            }
            //PoisonGoop facing right hitbox
            else {
                olc::vf2d PoisonGoop(PoisonGoopPos[k].x + 12, PoisonGoopPos[k].y + 5);
                olc::vf2d PoisonSize(48.0f, 60.0f);

                if (Poison.x < Archer.x + ArcherSize.x &&
                    Poison.x + PoisonSize.x > Archer.x &&
                    Poison.y < Archer.y + ArcherSize.y &&
                    Poison.y + PoisonSize.y > Archer.y) {
                    GameState = DEAD;
                }
            }
        }
        //Check if Poison balls hit player
        for (int k = 0; k < PoisonBallPos.size(); k++) {
            //Ball variables
            olc::vf2d dir = (ArcherPos - PoisonBallPos[k]);
            //PoisonBall facing left
            if (dir.x < 0) {
                olc::vf2d Ball(PoisonBallPos[k].x + 7, PoisonBallPos[k].y + 8);
                olc::vf2d BallSize(20.0f, 17.0f);

                if (Ball.x < Archer.x + ArcherSize.x &&
                    Ball.x + BallSize.x > Archer.x &&
                    Ball.y < Archer.y + ArcherSize.y &&
                    Ball.y + BallSize.y > Archer.y) {
                    GameState = DEAD;
                }
            }
            //PoisonBall facing right
            else {
                olc::vf2d Ball(PoisonBallPos[k].x + 5, PoisonBallPos[k].y + 8);
                olc::vf2d BallSize(30.0f, 17.0f);

                if (Ball.x < Archer.x + ArcherSize.x &&
                    Ball.x + BallSize.x > Archer.x &&
                    Ball.y < Archer.y + ArcherSize.y &&
                    Ball.y + BallSize.y > Archer.y) {
                    GameState = DEAD;
                }
            }
        }
        //Check if skeleton ArrowHitBoxPos hits player
        for (int k = 0; k < SkeleArrowPos.size(); k++) {
            //Skele variables
            olc::vi2d SkeleArrow(SkeleArrowPos[k]);
            olc::vi2d SkeleArrowSize(32, 32);

            float angle = atan2f(SkeleArrowVel[k].y, SkeleArrowVel[k].x);

            //Calculate the position and size of the ArrowHitboxPos hitbox
            olc::vf2d ArrowHitboxPos = SkeleArrowPos[k];
            olc::vf2d ArrowHitboxSize = SkeleArrowSize;

            //Apply rotation to the hitbox position
            ArrowHitboxPos -= ArrowHitboxSize * 0.5f; //Center the hitbox
            ArrowHitboxPos = RotatePoint(ArrowHitboxPos, SkeleArrowPos[k], angle);

            //Apply rotation to the hitbox size
            float maxDimension = std::max(ArrowHitboxSize.x, ArrowHitboxSize.y);
            ArrowHitboxSize = { maxDimension, maxDimension };

            if (ArrowHitboxPos.x < Archer.x + ArcherSize.x &&
                ArrowHitboxPos.x + ArrowHitboxSize.x > Archer.x &&
                ArrowHitboxPos.y < Archer.y + ArcherSize.y &&
                ArrowHitboxPos.y + ArrowHitboxSize.y > Archer.y) {
                GameState = DEAD;
            }
        }
    }
    void PlayerSlowPoison(float ArcherSpeed, float fElapsedTime) {
        //Archer variables
        olc::vi2d Archer(ArcherPos);
        olc::vi2d ArcherSize(60, 60);
        for (int k = 0; k < PoisonSplashPos.size(); k++) {
            olc::vi2d Splash(PoisonSplashPos[k]);
            olc::vi2d SplashSize(95, 95);
            if (Splash.x < ArcherPos.x + ArcherSize.x &&
                Splash.x + SplashSize.x > Archer.x &&
                Splash.y < Archer.y + ArcherSize.y &&
                Splash.y + SplashSize.y > Archer.y) {
                ArcherSlowed = true;
            }
            else {
                ArcherSlowed = false;
            }
        }
    }
    void DrawArrow(float fElapsedTime) {
        // Move and draw the arrows
        for (size_t i = 0; i < arrowPos.size(); i++) {
            arrowPos[i] += arrowVel[i] * fElapsedTime;

            // Check if ArrowHitBoxPos is off-screen
            if (arrowPos[i].x < 0 || arrowPos[i].x >= ScreenWidth() || arrowPos[i].y < 0 || arrowPos[i].y >= ScreenHeight()) {
                // Remove the ArrowHitBoxPos
                arrowPos.erase(arrowPos.begin() + i);
                arrowVel.erase(arrowVel.begin() + i);
                i--;
            }
            else {
                // Calculate the angle of rotation based on the ArrowHitBoxPos's velocity
                float angle = atan2f(arrowVel[i].y, arrowVel[i].x);

                // Draw the rotated ArrowHitBoxPos
                DrawRotatedDecal(arrowPos[i], PumpkinArrowDecal, angle, { 1.0f, 1.0f }, { 1.0f, 1.0f }, olc::WHITE);

                //ArrowHitBoxPos+Goop Check
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
            olc::vf2d vel = (targetPos - olc::vf2d(ArcherPos)).norm() * 400.0f;


            // Store the ArrowHitBoxPos's position and velocity
            arrowPos.push_back({ ArcherPos.x + 32, ArcherPos.y + 32 });
            arrowVel.push_back(vel);
        }
        DrawArrow(fElapsedTime);
    }
    void SpawnArrowRing(float fElapsedTime) {
        float angleIncrement = 360.0f / 12.0f; // Divide 360 degrees into 12 directions

        for (int i = 0; i < 12; i++) {
            // Calculate the direction vector for each ArrowHitBoxPos
            float angle = i * angleIncrement;
            olc::vf2d direction = { cosf(M_PI * angle / 180.0f), sinf(M_PI * angle / 180.0f) };

            // Calculate the velocity of the ArrowHitBoxPos
            olc::vf2d vel = direction * 400.0f;

            // Store the ArrowHitBoxPos's position and velocity
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
        if (GetKey(olc::Key::E).bPressed && SkillUsed == false && Wave >= 10) {
            SpawnArrowRing(fElapsedTime);
            SkillUsed = true;
        }
        if (GetKey(olc::Key::ESCAPE).bPressed) {
            GameState = QUIT;
        }
        if (GetKey(olc::Key::V).bPressed && CanPoopBool == true) {
            PoopPos.push_back({ ArcherPos.x + 16, ArcherPos.y + 16 });
            PoopBool.push_back(1);
            PoopTimer.push_back(0);
            CanPoopBool = false;
        }
    }
    //Wave
    void WaveCheck() {
        if ((KilledGoops >= TotalEnemies[0] 
            && KilledSkeles >= TotalEnemies[1] 
            && KilledPoison >= TotalEnemies[2])
            && (GoopPos.size() == 0 
            && SkelePos.size() == 0 
            && PoisonGoopPos.size() == 0)) {
            KilledGoops = 0;
            KilledSkeles = 0;
            KilledPoison = 0;
            Time = 0.0f;
            //Remove any skeleton arrows when wave ends
            SkeleArrowPos.clear();
            SkeleArrowVel.clear();
            //Remove any Poison abilities when wave ends
            PoisonBallPos.clear();
            PoisonBallVel.clear();
            PoisonSplashPos.clear();
            PoisonSplashTimer.clear();

            WaveDisplay = true;
            Wave++;
            //Goop
            //Increase max by one every 2 waves until Max == 6
            //Increase total by 2 every wave until Total == 16
            if (MaxEnemies[0] < 6) {
                WaveCounter[0]++;
            }
            if (TotalEnemies[0] < 16) {
                TotalEnemies[0] += 2;
            }
            if (WaveCounter[0] == 2) {
                MaxEnemies[0]++;
            }
            //Skeletons
            //Increase max by one every 3 waves until Max ==  5
            //Increase total by 1 every wave until Total == 14
            //Starting on Wave 3
            if (Wave >= 3) {
                if (MaxEnemies[1] < 5) {
                    WaveCounter[1]++;
                }
                if (TotalEnemies[1] < 14) {
                    TotalEnemies[1]++;
                }
                if (TotalEnemies[1] == 1) {
                    TotalEnemies[1]++;
                    MaxEnemies[1]++;
                }
                if (WaveCounter[1] == 3) {
                    MaxEnemies[1]++;
                    WaveCounter[1] = 0;
                }
            }
            //Poison Goops
            //Increase max by one every 4 waves until Max == 4
            //Increase total by 1 every 2 waves until Total == 10
            //Starting on Wave 8
            if (Wave >= 8) {
                if (MaxEnemies[2] < 4) {
                    WaveCounter[2]++;
                    WaveCounter[3]++;
                }
                if (TotalEnemies[2] < 10 && WaveCounter[3] == 2) {
                    TotalEnemies[2]++;
                    WaveCounter[3] = 0;
                }
                if (WaveCounter[2] == 4) {
                    MaxEnemies[2]++;
                    WaveCounter[2] = 0;
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
        DrawStringDecal({ (float)ScreenWidth() / 2 - 126, (float)ScreenHeight() / 3 + 3 }, "Wave", olc::BLACK, { 5.0f, 5.0f });
        DrawStringDecal({ (float)ScreenWidth() / 2 - 130, (float)ScreenHeight() / 3 }, "Wave", olc::WHITE, { 5.0f, 5.0f });
        DrawStringDecal({ (float)ScreenWidth() / 2 + 64, (float)ScreenHeight() / 3 + 3 }, WaveString, olc::BLACK, { 5.0f, 5.0f });
        DrawStringDecal({ (float)ScreenWidth() / 2 + 60, (float)ScreenHeight() / 3 }, WaveString, olc::WHITE, { 5.0f, 5.0f });
        if (Wave == 6) {
            DrawStringDecal({ (float)ScreenWidth() / 5 - 14, (float)ScreenHeight() / 2 + 3 }, "Unlocked ArrowHitBoxPos ring!", olc::BLACK, { 4.0f, 4.0f });
            DrawStringDecal({ (float)ScreenWidth() / 5 - 10, (float)ScreenHeight() / 2 }, "Unlocked ArrowHitBoxPos ring!", olc::WHITE, { 4.0f, 4.0f });
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

        if (GetMouseX() >= 440 && GetMouseY() >= 300 && GetMouseX() <= 570 && GetMouseY() <= 365 && (GetMouse(0).bPressed)) {
            ResetVariables();
            GameState = GAME;
        }
        if (GetMouseX() >= 440 && GetMouseY() >= 400 && GetMouseX() <= 570 && GetMouseY() <= 460 && (GetMouse(0).bPressed)) {
            WaveDisplay = false;
            GameState = QUIT;
        }
    }
    void DrawGrass() {
        for (int x = 0; x < 1024; x += 32) {
            for (int y = 0; y < 576; y += 32) {
                DrawDecal({ (float)x, (float)y }, GrassDecal);
            }
        }
        //Draw leaves
        DrawDecal({ 0.0f, 0.0f }, LeavesTestDecal, { 1.0f, 1.0f });
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
    void PoopFunction() {
        for (int k = 0; k < PoopBool.size(); k++) {
            if (PoopTimer[k] < 5.0f) {
                DrawDecal({ PoopPos[k] }, PoopDecal, { 1.0f, 1.0f });
            }
            else {
                PoopPos.erase(PoopPos.begin() + k);
                PoopTimer.erase(PoopTimer.begin() + k);
                PoopBool.erase(PoopBool.begin() + k);
            }
        }
    }
    //GameStates
    void GameGameState(float fElapsedTime) {
        fElapsedTime = std::min(fElapsedTime, 0.16667f);
        Clear(olc::BLACK);
        //Draw Grass
        DrawGrass();
        //Timers
        //Poop
        if (CanPoopBool == false) {
            CanPoopTimer += fElapsedTime;
        }
        if (CanPoopTimer >= 5.0f) {
            CanPoopTimer = 0.0f;
            CanPoopBool = true;
        }
        for (int k = 0; k < PoopBool.size(); k++) {
            if (PoopBool[k] == 1) {
                PoopTimer[k] += fElapsedTime;
            }
        }
        PoopFunction();
        //Currently Charging Goop
        for (int k = 0; k < GoopPos.size(); k++) {
            if (ChargingTimerBool[k] == 1) {
                ChargingTimer[k] += fElapsedTime;
            }
        }
        //Goop Charge Cooldown
        for (int k = 0; k < GoopPos.size(); k++) {
            if (ChargeCooldownBool[k] == 1) {
                ChargeCooldownTimer[k] += fElapsedTime;
            }
        }
        //Goop Charge
        for (int k = 0; k < GoopPos.size(); k++) {
            if (ChargeTimerBool[k] == 1) {
                ChargeTimer[k] += fElapsedTime;
            }
        }
        //Skeleton Shoot
        for (int k = 0; k < SkelePos.size(); k++) {
            if (SkeleShoot[k] == 1) {
                SkeleShootTimer[k] += fElapsedTime;
            }
        }
        //Poison Ball Shoot
        for (int k = 0; k < PoisonGoopPos.size(); k++) {
            if (PoisonBallShootBool[k] == 1) {
                PoisonBallTimer[k] += fElapsedTime;
            }
        }
        //Poison Splash
        for (int k = 0; k < PoisonSplashTimer.size(); k++) {
            PoisonSplashTimer[k] += fElapsedTime;
        }

        float ArcherSpeed = 200 * fElapsedTime;
        Time += fElapsedTime;
        if (ArcherSlowed == true) {
            ArcherSpeed = 80 * fElapsedTime;
        }
        
        //Enemy speeds
        float GoopSpeed;
        float SkeletonSpeed;
        float PoisonGoopSpeed;
        if (Wave < 25) {
            GoopSpeed = 220 * fElapsedTime;
            SkeletonSpeed = 240 * fElapsedTime;
            PoisonGoopSpeed = 180 * fElapsedTime;
        }
        if (Wave >= 25) {
            GoopSpeed = 250 * fElapsedTime;
            SkeletonSpeed = 280 * fElapsedTime;
            PoisonGoopSpeed = 240 * fElapsedTime;
        }
        //Draw Poison Splash, so player is above
        DrawPoisonSplash();
        //Draw Archer
        //Archer facing right
        if (ArcherDir == true) {
            DrawDecal({ ArcherPos }, ArcherRightDecal, { 2.0f, 2.0f });
        }
        //Archer facing left
        if (ArcherDir == false) {
            DrawDecal({ ArcherPos }, ArcherLeftDecal, { 2.0f, 2.0f });
        }
        PlayerSlowPoison(ArcherSpeed, fElapsedTime);

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
        if (Wave >= 10) {
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
        WaveCounter.push_back(0);
        srand(time(NULL));
        //Sprites
        Poop = std::make_unique<olc::Sprite>("./Sprites/Poop.png");
        LeavesTest = std::make_unique<olc::Sprite>("./Sprites/Leaves.png");
        PoisonSplatter = std::make_unique<olc::Sprite>("./Sprites/PoisonSplatter.png");
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
        ArrowHitBoxPos = std::make_unique<olc::Sprite>("./Sprites/ArrowHitBoxPos.png");
        //Decals
        PoopDecal = new olc::Decal(Poop.get());
        LeavesTestDecal = new olc::Decal(LeavesTest.get());
        PoisonSplatterDecal = new olc::Decal(PoisonSplatter.get());
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
        ArrowDecal = new olc::Decal(ArrowHitBoxPos.get());
        return true;
    }
};

int main() {
    GoopSlayer demo;
    if (demo.Construct(1024, 576, 1, 1, true))
        demo.Start();
    return 0;
}