package com.example.breakout;


import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.RelativeLayout;

import java.io.IOException;
import java.io.InputStream;

public enum AssetHelper {
    ;

    public static ImageView GetImageViewFromAsset(Context context, String fileName)
    {
        AssetManager assetManager = context.getAssets();
        try
        {
            InputStream inputStream = assetManager.open(fileName);
            BitmapFactory.Options options = new BitmapFactory.Options();
            options.inPreferredConfig = Bitmap.Config.ARGB_8888;
            Bitmap bitmap = BitmapFactory.decodeStream(inputStream, null, options);

            ImageView imageView = new ImageView(context);
            imageView.setImageBitmap(bitmap);

            RelativeLayout.LayoutParams params = new RelativeLayout.LayoutParams(bitmap.getWidth(), bitmap.getHeight());
            imageView.setLayoutParams(params);
            //SetImageViewAtCenter(imageView);

            return imageView;

        }
        catch (IOException e)
        {
            e.printStackTrace();
            return null;
        }
    }




    public static void SetImageViewAtCenter(ImageView imageView)
    {
        RelativeLayout.LayoutParams params = new RelativeLayout.LayoutParams(
                ViewGroup.LayoutParams.WRAP_CONTENT,
                ViewGroup.LayoutParams.WRAP_CONTENT
        );
        params.addRule(RelativeLayout.CENTER_IN_PARENT);
        imageView.setLayoutParams(params);
    }
}