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
EventByBall soundFX;




//declaration of function
void SendAllBricks(JNIEnv *env, jobject instance);

void SendUpdateGameInJava(JNIEnv *env, jobject instance);
//declaration of function



JNIEXPORT void JNICALL
Java_com_example_breakout_MainActivity_InitGame(JNIEnv *env, jobject instance)
{

     game.Init();

     score = game.Score;
     paddle = game.GetPaddle();

     game.ball.GetPaddleParameters(paddle);
     game.ball.SetBrickGrid(game.GetBrickGrid());


     ballX = game.ball.GetX();
     ballY = game.ball.GetY();


    __android_log_print(ANDROID_LOG_DEBUG, "BreakoutGameCPP", "init");

    SendAllBricks(env, instance);
}

// sending all bricks (one by one in a loop to java to be created by imageView
void SendAllBricks(JNIEnv *env, jobject instance) {
    const std::vector<std::vector<Brick>> &bricks = game.GetBrickGrid().GetBricks();
    for (const auto &row: bricks) {
        for (const auto &brick: row) {
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
}

// Helper function for updating the game state in Java
void SendUpdateGameInJava(JNIEnv *env, jobject instance)
{
    if(game.life < 0)
        return;

    score = game.Score;
    paddleX = paddle.GetX();
    game.ball.Update(paddleX);
    ballX = game.ball.GetX();
    ballY = game.ball.GetY();
    int brickUID = game.brickToRemoveUID;
    game.brickToRemoveUID = -1;
    life = game.life;
    soundFX = game.soundFX;

    jclass clazz = env->GetObjectClass(instance);
    jmethodID methodID = env->GetMethodID(clazz, "updateFromCPP", "(FFFIII)V");
    env->CallVoidMethod(instance, methodID, ballX, ballY, paddleX, brickUID, score, life);

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


