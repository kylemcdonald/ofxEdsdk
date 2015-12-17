#include "CanonDSLRDevice.h"
#include "ofAppGLFWWindow.h"

namespace ofxMachineVision {
	namespace Device {
		//----------
		CanonDSLRDevice::CanonDSLRDevice() {
			this->openTime = 0;
			this->frameIndex = 0;
			this->markFrameNew = false;
		}

		//----------
		string CanonDSLRDevice::getTypeName() const {
			return "CanonDSLRDevice";
		}

		//----------
		Specification CanonDSLRDevice::open(int deviceID) {
			this->camera = shared_ptr<ofxEdsdk::Camera>(new ofxEdsdk::Camera());
			if (!this->camera->setup(deviceID)) {
				return Specification();
			}

			this->openTime = ofGetElapsedTimeMicros();
			this->frameIndex = 0;

			//--
			//single shot with timeout
			this->camera->takePhoto();
			float startTime = ofGetElapsedTimef();
			while (!this->camera->isPhotoNew()) {
				this->camera->update();
				glfwPollEvents();
				ofSleepMillis(1);
				if (ofGetElapsedTimef() - startTime > 10.0f) {
					throw(ofxMachineVision::Exception("Timeout opening device CanonDSLRDevice. Check you have a memory card in your camera."));
				}
			}
			this->markFrameNew = true;
			//
			//--

			const auto & pixels = this->camera->getPhotoPixels();
			Specification specification(pixels.getWidth(), pixels.getHeight(), "Canon", "Photo");
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
			while (!this->camera->isPhotoNew()) {
				this->camera->update();
				glfwPollEvents();
				ofSleepMillis(1);
			}
			this->markFrameNew = true;
		}

		//----------
		void CanonDSLRDevice::updateIsFrameNew() {
			this->camera->update();
		}

		//----------
		bool CanonDSLRDevice::isFrameNew() {
			if (this->markFrameNew) {
				this->markFrameNew = false;
				return true;
			} else {
				return this->camera->isPhotoNew();
			}
		}

		//----------
		shared_ptr<Frame> CanonDSLRDevice::getFrame() {
			auto frame = shared_ptr<Frame>(new Frame());
			frame->getPixels() = this->camera->getPhotoPixels();
			frame->setTimestamp(ofGetElapsedTimeMicros() - this->openTime);
			frame->setFrameIndex(this->frameIndex++);
			return frame;
		}

		//----------
		shared_ptr<ofxEdsdk::Camera> CanonDSLRDevice::getCamera() {
			return this->camera;
		}
	}
}