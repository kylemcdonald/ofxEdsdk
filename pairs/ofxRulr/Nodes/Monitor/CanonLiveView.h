#pragma once

#include "ofxRulr/Nodes/Base.h"
#include "ofxCvGui/Panels/Draws.h"

namespace ofxRulr {
	namespace Nodes {
		namespace Monitor {
			class CanonLiveView : public Base {
			public:
				CanonLiveView();
				string getTypeName() const override;

				void init();
				void update();

				ofxCvGui::PanelPtr getView();
			protected:
				void updateDrawObject();
				shared_ptr<ofxCvGui::Panels::Draws> view;
			};
		}
	}
}