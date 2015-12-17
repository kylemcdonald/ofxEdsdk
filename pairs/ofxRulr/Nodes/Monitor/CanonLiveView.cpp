#include "CanonLiveView.h"

#include "ofxRulr/Nodes/Item/Camera.h"
#include "../../../addons/ofxEdsdk/pairs/ofxMachineVision/Device/CanonDSLRDevice.h"

namespace ofxRulr {
	namespace Nodes {
		namespace Monitor {
			//----------
			CanonLiveView::CanonLiveView() {
				RULR_NODE_INIT_LISTENER;
			}

			//----------
			string CanonLiveView::getTypeName() const {
				return "Monitor::CanonLiveView";
			}

			//----------
			void CanonLiveView::init() {
				RULR_NODE_UPDATE_LISTENER;

				this->addInput<Item::Camera>();

				this->view = make_shared<ofxCvGui::Panels::Draws>();
				this->view->setCaption("LiveView");
				this->view->onDraw += [this](ofxCvGui::DrawArguments & args) {
					if (!this->view->getDrawObject()) {
						//we have no target to draw, let's give a notice to the user
						ofxCvGui::Utils::drawText("Connect Item::Camera with device type CanonDSLRDevice", args.localBounds);
					}
				};
			}
			
			//----------
			void CanonLiveView::update() {
				this->updateDrawObject();
			}


			//----------
			ofxCvGui::PanelPtr CanonLiveView::getView() {
				return this->view;
			}

			//----------
			void CanonLiveView::updateDrawObject() {
				//try and set the view target to the canon device
				auto camera = this->getInput<Item::Camera>();
				if (camera) {
					auto grabber = camera->getGrabber();
					auto device = dynamic_pointer_cast<ofxMachineVision::Device::CanonDSLRDevice>(grabber->getDevice());
					if (device) {
						auto canonDevice = device->getCamera();
						this->view->setDrawObject(canonDevice->getLiveTexture());

						//we succeeded so lets exit
						return;
					}
				}

				//if we got here, then we're not valid and let's clear the object
				this->view->clearDrawObject();
			}
		}
	}
}