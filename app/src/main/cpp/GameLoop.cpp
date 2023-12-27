//
// Created by adiga on 14/12/2023.

#include <jni.h>
#include <android/log.h>
#include <unistd.h> // For sleep
#include <thread>   // For std::thread
#include "BreakoutGame.h"
#include "Brick.h"
#include "Ball.h"



extern "C" {


// game screen is 1000X1200

// this class is for communication between cpp - java.
// It will also start the creation of a game session (via BreakoutGame)
// - as the game start after getting a java message

BreakoutGame game = BreakoutGame();

// values to contain current info before sending back to java
float ballX;
float ballY;
float paddleX;
Paddle paddle;
int score;
int life;
int soundFX;
int brickUID;



//declaration of function
void SendAllBricks(JNIEnv *env, jobject instance);

void SendUpdateGameInJava(JNIEnv *env, jobject instance);
//declaration of function



JNIEXPORT void JNICALL
Java_com_example_breakout_MainActivity_InitGameLogic(JNIEnv *env, jobject instance)
{

     game.Init();

     score = game.Score;
     paddle = game.GetPaddle();

     game.Ball.GetPaddleParameters(paddle);
     game.Ball.SetBrickGrid(game.GetBrickGrid());


     ballX = game.Ball.GetX();
     ballY = game.Ball.GetY();


    __android_log_print(ANDROID_LOG_DEBUG, "BreakoutGameCPP", "init");

    SendAllBricks(env, instance);
}

// sending all bricks (one by one in a loop to java to be created by imageView
void SendAllBricks(JNIEnv *env, jobject instance) {

    auto& bricks = game.GetBrickGrid().GetBricks();
    int totalBricks = static_cast<int>(bricks.size());

    for (int index = totalBricks - 1; index >= 0; --index)
    {
        Brick brick = bricks[index];

        // Access brick information and call the Java method
        float x = brick.x;
        float y = brick.y;
        int color = brick.color;
        int uid = brick.uid;


        jclass clazz = env->GetObjectClass(instance);
        jmethodID methodID = env->GetMethodID(clazz, "DrawABrickFromCPP", "(FFII)V");
        env->CallVoidMethod(instance, methodID, x, y, color, uid);
    }
}

// Helper function for updating the game state in Java
void SendUpdateGameInJava(JNIEnv *env, jobject instance)
{
    if(game.Life < 0)
        return;


    paddleX = paddle.GetX();
    game.Update(paddleX);

    soundFX = game.SoundFX;
    score = game.Score;
    ballX = game.Ball.GetX();
    ballY = game.Ball.GetY();
    brickUID = game.BrickToRemove;
    life = game.Life;


    if(soundFX==7)
        SendAllBricks(env, instance);


    jclass clazz = env->GetObjectClass(instance);
    jmethodID methodID = env->GetMethodID(clazz, "updateFromCPP", "(FFFIIII)V");
    env->CallVoidMethod(instance, methodID, ballX, ballY, paddleX, brickUID, score, life, soundFX);


}



JNIEXPORT void JNICALL
Java_com_example_breakout_MainActivity_DoGameLoopAndMoveRequest(JNIEnv *env, jobject instance, jfloat moveRequest)
{
    // Your logic to convert touch event details to a unique input code if needed
    std::string myString = "request move: " + std::to_string(moveRequest);

    __android_log_print(ANDROID_LOG_DEBUG, "BreakoutGameCPP", "%s", myString.c_str());

    paddle.Update(moveRequest);

    SendUpdateGameInJava(env, instance);

}

// Method to start the game loop
JNIEXPORT void JNICALL
Java_com_example_breakout_MainActivity_DoGameLoop(JNIEnv *env, jobject instance)
{
    __android_log_print(ANDROID_LOG_DEBUG, "BreakoutGameCPP", "DoGameLoop");

    // Perform other logic specific to DoGameLoop


    // Call the helper function to update the game state in Java
    SendUpdateGameInJava(env, instance);
}


}


