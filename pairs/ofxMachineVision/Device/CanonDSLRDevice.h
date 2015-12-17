#pragma once

#include "../../../addons/ofxEdsdk/src/ofxEdsdk.h"
#include "../../../addons/ofxMachineVision/src/ofxMachineVision/Device/Updating.h"
namespace ofxMachineVision {
	namespace Device {
		class CanonDSLRDevice : public Updating {
		public:
			CanonDSLRDevice();
			string getTypeName() const override;
			Specification open(int deviceID) override;
			void close() override;
			void singleShot() override;

			void updateIsFrameNew() override;
			bool isFrameNew() override;
			shared_ptr<Frame> getFrame() override;

			shared_ptr<ofxEdsdk::Camera> getCamera();
		protected:
			int frameIndex;
			bool markFrameNew;
			ofxMachineVision::Microseconds openTime;
			shared_ptr<ofxEdsdk::Camera> camera;
		};
	}
}