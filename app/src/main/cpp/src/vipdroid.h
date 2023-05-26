//
// Created by gavin on 5/25/23.
//

#ifndef VIPDROID_VIPDROID_H
#define VIPDROID_VIPDROID_H

#include <vips/vips8>
#include <jni.h>

typedef std::vector<std::tuple<std::string, std::vector<std::string>>> effectsType;

class ResolveFunctionResult {
public:
    unsigned int *data;
    size_t size;
    int width;
    int height;
    int bands;
    ResolveFunctionResult(unsigned int *data, size_t size, int width, int height, int bands) {
        this->data = data;
        this->size = size;
        this->width = width;
        this->height = height;
        this->bands = bands;
    };
};

class Image {
    std::mutex mutex;
    vips::VImage internal;
    effectsType * effects_internal;
public:
    Image(vips::VImage image, effectsType * effects);
    vips::VImage image() {
        this->mutex.lock();
        vips::VImage image = this->internal;
        this->mutex.unlock();
        return image;
    };
    effectsType effects() {
        this->mutex.lock();
        effectsType * effects = this->effects_internal;
        this->mutex.unlock();
        if(effects == nullptr) {
            return *new effectsType();
        } else {
            return *effects;
        }
    };

};

class ImageMaster {
private:
    std::mutex mutex;
    std::vector<Image*> images_internal;
public:
    void addImage(int index, unsigned int *data, size_t size, int width, int height, int bands, VipsBandFormat format, effectsType * effects);
    std::vector<Image*> images() {
        this->mutex.lock();
        std::vector<Image*> images = this->images_internal;
        this->mutex.unlock();
        return images;
    }
    void addImage(int index, Image * image) {
        this->mutex.lock();
        this->images_internal[index] = image;
        this->mutex.unlock();
        return;
    }
    void removeImage(int index) {
        this->mutex.lock();
        this->images_internal[index] = nullptr;
        this->mutex.unlock();
        return;
    }
    Image * getImage(int index) {
        this->mutex.lock();
        Image * image = this->images_internal[index];
        this->mutex.unlock();
        return image;
    }
    ResolveFunctionResult resolve();

};

ImageMaster GLOBAL_IMAGE_MASTER;

extern "C" JNIEXPORT void JNICALL Java_com_example_vipdroid_ImageMaster_addImage(JNIEnv *env, jobject obj, jint index, jlongArray data, jsize size, jint width, jint height, jint bands) {
    GLOBAL_IMAGE_MASTER.addImage(index,(unsigned int *)data,size,width,height,bands, VipsBandFormat::VIPS_FORMAT_INT, nullptr);
    return;
}

extern "C" JNIEXPORT void JNICALL Java_com_example_vipdroid_ImageMaster_removeImage(JNIEnv *env, jobject obj, jint index) {
    GLOBAL_IMAGE_MASTER.removeImage(index);
    return;
}

extern "C" JNIEXPORT jobject JNICALL Java_com_example_vipdroid_ImageMaster_resolveInternal(JNIEnv *env, jobject obj) {
    jclass cls = env->FindClass("com/example/vipdroid/ResolveFunctionResult");
    if(cls == NULL) {
        return NULL;
    }
    jmethodID cid = env->GetMethodID(cls,"<init>", "([JIIII)V");
    if(cid == NULL) {
        return NULL;
    }
    ResolveFunctionResult resolve = GLOBAL_IMAGE_MASTER.resolve();
    jlong result[resolve.size];
    for (int i = 0; i < resolve.size; i++) {
        result[i] = resolve.data[i];
    }
    return env->NewObject(cls, cid, (jlongArray)result, (int)resolve.size,resolve.width,resolve.height, resolve.bands);
}

#endif //VIPDROID_VIPDROID_H
