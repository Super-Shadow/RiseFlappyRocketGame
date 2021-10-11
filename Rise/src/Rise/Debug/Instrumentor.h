#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>

#include <thread>

namespace Rise
{
	struct ProfileResult
	{
		std::string Name;
		long long Start, End;
		size_t ThreadID;
	};

	struct InstrumentationSession
	{
		std::string Name;
	};

	class Instrumentor
	{
	public:
		Instrumentor() : m_CurrentSession(nullptr), m_ProfileCount(0) {}

		/* Explicitly disallow copying. */
		Instrumentor(const Instrumentor&) = delete;
		Instrumentor& operator= (const Instrumentor&) = delete;

		Instrumentor(Instrumentor&&) = delete;
		Instrumentor& operator=(Instrumentor&&) = delete;
		~Instrumentor() = default;

		void BeginSession(const std::string& name, const std::string& filepath = "results.json")
		{
			m_OutputStream.open(filepath);
			WriteHeader();
			m_CurrentSession = new InstrumentationSession{ name };
		}

		void EndSession()
		{
			WriteFooter();
			m_OutputStream.close();
			delete m_CurrentSession;
			m_CurrentSession = nullptr;
			m_ProfileCount = 0;
		}

		void WriteProfile(const ProfileResult& result)
		{
			if (m_ProfileCount++ > 0)
				m_OutputStream << ",";

			std::string name = result.Name;
			std::ranges::replace(name, '"', '\'');

			m_OutputStream << '{';
			m_OutputStream << R"("cat":"function",)";
			m_OutputStream << R"("dur":)" << (result.End - result.Start) << ',';
			m_OutputStream << R"("name":")" << name << R"(",)";
			m_OutputStream << R"("ph":"X",)";
			m_OutputStream << R"("pid":0,)";
			m_OutputStream << R"("tid":)" << result.ThreadID << ",";
			m_OutputStream << R"("ts":)" << result.Start;
			m_OutputStream << '}';

			m_OutputStream.flush();
		}

		void WriteHeader()
		{
			m_OutputStream << R"({"otherData": {},"traceEvents":[)";
			m_OutputStream.flush();
		}

		void WriteFooter()
		{
			m_OutputStream << "]}";
			m_OutputStream.flush();
		}

		static Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}
	private:
		InstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;
		int m_ProfileCount;
	};

	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* name) : m_Name(name), m_Stopped(false)
		{
			m_StartTimepoint = std::chrono::high_resolution_clock::now();
		}

		InstrumentationTimer(InstrumentationTimer const&) = delete;
		InstrumentationTimer& operator=(InstrumentationTimer const&) = delete;

		InstrumentationTimer(InstrumentationTimer&&) = delete;
		InstrumentationTimer& operator=(InstrumentationTimer&&) = delete;

		~InstrumentationTimer()
		{
			if (!m_Stopped)
				Stop();
		}

		void Stop()
		{
			const auto endTimepoint = std::chrono::high_resolution_clock::now();

			const auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
			const auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

			const auto threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
			Instrumentor::Get().WriteProfile({ m_Name, start, end, threadID });

			m_Stopped = true;
		}
	private:
		const char* m_Name;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
		bool m_Stopped;
	};
}

#define RS_PROFILE 1
#if RS_PROFILE
	#define RS_PROFILE_BEGIN_SESSION(name, filepath) ::Rise::Instrumentor::Get().BeginSession(name, filepath)
	#define RS_PROFILE_END_SESSION() ::Rise::Instrumentor::Get().EndSession()
	#define RS_PROFILE_SCOPE(name) ::Rise::InstrumentationTimer timer##__LINE__(name);
	#define RS_PROFILE_FUNCTION() RS_PROFILE_SCOPE(__FUNCSIG__)
#else
	#define RS_PROFILE_BEGIN_SESSION(name, filepath)
	#define RS_PROFILE_END_SESSION()
	#define RS_PROFILE_SCOPE(name)
	#define RS_PROFILE_FUNCTION()
#endif