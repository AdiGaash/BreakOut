package com.example.breakout;

import android.content.Context;
import android.media.AudioAttributes;
import android.media.AudioManager;
import android.media.SoundPool;
import android.os.Build;

public enum SoundManager {
    ;
    private static SoundPool soundPool;
    private static int[] soundEffects;

    public static void initializeSounds(Context context)
    {

        AudioAttributes audioAttributes = new AudioAttributes.Builder()
                .setUsage(AudioAttributes.USAGE_GAME)
                .setContentType(AudioAttributes.CONTENT_TYPE_SONIFICATION)
                .build();

        soundPool = new SoundPool.Builder()
                .setMaxStreams(6) // Set the maximum number of simultaneous streams
                .setAudioAttributes(audioAttributes)
                .build();




        // Load sound effects
        soundEffects = new int[8];
        soundEffects[0] = soundPool.load(context, R.raw.bounce_wall1, 1);
        soundEffects[1] = soundPool.load(context, R.raw.bounce_wall2, 1);
        soundEffects[2] = soundPool.load(context, R.raw.bounce_paddle1, 1);
        soundEffects[3] = soundPool.load(context, R.raw.bounce_paddle2, 1);
        soundEffects[4] = soundPool.load(context, R.raw.break_brick, 1);
        soundEffects[5] = soundPool.load(context, R.raw.game_over, 1);
        soundEffects[6] = soundPool.load(context, R.raw.hit_brick, 1);
        soundEffects[7] = soundPool.load(context, R.raw.level_complete, 1);
    }

    public static void playSoundEffect(int soundEffectIndex)
    {
        if (soundEffectIndex >= 0 && soundEffectIndex < soundEffects.length)
            soundPool.play(soundEffects[soundEffectIndex], 1.0f, 1.0f, 0, 0, 1.0f);
    }
}