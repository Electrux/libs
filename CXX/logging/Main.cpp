#include "Logging.hpp"

int main()
{
	logging::Logger logger;
	logger.setLevel(logging::ALL);
	logger.fatal("fatality occurred");
	logger.warn("warning occurred");
	logger.info("info occurred");
	logger.debug("debug occurred");
	logger.trace("trace occurred");
	return 0;
}
