#pragma once

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
		friend class EventDispatcher;
	public:
		virtual ~Event() = default;
		[[nodiscard]] virtual EventType GetEventType() const abstract;
		[[nodiscard]] virtual const char* GetName() const abstract;
		[[nodiscard]] virtual int GetCategoryFlags() const abstract;
		[[nodiscard]] virtual std::string ToString() const { return GetName(); }

		[[nodiscard]] bool IsInCategory(EventCategory category) const
		{
			return GetCategoryFlags() & category;
		}
	protected:
		bool m_Handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : m_Event(event){}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if(m_Event.GetEventType() == T::GetStaticType())
			{
				// maybe better ways will have to check once code it fully complete!
				// I will be able to compare results of each one, ideally want bit_cast since it is the newest but idk if it is what the code wants u dig dog!
				//				m_Event.m_Handled = func(*std::bit_cast<T*>(&m_Event));
				//				m_Event.m_Handled = func(*static_cast<T*>(&m_Event));

				m_Event.m_Handled = func(*(T*)(&m_Event));
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