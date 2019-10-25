#include <jni.h>
#include <string>
#include "aes.h"

#include<android/log.h>
#define TAG "AES" // LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型

const int NUM = 16;
const int BITS = 128;

// 密钥
const unsigned char master_key[NUM] = {
        '1', '2', '3', '4', '5', '6', '7', '8',
        '9', '0', 'a', 'b', 'c', 'd', 'e', 'f',
};
// 偏移量
const unsigned char iv[NUM] = {
        '1', '2', '3', '4', '5', '6', '7', '8',
        '9', '0', 'a', 'b', 'c', 'd', 'e', 'f',
};

// 加密函数
extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_example_myapplication_MainActivity_encryptedFromJNI(JNIEnv *env, jobject thiz,
                                                             jbyteArray clear_bytes) {

    jbyte* textBuffer = env->GetByteArrayElements(clear_bytes, 0);
    auto* text = (unsigned char *)textBuffer;
    unsigned char ivc[NUM];
    unsigned char encrypted[NUM];
    memset(encrypted, 0, NUM * sizeof(char));
    AES_KEY key;
    AES_set_encrypt_key(master_key, BITS, &key);
    memcpy(ivc, iv, NUM*sizeof(char));
    AES_cbc_encrypt(text, encrypted, NUM, &key, ivc, AES_ENCRYPT);
    jbyteArray byteArray = env->NewByteArray(NUM);
    env->SetByteArrayRegion(byteArray, 0, NUM, (jbyte *)encrypted);
    return byteArray;
}

// 解密函数
extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_example_myapplication_MainActivity_decryptedFromJNI(JNIEnv *env, jobject thiz,
                                                             jbyteArray secret_bytes) {
    jbyte* textBuffer = env->GetByteArrayElements(secret_bytes, 0);
    auto* secretText = (unsigned char *)textBuffer;
    unsigned char ivc[NUM];
    unsigned char decrypted[NUM];
    memset(decrypted, 0, NUM * sizeof(char));
    AES_KEY key;
    AES_set_decrypt_key(master_key, BITS, &key);
    memcpy(ivc, iv, NUM * sizeof(char));
    AES_cbc_encrypt(secretText, decrypted, NUM, &key, ivc, AES_DECRYPT);
    jbyteArray byteArray = env->NewByteArray(NUM);
    env->SetByteArrayRegion(byteArray, 0, NUM, (jbyte *)decrypted);
    return byteArray;
}