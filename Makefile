#Copyright (c) 2019-2020 <>< Charles Lohr - Under the MIT/x11 or NewBSD License you choose.
# NO WARRANTY! NO GUARANTEE OF SUPPORT! USE AT YOUR OWN RISK

all : demo.apk

.PHONY : push run

# WARNING WARNING WARNING!  YOU ABSOLUTELY MUST OVERRIDE THE PROJECT NAME
# you should also override these parameters, get your own signatre file and make your own manifest.
APPNAME?=demo
LABEL?=$(APPNAME)
APKFILE ?= $(APPNAME).apk
PACKAGENAME?=com.sulav.$(APPNAME)
RAWDRAWANDROID?=./giga
RAWDRAWANDROIDSRCS=$(RAWDRAWANDROID)/android_native_app_glue.c
SRC?=lib/launch.c

#We've tested it with android version 22, 24, 28, 29 and 30.
#You can target something like Android 28, but if you set ANDROIDVERSION to say 22, then
#Your app should (though not necessarily) support all the way back to Android 22. 
ANDROIDVERSION?=28
ANDROIDTARGET?=$(ANDROIDVERSION)
#Default is to be strip down, but your app can override it.
CFLAGS?=-ffunction-sections -Os -fdata-sections -Wall -fvisibility=hidden
LDFLAGS?=-Wl,--gc-sections -s
ANDROID_FULLSCREEN?=y
ADB?=adb
UNAME := $(shell uname)





ANDROIDSRCS:= $(SRC) $(RAWDRAWANDROIDSRCS)

#if you have a custom Android Home location you can add it to this list.  
#This makefile will select the first present folder.


ifeq ($(UNAME), Linux)
OS_NAME = linux-x86_64
endif
ifeq ($(UNAME), Darwin)
OS_NAME = darwin-x86_64
endif
ifeq ($(OS), Windows_NT)
OS_NAME = windows-x86_64
endif

# Search list for where to try to find the SDK
SDK_LOCATIONS += $(ANDROID_HOME) $(ANDROID_SDK_ROOT) ~/Android/Sdk $(HOME)/Library/Android/sdk

#Just a little Makefile witchcraft to find the first SDK_LOCATION that exists
#Then find an ndk folder and build tools folder in there.
ANDROIDSDK?=$(firstword $(foreach dir, $(SDK_LOCATIONS), $(basename $(dir) ) ) )
NDK?=$(firstword $(ANDROID_NDK) $(ANDROID_NDK_HOME) $(wildcard $(ANDROIDSDK)/ndk/*) $(wildcard $(ANDROIDSDK)/ndk-bundle/*) )
BUILD_TOOLS?=$(lastword $(wildcard $(ANDROIDSDK)/build-tools/*) )

# fall back to default Android SDL installation location if valid NDK was not found
ifeq ($(NDK),)
ANDROIDSDK := ~/Android/Sdk
endif

# Verify if directories are detected
ifeq ($(ANDROIDSDK),)
$(error ANDROIDSDK directory not found)
endif
ifeq ($(NDK),)
$(error NDK directory not found)
endif
ifeq ($(BUILD_TOOLS),)
$(error BUILD_TOOLS directory not found)
endif

testsdk :
	@echo "SDK:\t\t" $(ANDROIDSDK)
	@echo "NDK:\t\t" $(NDK)
	@echo "Build Tools:\t" $(BUILD_TOOLS)

CFLAGS+=-Os -DANDROID -DAPPNAME=\"$(APPNAME)\"
ifeq (ANDROID_FULLSCREEN,y)
CFLAGS +=-DANDROID_FULLSCREEN
endif
CFLAGS+= -I$(RAWDRAWANDROID)/rawdraw -I$(NDK)/sysroot/usr/include -I$(NDK)/sysroot/usr/include/android -I$(NDK)/toolchains/llvm/prebuilt/$(OS_NAME)/sysroot/usr/include/android -fPIC -I$(RAWDRAWANDROID) -DANDROIDVERSION=$(ANDROIDVERSION)
LDFLAGS += -lm -lGLESv3 -lEGL -landroid -llog
LDFLAGS += -shared -uANativeActivity_onCreate

CC_ARM64:=$(NDK)/toolchains/llvm/prebuilt/$(OS_NAME)/bin/aarch64-linux-android$(ANDROIDVERSION)-clang
CC_ARM32:=$(NDK)/toolchains/llvm/prebuilt/$(OS_NAME)/bin/armv7a-linux-androideabi$(ANDROIDVERSION)-clang
CC_x86:=$(NDK)/toolchains/llvm/prebuilt/$(OS_NAME)/bin/i686-linux-android$(ANDROIDVERSION)-clang
CC_x86_64=$(NDK)/toolchains/llvm/prebuilt/$(OS_NAME)/bin/x86_64-linux-android$(ANDROIDVERSION)-clang
AAPT:=$(BUILD_TOOLS)/aapt

# Which binaries to build? Just comment/uncomment these lines:
TARGETS += build/lib/arm64-v8a/lib$(APPNAME).so
TARGETS += build/lib/armeabi-v7a/lib$(APPNAME).so
# TARGETS += build/lib/x86/lib$(APPNAME).so
# TARGETS += build/lib/x86_64/lib$(APPNAME).so

CFLAGS_ARM64:=-m64
CFLAGS_ARM32:=-mfloat-abi=softfp -m32
CFLAGS_x86:=-march=i686 -mtune=intel -mssse3 -mfpmath=sse -m32
CFLAGS_x86_64:=-march=x86-64 -msse4.2 -mpopcnt -m64 -mtune=intel
STOREPASS?=password
DNAME:="CN=example.com, OU=ID, O=Example, L=Doe, S=John, C=GB"
KEYSTOREFILE:=my-release-key.keystore
ALIASNAME?=standkey

keystore : $(KEYSTOREFILE)

$(KEYSTOREFILE) :
	keytool -genkey -v -keystore $(KEYSTOREFILE) -alias $(ALIASNAME) -keyalg RSA -keysize 2048 -validity 10000 -storepass $(STOREPASS) -keypass $(STOREPASS) -dname $(DNAME)

folders:
	mkdir -p build/lib/arm64-v8a
	mkdir -p build/lib/armeabi-v7a
	mkdir -p build/lib/x86
	mkdir -p build/lib/x86_64

build/lib/arm64-v8a/lib$(APPNAME).so : $(ANDROIDSRCS)
	mkdir -p build/lib/arm64-v8a
	$(CC_ARM64) $(CFLAGS) $(CFLAGS_ARM64) -o $@ $^ -L$(NDK)/toolchains/llvm/prebuilt/$(OS_NAME)/sysroot/usr/lib/aarch64-linux-android/$(ANDROIDVERSION) $(LDFLAGS)

build/lib/armeabi-v7a/lib$(APPNAME).so : $(ANDROIDSRCS)
	mkdir -p build/lib/armeabi-v7a
	$(CC_ARM32) $(CFLAGS) $(CFLAGS_ARM32) -o $@ $^ -L$(NDK)/toolchains/llvm/prebuilt/$(OS_NAME)/sysroot/usr/lib/arm-linux-androideabi/$(ANDROIDVERSION) $(LDFLAGS)

build/lib/x86/lib$(APPNAME).so : $(ANDROIDSRCS)
	mkdir -p build/lib/x86
	$(CC_x86) $(CFLAGS) $(CFLAGS_x86) -o $@ $^ -L$(NDK)/toolchains/llvm/prebuilt/$(OS_NAME)/sysroot/usr/lib/i686-linux-android/$(ANDROIDVERSION) $(LDFLAGS)

build/lib/x86_64/lib$(APPNAME).so : $(ANDROIDSRCS)
	mkdir -p build/lib/x86_64
	$(CC_x86) $(CFLAGS) $(CFLAGS_x86_64) -o $@ $^ -L$(NDK)/toolchains/llvm/prebuilt/$(OS_NAME)/sysroot/usr/lib/x86_64-linux-android/$(ANDROIDVERSION) $(LDFLAGS)

#We're really cutting corners.  You should probably use resource files.. Replace android:label="@string/app_name" and add a resource file.
#Then do this -S Sources/res on the aapt line.
#For icon support, add -S build/res to the aapt line.  also,  android:icon="@mipmap/icon" to your application line in the manifest.
#If you want to strip out about 800 bytes of data you can remove the icon and strings.

#Notes for the past:  These lines used to work, but don't seem to anymore.  Switched to newer jarsigner.
#(zipalign -c -v 8 build.apk)||true #This seems to not work well.
#jarsigner -verify -verbose -certs build.apk



build.apk : $(TARGETS) $(EXTRA_ASSETS_TRIGGER) giga/AndroidManifest.xml
	mkdir -p build/assets
	cp -r giga/Sources/assets/* build/assets
	cp -R vendor/arm64-v8a/libbass.so build/lib/arm64-v8a 
	cp -R vendor/armeabi-v7a/libbass.so build/lib/armeabi-v7a 
	# cp -R vendor/x86/libbass.so build/lib/x86 
	# cp -R vendor/x86_64/libbass.so build/lib/x86_64 
	
	rm -rf temp.apk
	$(AAPT) package -f -F temp.apk -I $(ANDROIDSDK)/platforms/android-$(ANDROIDVERSION)/android.jar -M giga/AndroidManifest.xml -S giga/Sources/res -A build/assets -v --target-sdk-version $(ANDROIDTARGET)
	unzip -o temp.apk -d build
	rm -rf build.apk
	cd build && zip -D9r ../build.apk . && zip -D0r ../build.apk ./resources.arsc ./AndroidManifest.xml
	jarsigner -sigalg SHA1withRSA -digestalg SHA1 -verbose -keystore $(KEYSTOREFILE) -storepass $(STOREPASS) build.apk $(ALIASNAME)
	rm -rf $(APKFILE)
	$(BUILD_TOOLS)/zipalign -v 4 build.apk $(APKFILE)
	#Using the apksigner in this way is only required on Android 30+
	$(BUILD_TOOLS)/apksigner sign --key-pass pass:$(STOREPASS) --ks-pass pass:$(STOREPASS) --ks $(KEYSTOREFILE) $(APKFILE)
	rm -rf temp.apk
	rm -rf build.apk
	@ls -l $(APKFILE)

manifest: giga/AndroidManifest.xml

android/AndroidManifest.xml :
	rm -rf giga/AndroidManifest.xml
	PACKAGENAME=$(PACKAGENAME) \
		ANDROIDVERSION=$(ANDROIDVERSION) \
		ANDROIDTARGET=$(ANDROIDTARGET) \
		APPNAME=$(APPNAME) \
		LABEL=$(LABEL) envsubst '$$ANDROIDTARGET $$ANDROIDVERSION $$APPNAME $$PACKAGENAME $$LABEL' \
		< giga/AndroidManifest.xml.template > giga/AndroidManifest.xml


uninstall : 
	($(ADB) uninstall $(PACKAGENAME))||true

push : build.apk
	@echo "Installing" $(PACKAGENAME)
	$(ADB) install -r $(APKFILE)

run : push
	$(eval ACTIVITYNAME:=$(shell $(AAPT) dump badging $(APKFILE) | grep "launchable-activity" | cut -f 2 -d"'"))
	$(ADB) shell am start -n $(PACKAGENAME)/$(ACTIVITYNAME)

clean :
	rm -rf temp.apk build.apk build $(APKFILE)

