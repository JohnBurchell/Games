#pragma once
#ifndef __TOGGLE_BUTTON_H_
#define __TOGGLE_BUTTON_H_

#include "Button.h"

class Toggle_Button : public Button
{
public:
	Toggle_Button() = default;
	Toggle_Button(Graphics& graphics, const int height, const int width);

	void toggle_button();
	inline bool toggled() const { return m_toggled; };

private:
	bool m_toggled;
};

#endif //__TOGGLE_BUTTON_H_