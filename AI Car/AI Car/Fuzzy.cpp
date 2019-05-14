#include "Fuzzy.h"

Fuzzy::Fuzzy()
{
}

Fuzzy::~Fuzzy()
{
}

void Fuzzy::InitEngine()
{
	engine = new Engine;
	engine->setName("RacingLine");
	engine->setDescription("");

	Position = new InputVariable;
	Position->setName("Position");
	Position->setDescription("");
	Position->setEnabled(true);
	Position->setRange(-1.0, 1.0);
	Position->setLockValueInRange(true);
	Position->addTerm(new Trapezoid("farleft", -1.2, -1.0,-0.9, -0.7, 1.0));
	Position->addTerm(new Trapezoid("left", -0.9, -0.6, -0.5, -0.1, 1.0));
	Position->addTerm(new Triangle("centre", -1.0, 0.00, 1.000, 1.0));
	Position->addTerm(new Trapezoid("right", 0.1, 0.4, 0.7, 0.9, 1.0));
	Position->addTerm(new Trapezoid("farright", 0.7, 0.9, 1.0, 1.2, 1.0));
	engine->addInputVariable(Position);

	Direction = new InputVariable;
	Direction->setName("Direction");
	Direction->setDescription("");
	Direction->setEnabled(true);
	Direction->setRange(-1.0, 1.0);
	Direction->setLockValueInRange(true);
	Direction->addTerm(new Trapezoid("farleft", -1.2, -1.0, -0.9, -0.6, 1.0));
	Direction->addTerm(new Trapezoid("left", -0.8, -0.6, -0.3, -1.0));
	Direction->addTerm(new Triangle("straight", -0.8, 0.0, 0.8, 1.0));
	Direction->addTerm(new Trapezoid("right", 0.1, 0.3, 0.6, 0.8, 1.0));
	Direction->addTerm(new Trapezoid("farright", 0.6, 0.9, 1.0, 1.2, 1.0));
	engine->addInputVariable(Direction);

	SteerDir = new OutputVariable;
	SteerDir->setName("SteerDir");
	SteerDir->setDescription("");
	SteerDir->setEnabled(true);
	SteerDir->setRange(-2.000, 2.000);
	SteerDir->setLockValueInRange(true);
	SteerDir->setAggregation(new Maximum);
	SteerDir->setDefuzzifier(new Centroid);
	SteerDir->setDefaultValue(fl::nan);
	SteerDir->setLockPreviousValue(false);
	SteerDir->addTerm(new Triangle("farleft", -3.25, -2.0, -0.75, 1.0));
	SteerDir->addTerm(new Triangle("left", -1.4, -0.9, -0.4, 1.0));
	SteerDir->addTerm(new Triangle("straight", -1.5, 0.0, 1.5, 1.0));
	SteerDir->addTerm(new Triangle("right", 0.4, 0.9, 1.4, 1.0));
	SteerDir->addTerm(new Triangle("farright", 0.75, 2.0, 3.25, 1.0));
	engine->addOutputVariable(SteerDir);

	mamdani = new RuleBlock;
	mamdani->setName("");
	mamdani->setDescription("");
	mamdani->setEnabled(true);
	mamdani->setConjunction(new Minimum);
	mamdani->setDisjunction(new Maximum);
	mamdani->setImplication(new Minimum);
	mamdani->setActivation(new General);

	mamdani->addRule(Rule::parse("if Position is farleft and Direction is farleft then SteerDir is farright", engine));
	mamdani->addRule(Rule::parse("if Position is farleft and Direction is left then SteerDir is farright", engine));
	mamdani->addRule(Rule::parse("if Position is farleft and Direction is straight then SteerDir is farright", engine));
	mamdani->addRule(Rule::parse("if Position is farleft and Direction is right then SteerDir is right", engine));
	mamdani->addRule(Rule::parse("if Position is farleft and Direction is farright then SteerDir is left", engine));

	mamdani->addRule(Rule::parse("if Position is left and Direction is farleft then SteerDir is farright", engine));
	mamdani->addRule(Rule::parse("if Position is left and Direction is left then SteerDir is farright", engine));
	mamdani->addRule(Rule::parse("if Position is left and Direction is straight then SteerDir is right", engine));
	mamdani->addRule(Rule::parse("if Position is left and Direction is right then SteerDir is straight", engine));
	mamdani->addRule(Rule::parse("if Position is left and Direction is farright then SteerDir is left", engine));

	mamdani->addRule(Rule::parse("if Position is centre and Direction is farleft then SteerDir is farright", engine));
	mamdani->addRule(Rule::parse("if Position is centre and Direction is left then SteerDir is right", engine));
	mamdani->addRule(Rule::parse("if Position is centre and Direction is straight then SteerDir is straight", engine));
	mamdani->addRule(Rule::parse("if Position is centre and Direction is right then SteerDir is left", engine));
	mamdani->addRule(Rule::parse("if Position is centre and Direction is farright then SteerDir is farleft", engine));

	mamdani->addRule(Rule::parse("if Position is right and Direction is farleft then SteerDir is right", engine));
	mamdani->addRule(Rule::parse("if Position is right and Direction is left then SteerDir is straight", engine));
	mamdani->addRule(Rule::parse("if Position is right and Direction is straight then SteerDir is left", engine));
	mamdani->addRule(Rule::parse("if Position is right and Direction is right then SteerDir is farleft", engine));
	mamdani->addRule(Rule::parse("if Position is right and Direction is farright then SteerDir is farleft", engine));

	mamdani->addRule(Rule::parse("if Position is farright and Direction is farleft then SteerDir is straight", engine));
	mamdani->addRule(Rule::parse("if Position is farright and Direction is left then SteerDir is left", engine));
	mamdani->addRule(Rule::parse("if Position is farright and Direction is straight then SteerDir is farleft", engine));
	mamdani->addRule(Rule::parse("if Position is farright and Direction is right then SteerDir is farleft", engine));
	mamdani->addRule(Rule::parse("if Position is farright and Direction is farright then SteerDir is farleft", engine));

	engine->addRuleBlock(mamdani);

	std::string status;
	if (not engine->isReady(&status))
	{
		throw Exception("[Engine Error] its no ready :n" + status, FL_AT);

	}
}

float Fuzzy::Update(float pos, float dir)
{
	Position->setValue(pos);
	Direction->setValue(dir);
	engine->process();

	return SteerDir->getValue();
}

float Fuzzy::ManualUpdate()
{
	std::cout << "Enter how far the car is from the racing line (between -1 and 1, negative being left of the line and positive being right of the line" << std::endl;
	bool valid = false;
	int input;
	while (!valid) {
		if (std::cin >> input) {//this checks whether an integer was entered
			if (input >= -1 && input <= 1) valid = true;//then we have to see if this integer is in range
		}
		else std::cin.clear();//some cleaning up

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//empty input stream

		if (!valid) std::cout << "enter a number between -1 and 1\n";
	}

	Position->setValue(input);
	valid = false;
	input = NULL;

	std::cout << "Enter the direction the car is moving (between -1 and 1, -1 being far left and 1 being far right" << std::endl;
	while (!valid) {
		if (std::cin >> input) {//this checks whether an integer was entered
			if (input >= -1 && input <= 1) valid = true;//then we have to see if this integer is in range
		}
		else std::cin.clear();//some cleaning up

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//empty input stream

		if (!valid) std::cout << "enter a number between -1 and 1\n";
	}
	Direction->setValue(input);

	engine->process();
	std::cout << Position->getValue() << std::endl;
	std::cout << Direction->getValue() << std::endl;
	std::cout << SteerDir->getValue() << std::endl;

	return SteerDir->getValue();
}