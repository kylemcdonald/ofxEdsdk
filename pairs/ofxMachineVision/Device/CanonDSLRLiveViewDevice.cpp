#include "CanonDSLRLiveViewDevice.h"
#include "ofAppGLFWWindow.h"

namespace ofxMachineVision {
	namespace Device {
		//----------
		CanonDSLRLiveViewDevice::CanonDSLRLiveViewDevice() {
			this->openTime = 0;
			this->frameIndex = 0;
		}

		//----------
		string CanonDSLRLiveViewDevice::getTypeName() const {
			return "CanonDSLRLiveViewDevice";
		}

		//----------
		Specification CanonDSLRLiveViewDevice::open(int deviceID) {
			this->camera = make_shared<ofxEdsdk::Camera>();

			try {
				if (!this->camera->setup(deviceID)) {
                    auto message = "Cannot open camera [" + ofToString(deviceID) + "]";
					throw(Exception(message));
				}

				this->openTime = ofGetElapsedTimeMicros();
				this->frameIndex = 0;

				//wait for the first live view frame to arrive
				auto startTime = ofGetElapsedTimeMillis();
				while (!this->camera->isLiveReady()) {
					if (ofGetElapsedTimeMillis() - startTime > 5000) {
						throw(Exception("Timeout getting first frame"));
					}
					ofSleepMillis(10);
					this->camera->update();
				}
			}
			catch (Exception e) {
				ofLogError("ofxMachineVision::Device::CanonDSLRLiveViewDevice::open") << e.what();
				return Specification();
			}

			//copy the specification from the first live view frame
			const auto & pixels = this->camera->getLivePixels();
			Specification specification(pixels.getWidth(), pixels.getHeight(), "Canon", "LiveView");
			specification.addFeature(ofxMachineVision::Feature::Feature_FreeRun);

			return specification;
		}

		//----------
		void CanonDSLRLiveViewDevice::close() {
			this->camera.reset();
		}

		//----------
		void CanonDSLRLiveViewDevice::updateIsFrameNew() {
			this->camera->update();
		}

		//----------
		bool CanonDSLRLiveViewDevice::isFrameNew() {
			return this->camera->isFrameNew();
		}

		//----------
		shared_ptr<Frame> CanonDSLRLiveViewDevice::getFrame() {
			auto frame = shared_ptr<Frame>(new Frame());
			frame->getPixels() = this->camera->getLivePixels();
			frame->setTimestamp(ofGetElapsedTimeMicros() - this->openTime);
			frame->setFrameIndex(this->frameIndex++);
			return frame;
		}
	}
}