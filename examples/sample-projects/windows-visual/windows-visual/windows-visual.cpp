#include "stdafx.h"

#include "modio.h"

int main(void)
{
	modio::Instance modio_instance(MODIO_ENVIRONMENT_TEST, 7, "e91c01b8882f4affeddd56c96111977b");

	volatile static bool finished = false;

	auto wait = [&]() {
		while (!finished)
		{
			modio_instance.sleep(10);
			modio_instance.process();
		}
	};

	auto finish = [&]() {
		finished = true;
	};

	// Before requesting mods, let's define the query filters
	modio::FilterCreator filter;
	filter.setLimit(7);
	filter.setCacheMaxAgeSeconds(100);

	std::cout << "Getting mods..." << std::endl;

	// Now we finished setting up the filters we are ready to request the mods
	modio_instance.getAllMods(filter, [&](const modio::Response &response, const std::vector<modio::Mod> &mods) {
		std::cout << "On mod get response: " << response.code << std::endl;
		
		finish();
	});

	wait();

	std::cout << "Process finishedd" << std::endl;

	return 0;
}