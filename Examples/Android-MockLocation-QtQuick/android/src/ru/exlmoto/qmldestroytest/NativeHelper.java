//
// NativeHelper.java
//
// Use javah utility for generating header file:
//    $ pwd
//    ../QmlDestroyTest/android/src
//    $ javah ru.exlmoto.qmldestroytest.NativeHelper
//    $ mv *.h ../..

package ru.exlmoto.qmldestroytest;

public class NativeHelper {
    public native static void invokeVoidMethod(int arg);
    public native static void sendMockLocationDataToQml(int i, double lo, double la, double al);
}
