#pragma once
//#define FL_LOG

#include"fl\Headers.h"
#include<iostream>

using namespace fl;

class FuzzyLogic
{

public:
	FuzzyLogic();
	~FuzzyLogic();
	void InitEngine();
	float Update(float pos, float dr);
	float ManualUpdate();

	Engine* engine;
	InputVariable* Position;
	InputVariable* Direction;
	OutputVariable* SteerDir;
	RuleBlock* mamdani;
	Console* console;
	float input;
	bool running = true;
	int argc;

	fl::scalar distance = 0;
	fl::scalar speed = 0;
};
