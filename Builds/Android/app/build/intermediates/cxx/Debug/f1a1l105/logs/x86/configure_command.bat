@echo off
"C:\\Users\\Exdee\\AppData\\Local\\Android\\Sdk\\cmake\\3.22.1\\bin\\cmake.exe" ^
  "-HC:\\Users\\Exdee\\JUCE\\proj\\TestSynth\\Builds\\Android\\app" ^
  "-DCMAKE_SYSTEM_NAME=Android" ^
  "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON" ^
  "-DCMAKE_SYSTEM_VERSION=29" ^
  "-DANDROID_ABI=x86" ^
  "-DCMAKE_ANDROID_ARCH_ABI=x86" ^
  "-DANDROID_NDK=C:\\Users\\Exdee\\AppData\\Local\\Android\\Sdk\\ndk\\25.2.9519653" ^
  "-DCMAKE_ANDROID_NDK=C:\\Users\\Exdee\\AppData\\Local\\Android\\Sdk\\ndk\\25.2.9519653" ^
  "-DCMAKE_TOOLCHAIN_FILE=C:\\Users\\Exdee\\AppData\\Local\\Android\\Sdk\\ndk\\25.2.9519653\\build\\cmake\\android.toolchain.cmake" ^
  "-DCMAKE_MAKE_PROGRAM=C:\\Users\\Exdee\\AppData\\Local\\Android\\Sdk\\cmake\\3.22.1\\bin\\ninja.exe" ^
  "-DCMAKE_C_FLAGS=-O0" ^
  "-DCMAKE_CXX_FLAGS=-O0" ^
  "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=C:\\Users\\Exdee\\JUCE\\proj\\TestSynth\\Builds\\Android\\app\\build\\intermediates\\cxx\\Debug\\f1a1l105\\obj\\x86" ^
  "-DCMAKE_RUNTIME_OUTPUT_DIRECTORY=C:\\Users\\Exdee\\JUCE\\proj\\TestSynth\\Builds\\Android\\app\\build\\intermediates\\cxx\\Debug\\f1a1l105\\obj\\x86" ^
  "-DCMAKE_BUILD_TYPE=Debug" ^
  "-BC:\\Users\\Exdee\\JUCE\\proj\\TestSynth\\Builds\\Android\\app\\.cxx\\Debug\\f1a1l105\\x86" ^
  -GNinja ^
  "-DANDROID_TOOLCHAIN=clang" ^
  "-DANDROID_PLATFORM=android-29" ^
  "-DANDROID_STL=c++_static" ^
  "-DANDROID_CPP_FEATURES=exceptions rtti" ^
  "-DANDROID_ARM_MODE=arm" ^
  "-DANDROID_ARM_NEON=TRUE" ^
  "-DCMAKE_CXX_STANDARD=17" ^
  "-DCMAKE_CXX_EXTENSIONS=OFF" ^
  "-DJUCE_BUILD_CONFIGURATION=DEBUG"
