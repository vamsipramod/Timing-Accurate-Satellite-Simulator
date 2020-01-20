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


class Output2FILE
{
    public:
        static FILE*& Stream();
        static void Output(const std::string& msg);
};

inline void initLogger(const char * file, TLogLevel level);
inline void endLogger();


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


#endif //__LOG_H__