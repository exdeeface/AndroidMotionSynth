/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#include <cstring>

namespace BinaryData
{

//================== NativeApp.java ==================
static const unsigned char temp_binary_data_0[] =
"package com.me.NativeAndroid;\r\n"
"import com.rmsl.juce.Java;\r\n"
"\r\n"
"import android.app.Application;\r\n"
"\r\n"
"import android.content.Context;\r\n"
"import android.hardware.Sensor;\r\n"
"import android.hardware.SensorEvent;\r\n"
"import android.hardware.SensorEventListener;\r\n"
"import android.hardware.SensorManager;\r\n"
"import android.util.Log;\r\n"
"\r\n"
"public class NativeApp extends Application implements SensorEventListener {\r\n"
"\r\n"
"    private final String TAG = \"lOOK AT ME!\";\r\n"
"\r\n"
"    private final float[] accelerometerReading = new float[3];\r\n"
"    private final float[] magnetometerReading = new float[3];\r\n"
"    private final float[] rotationMatrix = new float[9];\r\n"
"    private final float[] orientationAngles = new float[3];\r\n"
"\r\n"
"    static float pitch, roll, yaw = 0.00f;\r\n"
"\r\n"
"    SensorManager sensorManager;\r\n"
"\r\n"
"    @Override\r\n"
"    public void onCreate() {\r\n"
"        super.onCreate();\r\n"
"        sensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);\r\n"
"\r\n"
"        Sensor accelerometer = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);\r\n"
"        if (accelerometer != null) {\r\n"
"            sensorManager.registerListener(this, accelerometer, SensorManager.SENSOR_DELAY_NORMAL, SensorManager.SENSOR_DELAY_UI);\r\n"
"            //sensorManager.registerListener(MainActivity.this, accelerometer, SensorManager.SENSOR_DELAY_FASTEST);\r\n"
"        }\r\n"
"\r\n"
"        Sensor magneticField = sensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);\r\n"
"        if (magneticField != null) {\r\n"
"            sensorManager.registerListener(this, magneticField, SensorManager.SENSOR_DELAY_NORMAL, SensorManager.SENSOR_DELAY_UI);\r\n"
"            //sensorManager.registerListener(MainActivity.this, magneticField, SensorManager.SENSOR_DELAY_FASTEST);\r\n"
"        }\r\n"
"\r\n"
"        Log.i(TAG, \"onCreate: sensor manager started.\");\r\n"
"        Java.initialiseJUCE (this);\r\n"
"\r\n"
"    }\r\n"
"\r\n"
"    @Override\r\n"
"    public void onAccuracyChanged(Sensor sensor, int accuracy) {\r\n"
"        // Do something here if sensor accuracy changes.\r\n"
"        // You must implement this callback in your code.\r\n"
"    }\r\n"
"\r\n"
"    @Override\r\n"
"    public void onSensorChanged(SensorEvent event) {\r\n"
"        if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {\r\n"
"            System.arraycopy(event.values, 0, accelerometerReading, 0, accelerometerReading.length);\r\n"
"        } else if (event.sensor.getType() == Sensor.TYPE_MAGNETIC_FIELD) {\r\n"
"            System.arraycopy(event.values, 0, magnetometerReading, 0, magnetometerReading.length);\r\n"
"        }\r\n"
"        updateOrientationAngles();\r\n"
"    }\r\n"
"\r\n"
"    public void updateOrientationAngles() {\r\n"
"        SensorManager.getRotationMatrix(rotationMatrix, null, accelerometerReading, magnetometerReading);\r\n"
"        SensorManager.getOrientation(rotationMatrix, orientationAngles);\r\n"
"\r\n"
"        pitch = orientationAngles[1];\r\n"
"        roll = orientationAngles[2];\r\n"
"        yaw = orientationAngles[0];\r\n"
"        Log.i(TAG, \"updateOrientationAngles: THIS IS IN NATIVEapp.JAVA oops\");\r\n"
"    }\r\n"
"\r\n"
"    public static float getPitch() { return pitch; }\r\n"
"    public static float getRoll() { return roll; }\r\n"
"    public static float getYaw() { return yaw; }\r\n"
"}\r\n";

const char* NativeApp_java = (const char*) temp_binary_data_0;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes);
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;

    if (resourceNameUTF8 != nullptr)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x21d08ed7:  numBytes = 3086; return NativeApp_java;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "NativeApp_java"
};

const char* originalFilenames[] =
{
    "NativeApp.java"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
        if (strcmp (namedResourceList[i], resourceNameUTF8) == 0)
            return originalFilenames[i];

    return nullptr;
}

}
