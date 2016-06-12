#include "toggle_Button.h"
#include "graphics.h"

Toggle_Button::Toggle_Button(Graphics& graphics, int height, int width) :
	Button(graphics, height, width),
	m_toggled(false)
{
	source_rect.y = m_height;
}

void Toggle_Button::toggle_button()
{
	m_toggled = !m_toggled;
	
	//Increase the offset of the height
	if (m_toggled)
	{
		source_rect.y = 0;
		return;
	}

	source_rect.y = m_height;
}