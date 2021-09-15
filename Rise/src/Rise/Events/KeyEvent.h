#pragma once

#include "Event.h"

namespace Rise
{
	class RISE_API KeyEvent : public Event
	{
	public:
		[[nodiscard]] int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(const int keyCode) : m_KeyCode(keyCode) {}
		int m_KeyCode;
	};

	class RISE_API KeyPressedEvent final : public KeyEvent
	{
	public:
		KeyPressedEvent(const int keyCode, const int repeatCount) : KeyEvent(keyCode), m_RepeatCount(repeatCount) {}

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
		KeyReleasedEvent(const int keyCode) : KeyEvent(keyCode) {}

		[[nodiscard]] std::string ToString() const override 
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent:" << GetKeyCode();
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class RISE_API KeyTypedEvent final : public KeyEvent
	{
	public:
		KeyTypedEvent(const int keyCode) : KeyEvent(keyCode) {}

		// nodiscard just is warning saying "hey you used this function but havent used what it returns" mainly for functions that are purely done for that returning value.
		// Like why else would you call tostring but not store/use it?
		[[nodiscard]] std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent:" << GetKeyCode();
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}
