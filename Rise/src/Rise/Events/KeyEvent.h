#pragma once

#include "Event.h"

namespace Rise
{
	class RISE_API KeyEvent : public Event
	{
	public:
		int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(const int keycode) : m_KeyCode(keycode) {}
		int m_KeyCode;
	};

	class RISE_API KeyPressedEvent final : public KeyEvent
	{
	public:
		KeyPressedEvent(const int keycode, const int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		[[nodiscard]] int GetRepeatCount() const { return m_RepeatCount; }

		// nodiscard just is warning saying "hey you used this function but havent used what it returns" mainly for functions that are purely done for that returning value.
		// Like why else would you call tostring but not store/use it?
		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent:" << GetKeyCode() << " (" << GetRepeatCount() << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class RISE_API KeyReleasedEvent final : public KeyEvent
	{
	public:
		KeyReleasedEvent(const int keycode) : KeyEvent(keycode) {}

		[[nodiscard]] std::string ToString() const override 
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent:" << GetKeyCode();
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}
