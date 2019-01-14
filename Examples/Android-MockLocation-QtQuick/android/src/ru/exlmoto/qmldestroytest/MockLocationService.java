//
// MockLocationService.java
//

package ru.exlmoto.qmldestroytest;

import android.app.Service;
import android.content.Intent;
import android.content.Context;
import android.os.IBinder;
import android.os.AsyncTask;
import android.util.Log;

import android.location.Location;
import android.location.Criteria;
import android.location.LocationManager;
import android.location.LocationProvider;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

public class MockLocationService extends Service {

    public static final String LOG_TAG = "MockLocationService";

    private final String MOCK_GPS_PROVIDER_INDEX = "GpsMockProviderIndex";

    private MockGpsProvider mMockGpsProviderTask = null;
    private String[] fCoordinates;
    private Integer mMockGpsProviderIndex = 0;

    public void onCreate() {
        super.onCreate();
        Log.d(LOG_TAG, "onCreate");

        /* Setup GPS */
        LocationManager locationManager = (LocationManager) getSystemService(Context.LOCATION_SERVICE);
        locationManager.addTestProvider(MockGpsProvider.GPS_MOCK_PROVIDER, false, false, false, false, true, true, true, Criteria.POWER_LOW,
                Criteria.ACCURACY_FINE);
        locationManager.setTestProviderEnabled(MockGpsProvider.GPS_MOCK_PROVIDER, true);
        locationManager.setTestProviderStatus(LocationManager.GPS_PROVIDER, LocationProvider.AVAILABLE, null, System.currentTimeMillis());

        if (locationManager.isProviderEnabled(MockGpsProvider.GPS_MOCK_PROVIDER)) {
            // locationManager.requestLocationUpdates(MockGpsProvider.GPS_MOCK_PROVIDER, 0, 0, this);
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
//                INFO: Move this to the someTask() method.
            } catch (Exception e) {
            }
        }
    }

    public int onStartCommand(Intent intent, int flags, int startId) {
        Log.d(LOG_TAG, "onStartCommand");
        someTask();
        //return super.onStartCommand(intent, flags, startId);
        return START_STICKY;
    }

    public void onDestroy() {
        super.onDestroy();
        Log.d(LOG_TAG, "onDestroy");

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

    // INFO:
    // See: https://stackoverflow.com/questions/29368519/mock-location-not-working-on-google-map
    /** Define a mock GPS provider as an asynchronous task of this Activity. */
    public class MockGpsProvider extends AsyncTask<String, Integer, Void> {
        public static final String LOG_TAG = "GpsMockProvider";
        public static final String GPS_MOCK_PROVIDER = LocationManager.GPS_PROVIDER;

        /** Keeps track of the currently processed coordinate. */
        public Integer index = 0;

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
                // location.setAltitude(0D);
                location.setBearing(0F);

                // show debug message in log
                Log.d(LOG_TAG, location.toString());

                // provide the new location
                LocationManager locationManager = (LocationManager) getSystemService(Context.LOCATION_SERVICE);
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

    public IBinder onBind(Intent intent) {
        Log.d(LOG_TAG, "onBind");
        return null;
    }

    void someTask() {
        mMockGpsProviderTask = new MockGpsProvider();
        mMockGpsProviderTask.execute(fCoordinates);
    }
}
