#pragma once

#include "rspch.h"
#include "Rise/Core.h"

namespace Rise
{
	// Event in Rise are currently blockeing, meaning when and event occurs it immediately gets dispatched and must be dealt with right there and then.
	//For the future, a better strategy might be to buffer events in an event bus and process them during the "event" part of the update stage.

	enum class EventType
	{
		None,
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,
		AppTick,
		AppUpdate,
		AppRender,
		KeyPressed,
		KeyReleased,
		KeyTyped,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled
	};

	enum EventCategory
	{
		None,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4),
	};

	#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType() { return EventType::##type; }\
									virtual EventType GetEventType() const override { return GetStaticType(); }\
									virtual const char* GetName() const override { return #type; }

	#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class RISE_API Event
	{
	public:
		virtual ~Event() = default;
		[[nodiscard]] virtual EventType GetEventType() const abstract;
		[[nodiscard]] virtual const char* GetName() const abstract;
		[[nodiscard]] virtual int GetCategoryFlags() const abstract;
		[[nodiscard]] virtual std::string ToString() const { return GetName(); }

		[[nodiscard]] bool IsInCategory(const EventCategory category) const
		{
			return GetCategoryFlags() & category;
		}
	//protected:
		bool m_Handled = false;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event) : m_Event(event) {}

		// F will be deduced by the compiler
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if(m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*dynamic_cast<T*>(&m_Event)); // Dynamic cast since we are casting a base class to a derived class at runtime.
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}
