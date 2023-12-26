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
    public native void InitGame();
    public native void DoGameLoopAndMoveRequest(float moveRequest);

    // game update loop parameters

    private Handler handler;


    private final int fps = 30;
    //private final int fps = 60;
    private final long frameTime = 1000 / fps; // Time per frame in milliseconds

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





    @SuppressLint("MissingInflatedId")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_game);
        gameLayout = findViewById(R.id.gameLayout);
        scoreText = findViewById(R.id.score);
        lifeText = findViewById(R.id.life);
        LoadAssets();
        gameLayout.addView(paddleView);
        gameLayout.addView(ballView);
        imageViewMap = new HashMap<>();
        handler = new Handler(Looper.getMainLooper());
        ListenToStartNewGame();
    }





    private void ListenToStartNewGame() {

        Button myButton = findViewById(R.id.startButton);
        myButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                InitGameJava();
            }
        });
    }


    void InitGameJava()
    {
        scoreText.setText("0");
        removeAllImageViews();
        handler.removeCallbacks(update);
        moveRequest = 0;
        InitGame();

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
            case 0:
            default:
                newImageView.setImageDrawable(brick1.getDrawable());
                break;
        }

        FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(
                brickWidth,brickHeight
        );

        params.leftMargin = (int) (x-brickWidth/2);
        params.topMargin = (int) (y-brickHeight/2);

        newImageView.setLayoutParams(params);
        gameLayout.addView(newImageView);

        imageViewMap.put(uid, newImageView);

    }

    private void removeAllImageViews()
    {
            Iterator<Map.Entry<Integer, ImageView>> iterator = imageViewMap.entrySet().iterator();

            while (iterator.hasNext()) {
                Map.Entry<Integer, ImageView> entry = iterator.next();
                Integer imageViewUIDName = entry.getKey();
                ImageView imageView = entry.getValue();
                if(imageView!=null) {
                    gameLayout.removeView(imageView);
                    iterator.remove();
                }
            }
    }

    // TODO: consider send int bouncing event for soundFX;
    public void updateFromCPP(float ballX, float ballY, float paddleX, int brickUID, int score, int life, int soundFX)
    {
        String str = Integer.toString(score);
        scoreText.setText(str);
        str = Integer.toString(life);
        lifeText.setText(str);
        paddleView.setX(paddleX);
        ballView.setX(ballX);
        ballView.setY(ballY);

        if(brickUID!=-1)
        {
            RemoveImageViewByUid(brickUID);
        }
        SoundManager.playSoundEffect(soundFX);

        SetNextUpdate();
    }


    void RemoveImageViewByUid(int targetUid)
    {
        Iterator<Map.Entry<Integer, ImageView>> iterator = imageViewMap.entrySet().iterator();

        while (iterator.hasNext())
        {
            Map.Entry<Integer, ImageView> entry = iterator.next();
            int uid = entry.getKey();
            ImageView imageView = entry.getValue();

            if (uid == targetUid)
            {
                gameLayout.removeView(imageView);

                iterator.remove();

                Log.d("BreakoutGameJava", "remove brick");
                break;
            }
        }
    }



    private void SetNextUpdate()
    {
        handler.postDelayed(update, frameTime);
    }

    private Runnable update = new Runnable()
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