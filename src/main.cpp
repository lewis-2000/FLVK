#include "fl_app.hpp" //App runner class
#include "logger.h" //Logger class


int main() {
	Logger logger;
	flApp app;

	try
	{
		app.run(); //run the app
	logger.information("App running"); //log that the app is running


	}
	catch (const std::exception &e)
	{
		logger.error(e.what()); //log the exception
		return EXIT_FAILURE; //return failure
	}

	return EXIT_SUCCESS; //return success
}