package com.example.vipdroid

import android.util.Size

class ImageMaster {
    init {
        System.loadLibrary("vipdroid")
    }

    external fun addImage(index: Int, data: LongArray, size: Int, width: Int, height: Int, bands: Int);
    external fun removeImage(index: Int);
    external fun resolveInternal(): ResolveFunctionResult;


}