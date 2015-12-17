#pragma once

#include "../../../addons/ofxEdsdk/src/ofxEdsdk.h"
#include "../../../addons/ofxMachineVision/src/ofxMachineVision/Device/Updating.h"
namespace ofxMachineVision {
	namespace Device {
		class CanonDSLRLiveViewDevice : public Updating {
		public:
			CanonDSLRLiveViewDevice();
			string getTypeName() const override;
			Specification open(int deviceID) override;
			void close() override;

			void updateIsFrameNew() override;
			bool isFrameNew() override;
			shared_ptr<Frame> getFrame() override;
		protected:
			int frameIndex;
			ofxMachineVision::Microseconds openTime;
			shared_ptr<ofxEdsdk::Camera> camera;
		};
	}
}