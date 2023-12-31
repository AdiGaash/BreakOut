package com.example.breakout;

import androidx.appcompat.app.AppCompatActivity;


import android.annotation.SuppressLint;
import android.os.Looper;
import android.view.MotionEvent;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.util.Log;


import android.os.Handler;
import android.widget.TextView;

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;


public class MainActivity extends AppCompatActivity {

    // Used to load the 'breakout' library on application startup.
    static {
        System.loadLibrary("game_loop");
    }


    // CPP call functions
    public native void DoGameLoop();
    public native void InitGameLogic();
    public native void DoGameLoopAndMoveRequest(float moveRequest);

    // game update loop parameters

    private Handler handler;


    private final int fps = 30;

    ImageView paddleView;
    ImageView ballView;
    TextView lifeText;
    ImageView brick1;
    ImageView brick2;
    ImageView brick3;

    Map<Integer, ImageView> imageViewMap;

    TextView scoreText;
    FrameLayout gameLayout;
    float moveRequest = 0;

    // brick def size
    int brickWidth = 104;
    int brickHeight = 39;

    FrameLayout groupOfBricksViewsLayout;



    @SuppressLint("MissingInflatedId")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        InitActivity();
        ListenToStartNewGame();
    }



    void InitActivity()
    {
        setContentView(R.layout.activity_game);
        gameLayout = findViewById(R.id.gameLayout);
        scoreText = findViewById(R.id.score);
        lifeText = findViewById(R.id.life);
        LoadAssets();
        gameLayout.addView(paddleView);
        gameLayout.addView(ballView);
        groupOfBricksViewsLayout= new FrameLayout(this);
        groupOfBricksViewsLayout.setLayoutParams(gameLayout.getLayoutParams());
        imageViewMap = new HashMap<>();
        gameLayout.addView(groupOfBricksViewsLayout);

        handler = new Handler(Looper.getMainLooper());
    }

    private void ListenToStartNewGame() {

        Button myButton = findViewById(R.id.startButton);
        myButton.setOnClickListener(view -> InitGameJava());
    }


    void InitGameJava()
    {
        scoreText.setText("0");
        removeAllBricks();
        handler.removeCallbacks(update);
        moveRequest = 0;
        InitGameLogic();

        Log.d("BreakoutGameJava", "Init Game");
        ListenToPaddleDrag();
        SetNextUpdate();
    }




    public void DrawABrickFromCPP(float x, float y, int color, int uid)
    {
        ImageView newImageView = new ImageView(this);
        switch(color)
        {
            case 1:
                newImageView.setImageDrawable(brick2.getDrawable());
                break;
            case 2:
                newImageView.setImageDrawable(brick3.getDrawable());
                break;
            case 3:
                newImageView.setImageDrawable(brick1.getDrawable());
                break;
        }

        FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(
                brickWidth,brickHeight
        );

        params.leftMargin = (int) (x-brickWidth/2);
        params.topMargin = (int) (y-brickHeight/2);

        newImageView.setLayoutParams(params);
        groupOfBricksViewsLayout.addView(newImageView);
        imageViewMap.put(uid, newImageView);





    }

    private void removeAllBricks()
    {
        imageViewMap = new HashMap<>();
        groupOfBricksViewsLayout.removeAllViewsInLayout();
    }

    // TODO: consider send int bouncing event for soundFX;
    @SuppressLint("SetTextI18n")
    public void updateFromCPP(float ballX, float ballY, float paddleX, int brickUID, int score, int life, int soundFX)
    {
        String str =  Integer.toString(score);
        scoreText.setText("Score: " + str);
        str = Integer.toString(life);
        lifeText.setText("Life: " + str);
        paddleView.setX(paddleX);
        ballView.setX(ballX);
        ballView.setY(ballY);

        if(brickUID!=-1)
        {
            RemoveImageViewByUid(brickUID);
        }
        SoundManager.playSoundEffect(soundFX);
        //if(soundFX==7) removeAllBricks();

         SetNextUpdate();
    }


    void RemoveImageViewByUid(int targetUid)
    {
        Iterator<Map.Entry<Integer, ImageView>> iterator = imageViewMap.entrySet().iterator();
        Log.d("BreakoutGameJava", "need to remove brick" + targetUid);
        while (iterator.hasNext())
        {
            Map.Entry<Integer, ImageView> entry = iterator.next();
            int uid = entry.getKey();
            ImageView imageView = entry.getValue();

            if (uid == targetUid)
            {
                groupOfBricksViewsLayout.removeView(imageView);
                iterator.remove();
                Log.d("BreakoutGameJava", "remove brick" + targetUid);
                break;
            }
        }
    }



    private void SetNextUpdate()
    {
        //private final int fps = 60;
        // Time per frame in milliseconds
        long frameTime = 1000 / fps;
        handler.postDelayed(update, frameTime);
    }

    private final Runnable update = new Runnable()
    {
        public void run() {
            if(moveRequest==0)
            {
                DoGameLoop();
            }
            else
            {
                DoGameLoopAndMoveRequest(moveRequest);
                moveRequest=0;
            }
        }
    };


    // paddleDrag manager
    float xPosWhenPressDown =0;
    @SuppressLint("ClickableViewAccessibility")
    void ListenToPaddleDrag()
    {
        paddleView.setOnTouchListener((v, event) ->
        {
        // Get the action of the drag event
            switch (event.getActionMasked())
            {
                case MotionEvent.ACTION_DOWN:
                    xPosWhenPressDown = event.getX();
                    break;

                case MotionEvent.ACTION_MOVE:
                    float movedX = event.getX();
                    moveRequest = movedX-xPosWhenPressDown;
                    break;
            }
        return true;
        });
    }


    void LoadAssets()
    {
        // load prefabs of bricks
        brick1 = new ImageView(this);
        brick1.setImageResource(R.drawable.brick1);

        brick2 = new ImageView(this);
        brick2.setImageResource(R.drawable.brick2);

        brick3 = new ImageView(this);
        brick3.setImageResource(R.drawable.brick3);

        brick1.setVisibility(View.INVISIBLE);
        brick2.setVisibility(View.INVISIBLE);
        brick3.setVisibility(View.INVISIBLE);



        // TODO: this is the old way that I load images before using the drawable folder - need to change to make it standard to all
        // load "game objects and set init positions
        paddleView = AssetHelper.GetImageViewFromAsset(this, "images/paddle.png");
        ballView = AssetHelper.GetImageViewFromAsset(this, "images/ball.png");
        paddleView.setX(0);
        paddleView.setY(1130);
        ballView.setX(0);
        ballView.setY(500);


        // Set audio resources by id

       SoundManager.initializeSounds(this);



    }






}