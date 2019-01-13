//
// QmlDestroyTest.java
//

package ru.exlmoto.qmldestroytest;

import android.util.Log;
import android.os.Bundle;
import android.os.Vibrator;
import android.content.Context;
import android.media.AudioManager;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

import android.location.Criteria;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.location.LocationProvider;
import android.os.AsyncTask;

public class QmlDestroyTest extends org.qtproject.qt5.android.bindings.QtActivity implements LocationListener {
    public static Vibrator m_vibrator;
    public static QmlDestroyTest m_instance;

    static String TAG = "QmlGpsMockProviderTest";
    static final String MOCK_GPS_PROVIDER_INDEX = "GpsMockProviderIndex";

    public static MockGpsProvider mMockGpsProviderTask = null;
    public static String[] fCoordinates;
    private static Integer mMockGpsProviderIndex = 0;

    public QmlDestroyTest() {
        m_instance = this;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        this.setVolumeControlStream(AudioManager.STREAM_MUSIC);
        super.onCreate(savedInstanceState);

        if (savedInstanceState instanceof Bundle) {
            mMockGpsProviderIndex = savedInstanceState.getInt(MOCK_GPS_PROVIDER_INDEX, 0);
        }

        /* Setup GPS */
        LocationManager locationManager = (LocationManager) getSystemService(Context.LOCATION_SERVICE);
        locationManager.addTestProvider(MockGpsProvider.GPS_MOCK_PROVIDER, false, false, false, false, true, true, true, Criteria.POWER_LOW,
                Criteria.ACCURACY_FINE);
        locationManager.setTestProviderEnabled(MockGpsProvider.GPS_MOCK_PROVIDER, true);
        locationManager.setTestProviderStatus(LocationManager.GPS_PROVIDER, LocationProvider.AVAILABLE, null, System.currentTimeMillis());

        if (locationManager.isProviderEnabled(MockGpsProvider.GPS_MOCK_PROVIDER)) {
            locationManager.requestLocationUpdates(MockGpsProvider.GPS_MOCK_PROVIDER, 0, 0, this);
            try {
                List<String> data = new ArrayList<String>();
                InputStream is = getAssets().open("mock_gps_data.csv");
                BufferedReader reader = new BufferedReader(new InputStreamReader(is));

                String line = null;
                while ((line = reader.readLine()) != null) {
                    data.add(line);
                }

                fCoordinates = new String[data.size()];
                data.toArray(fCoordinates);

//                mMockGpsProviderTask = new MockGpsProvider();
//                mMockGpsProviderTask.execute(coordinates);
//                INFO: Move this to invoke() method.
            } catch (Exception e) {
            }
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

        try {
            mMockGpsProviderTask.cancel(true);
            mMockGpsProviderTask = null;
        } catch (Exception e) {
        }

        try {
            LocationManager locationManager = (LocationManager) getSystemService(Context.LOCATION_SERVICE);
            locationManager.removeTestProvider(MockGpsProvider.GPS_MOCK_PROVIDER);
        } catch (Exception e) {
        }
    }

    @Override
    public void onSaveInstanceState(Bundle savedInstanceState) {
        savedInstanceState.putInt(MOCK_GPS_PROVIDER_INDEX, mMockGpsProviderIndex);
        super.onSaveInstanceState(savedInstanceState);
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
        NativeHelper.sendMockLocationDataToQml(mMockGpsProviderIndex.intValue(), location.getLongitude(),
                                               location.getLatitude(), location.getAltitude());
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

    /** Define a mock GPS provider as an asynchronous task of this Activity. */
    public static class MockGpsProvider extends AsyncTask<String, Integer, Void> {
        public static final String LOG_TAG = "GpsMockProvider";
        public static final String GPS_MOCK_PROVIDER = LocationManager.GPS_PROVIDER;

        private static QmlDestroyTest m_instance;

        /** Keeps track of the currently processed coordinate. */
        public Integer index = 0;

        public MockGpsProvider(QmlDestroyTest instance) {
            m_instance = instance;
        }

        @Override
        protected Void doInBackground(String... data) {
            // process data
            for (String str : data) {
                // skip data if needed (see the Activity's savedInstanceState functionality)
                if (index < mMockGpsProviderIndex) {
                    index++;
                    continue;
                }

                // let UI Thread know which coordinate we are processing
                publishProgress(index);

                // retrieve data from the current line of text
                Double latitude = null;
                Double longitude = null;
                Double altitude = null;
                try {
                    String[] parts = str.split(",");
                    latitude = Double.valueOf(parts[0]);
                    longitude = Double.valueOf(parts[1]);
                    altitude = Double.valueOf(parts[2]);
                } catch (NullPointerException e) {
                    break;
                } // no data available
                catch (Exception e) {
                    continue;
                } // empty or invalid line

                // translate to actual GPS location
                Location location = new Location(GPS_MOCK_PROVIDER);
                location.setLatitude(latitude);
                location.setLongitude(longitude);
                location.setAltitude(altitude);
                location.setAccuracy(1);
                location.setTime(System.currentTimeMillis());
                location.setBearing(0F);
                location.setSpeed(0.0F);
                location.setAccuracy(16F);
                location.setAltitude(0D);
                location.setBearing(0F);

                // show debug message in log
                Log.d(LOG_TAG, location.toString());

                // provide the new location
                LocationManager locationManager = (LocationManager) m_instance.getSystemService(Context.LOCATION_SERVICE);
                locationManager.setTestProviderLocation(GPS_MOCK_PROVIDER, location);

                // sleep for a while before providing next location
                try {
                    Thread.sleep(200);

                    // gracefully handle Thread interruption (important!)
                    if (Thread.currentThread().isInterrupted())
                        throw new InterruptedException("");
                } catch (InterruptedException e) {
                    break;
                }

                // keep track of processed locations
                index++;
            }

            return null;
        }

        @Override
        protected void onProgressUpdate(Integer... values) {
            Log.d(LOG_TAG, "onProgressUpdate():" + values[0]);
            mMockGpsProviderIndex = values[0];
        }
    }

    public static void invoke(int x) {
        String toast = "Mocking location data already started, sorry!";
        if (m_instance.mMockGpsProviderTask == null) {
            m_instance.mMockGpsProviderTask = new MockGpsProvider(m_instance);
            m_instance.mMockGpsProviderTask.execute(m_instance.fCoordinates);
            toast = "Start mocking location data.";
        }
        final String fToast = toast;
        m_instance.runOnUiThread(new Runnable() {
            public void run() {
                Toast.makeText(m_instance, fToast, Toast.LENGTH_SHORT).show();
            }
        });
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
