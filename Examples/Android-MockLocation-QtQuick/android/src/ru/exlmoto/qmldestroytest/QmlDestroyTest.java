//
// QmlDestroyTest.java
//

package ru.exlmoto.qmldestroytest;

import android.util.Log;
import android.os.Bundle;
import android.content.Intent;
import android.os.Vibrator;
import android.content.Context;
import android.media.AudioManager;
import android.widget.Toast;
import android.app.ActivityManager;
import android.app.ActivityManager.RunningServiceInfo;

import android.location.Criteria;
import android.location.Location;
import android.location.LocationManager;
import android.location.LocationListener;
import android.location.LocationProvider;

public class QmlDestroyTest extends org.qtproject.qt5.android.bindings.QtActivity implements LocationListener {
    public static Vibrator m_vibrator;
    public static QmlDestroyTest m_instance;

    private int counter;

    static String TAG = "QmlDestroyTest";

    public QmlDestroyTest() {
        m_instance = this;
        counter = 0;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        this.setVolumeControlStream(AudioManager.STREAM_MUSIC);
        super.onCreate(savedInstanceState);

        LocationManager locationManager = (LocationManager) getSystemService(Context.LOCATION_SERVICE);
        if (locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER)) {
            locationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 0, 0, this);
        }
    }

    @Override
    public void onStop() {
        Log.w(TAG, "onStop() called!");
        NativeHelper.invokeVoidMethod(42);
        super.onStop();
    }

    @Override
    public void onDestroy() {
        Log.w(TAG, "onDestroy() called!");
        super.onDestroy();
    }

    @Override
    public void onLocationChanged(Location location) {
        /*
        Log.w(TAG, "===> Index: " + mMockGpsProviderIndex +
            " | LON: " + location.getLongitude() +
            " | LAT: " + location.getLatitude() +
            " | ALT: " + location.getAltitude());
        // NOTE: Log this into QML code.
        */
        NativeHelper.sendMockLocationDataToQml(counter, location.getLongitude(),
                                               location.getLatitude(), location.getAltitude());
        counter++;
    }

    @Override
    public void onProviderDisabled(String provider) {
        // TODO Auto-generated method stub
    }

    @Override
    public void onProviderEnabled(String provider) {
        // TODO Auto-generated method stub
    }

    @Override
    public void onStatusChanged(String provider, int status, Bundle extras) {
        // TODO Auto-generated method stub
    }

    public static void invoke(int x) {
        String toast = "Mocking location service already started, sorry!";
        if (x == 0) { // RUN SERVICE
            if (!m_instance.isMyServiceRunning(MockLocationService.class, m_instance)) {
                m_instance.startService(new Intent(m_instance, MockLocationService.class));
                toast = "Start mocking location data.";
            }
        } else if (x == 1) { // STOP SEVICE
            toast = "Mocking location service already stopped, sorry!";
            if (m_instance.isMyServiceRunning(MockLocationService.class, m_instance)) {
                m_instance.stopService(new Intent(m_instance, MockLocationService.class));
                toast = "Stop mocking location data.";
                NativeHelper.sendMockLocationDataToQml(0, 0D, 0D, 0D);
            }
        }
        final String fToast = toast;
        m_instance.runOnUiThread(new Runnable() {
            public void run() {
                Toast.makeText(m_instance, fToast, Toast.LENGTH_SHORT).show();
            }
        });
    }

    // https://stackoverflow.com/a/5921190
    private boolean isMyServiceRunning(Class<?> serviceClass, QmlDestroyTest m_instance) {
        ActivityManager manager = (ActivityManager) m_instance.getSystemService(Context.ACTIVITY_SERVICE);
        for (RunningServiceInfo service : manager.getRunningServices(Integer.MAX_VALUE)) {
            if (serviceClass.getName().equals(service.service.getClassName())) {
                return true;
            }
        }
        return false;
    }

    public static void vibrate(int x) {
        if (m_vibrator == null) {
            if (m_instance != null) {
              m_vibrator = (Vibrator) m_instance.getSystemService(Context.VIBRATOR_SERVICE);
              m_vibrator.vibrate(x);
            }
        } else {
            m_vibrator.vibrate(x);
        }
        Log.w(TAG, "Vibro: Java");
    }
}
