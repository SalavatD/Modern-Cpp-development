#include <sstream>
#include <string>

using namespace std;

class Logger {
public:
    explicit Logger(ostream &output_stream) : os(output_stream) {}

    void SetLogLine(bool value) { log_line = value; }

    bool GetLogLine() const { return log_line; }

    void SetLogFile(bool value) { log_file = value; }

    bool GetLogFile() const { return log_file; }

    void Log(const string &message) { os << message << endl; }

private:
    ostream &os;
    bool log_line = false;
    bool log_file = false;
};

#define LOG(logger, message) {                        \
    stringstream message_stream;                      \
    if (logger.GetLogFile()) {                        \
        message_stream << __FILE__;                   \
        if (logger.GetLogLine()) {                    \
            message_stream << ':' << __LINE__;        \
        }                                             \
        message_stream << ' ';                        \
    }                                                 \
    else if (logger.GetLogLine()) {                   \
        message_stream << "Line " << __LINE__ << ' '; \
    }                                                 \
    message_stream << message;                        \
    logger.Log(message_stream.str());                 \
}
