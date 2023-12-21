package com.example.breakout;


public class InputHandler {
    // Load the native library
    static {
        System.loadLibrary("breakout");
    }

    // Declare the native function
    public native void nativeHandleInput(int inputCode);
    public native void nativeHandleInputFloat(float newPos);
    public native void nativeHandleInput(String action, float value);

}