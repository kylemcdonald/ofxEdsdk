# ofxEdsdk

ofxEdsdk requires the EDSDK library from Canon.

ofxEdsdk was developed with support from YCAM http://www.ycam.jp/


## Installation/Usage

1. Apply for a developer's license from [Canon's website](http://consumer.usa.canon.com/cusa/support/consumer/eos_slr_camera_systems/eos_digital_slr_cameras/digital_rebel_xt?fileURL=ps_sdk_form&pageKeyCode=downloadLicense&id=0901e02480057a74_1&productOverviewCid=0901e0248003ce28&keycode=Sdk_Lic) 
2. After you have been approved (can take anywhere from minutes to a day or two), follow the download instructions included in your confirmation email from Canon.
3. Download this repo as a zip file, unzip, and place contents in your addons folder.
4. Edit the folder name so that it only says "ofxEdsdk."
5. Open the Canon EDSDK .dmg image.
6. Copy the Eds* files into the directory `openFrameworks/addons/ofxEdsdk/src/EdsWrapper`
7. Open the OF Project Generator application and build a new app, including the ofxEdsdk addon.
8. In the new project, go to the project Build Settings and add `../../../addons/ofxEdsdk/libs/EDSDK/lib` to `Framework Search Paths`.

Following these steps will include Canon's developer library and this wrapper for all its functions for use in OF. You should be able to run the blank project successfully.

ofxEdsdk is tested with Canon SDK 3.6, on macOS 10.11-10.13 and Windows 8.1 with openFrameworks 0.9.2 and up.