
#ifndef __LOG_H__
#define __LOG_H__

#include <sstream>
#include <string>
#include <stdio.h>

inline std::string NowTime();

//enum TLogLevel {logERROR, logWARNING, logINFO, logDEBUG, logDEBUG1, logDEBUG2, logDEBUG3, logDEBUG4};
enum TLogLevel {lerror, lwarning, linfo, ldebug, ldebug1, ldebug2, ldebug3, ldebug4};

template <typename T>
class Log
{
public:
    Log();
    virtual ~Log();
    std::ostringstream& Get(TLogLevel level = linfo);
public:
    static TLogLevel& ReportingLevel();
    static std::string ToString(TLogLevel level);
    static TLogLevel FromString(const std::string& level);
protected:
    std::ostringstream os;
private:
    Log(const Log&);
    Log& operator =(const Log&);
};

template <typename T>
Log<T>::Log()
{
}

template <typename T>
std::ostringstream& Log<T>::Get(TLogLevel level)
{
    os << "- " << NowTime();
    os << " " << ToString(level) << ": ";
    os << std::string(level > ldebug ? level - ldebug : 0, '\t');
    return os;
}

template <typename T>
Log<T>::~Log()
{
    os << std::endl;
    T::Output(os.str());
}

template <typename T>
TLogLevel& Log<T>::ReportingLevel()
{
    static TLogLevel reportingLevel = ldebug4;
    return reportingLevel;
}

template <typename T>
std::string Log<T>::ToString(TLogLevel level)
{
	static const char* const buffer[] = {"ERROR", "WARNING", "INFO", "DEBUG", "DEBUG1", "DEBUG2", "DEBUG3", "DEBUG4"};
    return buffer[level];
}

template <typename T>
TLogLevel Log<T>::FromString(const std::string& level)
{
    if (level == "DEBUG4")
        return ldebug4;
    if (level == "DEBUG3")
        return ldebug3;
    if (level == "DEBUG2")
        return ldebug2;
    if (level == "DEBUG1")
        return ldebug1;
    if (level == "DEBUG")
        return ldebug;
    if (level == "INFO")
        return linfo;
    if (level == "WARNING")
        return lwarning;
    if (level == "ERROR")
        return lerror;
    Log<T>().Get(lwarning) << "Unknown logging level '" << level << "'. Using INFO level as default.";
    return linfo;
}

class Output2FILE
{
public:
    static FILE*& Stream();
    static void Output(const std::string& msg);
};

inline FILE*& Output2FILE::Stream()
{
    static FILE* pStream = stderr;
    return pStream;
}

inline void Output2FILE::Output(const std::string& msg)
{   
    FILE* pStream = Stream();
    if (!pStream)
        return;
    fprintf(pStream, "%s", msg.c_str());
    fflush(pStream);
}

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#   if defined (BUILDING_FILELOG_DLL)
#       define FILELOG_DECLSPEC   __declspec (dllexport)
#   elif defined (USING_FILELOG_DLL)
#       define FILELOG_DECLSPEC   __declspec (dllimport)
#   else
#       define FILELOG_DECLSPEC
#   endif // BUILDING_DBSIMPLE_DLL
#else
#   define FILELOG_DECLSPEC
#endif // _WIN32

class FILELOG_DECLSPEC FILELog : public Log<Output2FILE> {};
//typedef Log<Output2FILE> FILELog;

#ifndef FILELOG_MAX_LEVEL
#define FILELOG_MAX_LEVEL ldebug4
#endif

#define FILE_LOG(level) \
    if (level > FILELOG_MAX_LEVEL) ;\
    else if (level > FILELog::ReportingLevel() || !Output2FILE::Stream()) ; \
    else FILELog().Get(level)

#define LOG(level) \
if (level > FILELOG_MAX_LEVEL) ;\
else if (level > FILELog::ReportingLevel() || !Output2FILE::Stream()) ; \
else FILELog().Get(level)

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)

#include <windows.h>

inline std::string NowTime()
{
    const int MAX_LEN = 200;
    char buffer[MAX_LEN];
    if (GetTimeFormatA(LOCALE_USER_DEFAULT, 0, 0, 
            "HH':'mm':'ss", buffer, MAX_LEN) == 0)
        return "Error in NowTime()";

    char result[100] = {0};
    static DWORD first = GetTickCount();
    std::sprintf(result, "%s.%03ld", buffer, (long)(GetTickCount() - first) % 1000); 
    return result;
}

#else

#include <sys/time.h>

inline std::string NowTime()
{
    char buffer[11];
    time_t t;
    time(&t);
    tm r = {0};
    strftime(buffer, sizeof(buffer), "%X", localtime_r(&t, &r));
    struct timeval tv;
    gettimeofday(&tv, 0);
    char result[100] = {0};
    std::sprintf(result, "%s.%03ld", buffer, (long)tv.tv_usec / 1000); 
    return result;
}

#endif //WIN32

inline void initLogger(const char * file, TLogLevel level)
{
    FILELog::ReportingLevel() = level;
    FILE* log_fd = fopen( file, "w" );
    Output2FILE::Stream() = log_fd;
}

inline void endLogger()
{
	if (Output2FILE::Stream())
		fclose(Output2FILE::Stream());
}

#endif //__LOG_H__