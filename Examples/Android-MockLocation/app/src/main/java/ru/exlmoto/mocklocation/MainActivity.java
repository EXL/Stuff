package ru.exlmoto.mocklocation;

import android.Manifest;
import android.annotation.SuppressLint;
import android.app.ActivityManager;
import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.provider.Settings;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements LocationListener {

    private final int DIALOG_MOCK_LOCATION = 0;
    private final int DIALOG_ERROR_OPEN_DEVELOPER_OPTIONS = 1;
    private final int REQUEST_PERMISSION_LOCATION = 2;
    private MainActivity mainActivity = null;
    private TextView textView = null;
    private TextView textViewLoc = null;
    private Button buttonStart = null;
    private Button buttonStop = null;
    private DialogListener dialogListener = null;
    private ErrorDialogListener errorDialogListener = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mainActivity = this;
        textView = findViewById(R.id.textView);
        textViewLoc = findViewById(R.id.textViewLoc);
        buttonStart = findViewById(R.id.buttonStart);
        buttonStop = findViewById(R.id.buttonStop);

        dialogListener = new DialogListener();
        errorDialogListener = new ErrorDialogListener();

        boolean mockEnable = isMockLocationEnabled();

        updateTextViewLocation(mockEnable);

        if (!mockEnable) {
            showDialog(DIALOG_MOCK_LOCATION);
        }

        LocationManager locationManager = (LocationManager) getSystemService(Context.LOCATION_SERVICE);
        if (locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER)) {
            showLocationPermission();
            locationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 0, 0, this);
        }

        buttonStart.setOnClickListener(new OnClickListener() {
            final MainActivity fMainActivity = mainActivity;

            @Override
            public void onClick(View view) {
                String toast = "Mocking location service already started, sorry!";
                if (!fMainActivity.isMyServiceRunning(MockLocationService.class)) {
                    fMainActivity.startService(new Intent(fMainActivity, MockLocationService.class));
                    toast = "Start mocking location data.";
                }
                showToast(toast);
            }
        });

        buttonStop.setOnClickListener(new OnClickListener() {
            final MainActivity fMainActivity = mainActivity;

            @Override
            public void onClick(View view) {
                String toast = "Mocking location service already stopped, sorry!";
                if (fMainActivity.isMyServiceRunning(MockLocationService.class)) {
                    fMainActivity.stopService(new Intent(fMainActivity, MockLocationService.class));
                    toast = "Stop mocking location data.";
                    textView.setText("");
                }
                showToast(toast);
            }
        });
    }

    // https://stackoverflow.com/a/35486162
    private void showLocationPermission() {
        int permissionCheck = ActivityCompat.checkSelfPermission(
                this, Manifest.permission.ACCESS_FINE_LOCATION);
        if (permissionCheck != PackageManager.PERMISSION_GRANTED) {
            if (ActivityCompat.shouldShowRequestPermissionRationale(this,
                    Manifest.permission.ACCESS_FINE_LOCATION)) {
                showExplanation("Permission Needed", "Rationale", Manifest.permission.ACCESS_FINE_LOCATION, REQUEST_PERMISSION_LOCATION);
            } else {
                requestPermission(Manifest.permission.ACCESS_FINE_LOCATION, REQUEST_PERMISSION_LOCATION);
            }
        } else {
            Toast.makeText(MainActivity.this, "Permission (already) Granted!", Toast.LENGTH_SHORT).show();
        }
    }

    @Override
    public void onRequestPermissionsResult(
            int requestCode,
            String permissions[],
            int[] grantResults) {
        switch (requestCode) {
            case REQUEST_PERMISSION_LOCATION:
                if (grantResults.length > 0
                        && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    Toast.makeText(MainActivity.this, "Permission Granted!", Toast.LENGTH_SHORT).show();
                } else {
                    Toast.makeText(MainActivity.this, "Permission Denied!", Toast.LENGTH_SHORT).show();
                }
        }
    }

    private void showExplanation(String title,
                                 String message,
                                 final String permission,
                                 final int permissionRequestCode) {
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle(title)
                .setMessage(message)
                .setPositiveButton(android.R.string.ok, new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int id) {
                        requestPermission(permission, permissionRequestCode);
                    }
                });
        builder.create().show();
    }

    private void requestPermission(String permissionName, int permissionRequestCode) {
        ActivityCompat.requestPermissions(this,
                new String[]{permissionName}, permissionRequestCode);
    }

    @Override
    protected void onResume() {
        super.onResume();

        updateTextViewLocation(isMockLocationEnabled());
    }

    private void updateTextViewLocation(boolean mockEnable) {
        if (mockEnable) {
            textViewLoc.setText("Allow Mock Location enabled.");
            buttonStart.setEnabled(true);
            buttonStop.setEnabled(true);
        } else {
            textViewLoc.setText("Allow Mock Location disabled.");
            buttonStart.setEnabled(false);
            buttonStop.setEnabled(false);
        }
    }

    private void showToast(String toast) {
        Toast.makeText(this, toast, Toast.LENGTH_SHORT).show();
    }

    // https://stackoverflow.com/a/5921190
    private boolean isMyServiceRunning(Class<?> serviceClass) {
        ActivityManager manager = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
        for (ActivityManager.RunningServiceInfo service : manager.getRunningServices(Integer.MAX_VALUE)) {
            if (serviceClass.getName().equals(service.service.getClassName())) {
                return true;
            }
        }
        return false;
    }

    @Override
    public void onLocationChanged(Location location) {
        if (textView != null) {
            textView.setText("LON: " + location.getLongitude() +
                    " | LAT: " + location.getLatitude() +
                    " | ALT: " + location.getAltitude());
        }
    }

    @Override
    public void onStatusChanged(String s, int i, Bundle bundle) {

    }

    @Override
    public void onProviderEnabled(String s) {

    }

    @Override
    public void onProviderDisabled(String s) {

    }

    protected Dialog onCreateDialog(int dialog) {
        switch (dialog) {
            case DIALOG_MOCK_LOCATION:
            default: {
                String text;
                if (Build.VERSION.SDK_INT >= 23) {
                    text = "The application must allow mock locations: (Settings => Developer Options => Select mock location app)";
                } else {
                    text = "Mock Locations are required for this application: (Settings => Developer Options => \"Allow mock locations\")";
                }
                AlertDialog.Builder builderDialog = new AlertDialog.Builder(this);
                builderDialog.setCancelable(false);
                builderDialog.setTitle("Enable Mock Location");
                builderDialog.setMessage(text);
                builderDialog.setPositiveButton("Settings", dialogListener);
                builderDialog.setNegativeButton("Cancel", dialogListener);
                return builderDialog.create();
            }
            case DIALOG_ERROR_OPEN_DEVELOPER_OPTIONS: {
                AlertDialog.Builder builderDialog = new AlertDialog.Builder(this);
                builderDialog.setCancelable(false);
                builderDialog.setTitle("Open developer settings error!");
                builderDialog.setMessage("Cannot open developer settings! See video for more information.");
                builderDialog.setPositiveButton("Show Video", errorDialogListener);
                builderDialog.setNegativeButton("Cancel", errorDialogListener);
                return builderDialog.create();
            }

        }
    }

    @SuppressLint({"NewApi"})
    public boolean isMockLocationEnabled() {
        boolean enabled = false;
        try {
            if (Build.VERSION.SDK_INT >= 23) {
                try {
                    LocationManager locationManager = (LocationManager) this.getSystemService(Context.LOCATION_SERVICE);
                    locationManager.addTestProvider("test", false, true, false, false, true, true, true, 3, 15);
                    locationManager.removeTestProvider("test");
                    enabled = true;
                } catch (Exception e) {
                    e.printStackTrace();
                }
            } else {
                enabled = !Settings.Secure.getString(this.getContentResolver(), "mock_location").equals("0");
            }
            return enabled;
        } catch (Exception unused) {
            return false;
        }
    }

    class DialogListener implements AlertDialog.OnClickListener {
        public void onClick(DialogInterface dialogInterface, int i) {
            switch (i) {
                case AlertDialog.BUTTON_NEGATIVE:
                default:
                    MainActivity.this.finish();
                    return;
                case AlertDialog.BUTTON_POSITIVE:
                    try {
                        if (Build.VERSION.SDK_INT < 26) {
                            MainActivity.this.startActivity(new Intent().setClassName("com.android.settings", "com.android.settings.DevelopmentSettings"));
                        } else if (Settings.Secure.getInt(MainActivity.this.getContentResolver(), "development_settings_enabled", 0) == 0) {
                            MainActivity.this.showDialog(DIALOG_ERROR_OPEN_DEVELOPER_OPTIONS);
                        } else {
                            MainActivity.this.startActivity(new Intent("android.settings.APPLICATION_DEVELOPMENT_SETTINGS"));
                        }
                    } catch (Exception unused) {
                        MainActivity.this.showDialog(DIALOG_ERROR_OPEN_DEVELOPER_OPTIONS);
                    }
            }
        }
    }

    class ErrorDialogListener implements AlertDialog.OnClickListener {
        public void onClick(DialogInterface dialogInterface, int i) {
            switch (i) {
                case AlertDialog.BUTTON_NEGATIVE:
                default:
                    MainActivity.this.finish();
                    return;
                case AlertDialog.BUTTON_POSITIVE:
                    MainActivity.this.startActivity(new Intent("android.intent.action.VIEW", Uri.parse("https://www.youtube.com/watch?v=hdz7ro0oZq8")));
                    MainActivity.this.finish();
            }
        }
    }
}
