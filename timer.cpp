#include <mlpack/core.hpp>

using namespace mlpack;

int main(int argc, char** argv)
{
	CLI::ParseCommandLine(argc, argv);

	// Start a timer.
	Timer::Start("some_timer");

	// Do some things.
	for(int i=0; i<10000; i++);

	// Stop the timer.
	Timer::Stop("some_timer");
	return 0;
}

