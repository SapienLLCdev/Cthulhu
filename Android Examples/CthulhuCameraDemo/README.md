Cthulhu Camera Demo
===================
This example app uses a simple frame difference method to detect motion within each frame from an Android device's front or back camera. This motion is then mapped to the 4x4 grid of electrodes on the Cthulhu Shield, connected via USB.

An evenly spaced 4x4 grid is drawn over the video stream. If the amount of motion (the difference between the previous and current frame) within one tile of the grid exceeds a threshold value, the cooresponding LED/electrode on the Cthulhu is activated. The user can adjust this threshold value using the 3-dot overflow menu on the apps toolbar. Lower threshold values will make the motion detection more sensitive (a smaller amount of motion will trigger an electrode). 

Installation
------------
The easiest way to install this app is via the Google Play Store, [here](https://play.google.com/store/apps/details?id=funkatronics.code.cthulhucamerademo&hl=en "CthulhuCameraMotionDemo")

Alternatively, the APK provided in this folder can be installed by enabling "Unknown Sources" in your devices security settings. With this setting enabled, you will be able to open the APK file on your device and Android will begin the installation automatically. 

You can also clone this repository to a folder on your computer and build the APK yourself. 

Credits
-------
Built by Marco Martinez ([Funkatronics](https://github.com/funkatronics "Funkatronics GitHub")) with support from Sapien, LLC

