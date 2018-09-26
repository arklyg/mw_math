#include <mwglobal.h>
#include <mwlogger.h>

#include <mwmathglobal.h>

#define PROGRAMM_NAME "mwmathserializabletest"

class TestSerializableSingleton;

class TestSerializableSingleton : public MWSingleton<TestSerializableSingleton>, public MWSerializableSingleton
{
public:
};

int main(int argc, const char* argv[])
{
	init_logger(PROGRAMM_NAME);
	
	LOG_INFO(_logger, PROGRAMM_NAME << " start");

	
}
