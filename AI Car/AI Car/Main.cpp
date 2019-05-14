#include "main.h"

using namespace fl;

int main()
{
	std::cout << "Press 1 for manually entering variables into the FIS and 2 for a game" << std::endl;

	bool valid = false;
	int input;
	while (!valid) {
		if (std::cin >> input) {//this checks whether an integer was entered
			if (input == 1 || input == 2) valid = true;//then we have to see if this integer is in range
		}
		else std::cin.clear();//some cleaning up

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//empty input stream

		if (!valid) std::cout << "this input is not valid\n";
	}

	FIS.InitEngine();

	if (input == 1)
	{
		game.isPlaying = true;
		FIS.ManualUpdate();
		return 0;
	}
	else if (input == 2)
	{
		game.CreateDisplay();
		return 0;
	}
}