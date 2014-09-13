#include "CanonDSLRDevice.h"

namespace ofxMachineVision {
	namespace Device {
		//----------
		CanonDSLRDevice::CanonDSLRDevice() {
			this->openTime = 0;
			this->frameIndex = 0;
		}

		//----------
		Specification CanonDSLRDevice::open(int deviceID) {
			this->camera = shared_ptr<ofxEdsdk::Camera>(new ofxEdsdk::Camera());
			this->camera->setup(deviceID);

			this->openTime = ofGetElapsedTimeMicros();
			this->frameIndex = 0;

			this->camera->takePhoto();
			while (!this->camera->isFrameNew()) {
				this->camera->update();
				ofSleepMillis(1);
			}
			const auto & pixels = this->camera->getPhotoPixels();
			Specification specification(pixels.getWidth(), pixels.getHeight(), "Canon", "Unknown");
			specification.addFeature(ofxMachineVision::Feature::Feature_OneShot);

			return specification;
		}

		//----------
		void CanonDSLRDevice::close() {
			this->camera.reset();
		}

		//----------
		void CanonDSLRDevice::singleShot() {
			this->camera->takePhoto();
		}
		//----------
		void CanonDSLRDevice::updateIsFrameNew() {

		}

		//----------
		bool CanonDSLRDevice::isFrameNew() {
			return this->camera->isPhotoNew();
		}

		//----------
		shared_ptr<ofxMachineVision::Frame> CanonDSLRDevice::getFrame() {
			auto frame = shared_ptr<ofxMachineVision::Frame>(new Frame());
			frame->getPixelsRef() = this->camera->getPhotoPixels();
			frame->setTimestamp(ofGetElapsedTimeMicros() - this->openTime);
			frame->setFrameIndex(this->frameIndex++);
			return frame;
		}
	}
}