// tester.cpp : Defines the entry point for the application.
//

#include "tester.h"

using namespace std;

#define INPUT_NO 4
#define OUTPUT_NO 1

int main()
{
//	vector<string> tmp1 = {"ascz", "asxcz", "asdf", "qset"};
	//vector<string>({ "ascz", "asxcz", "asdf", "qset" })
	
	//Signal::buildFromLabels({ "ascz", "asxcz", "asdf", "qset" });
	string inputs[] = {"input0", "input1", "input2", "input3"};
	unsigned int mask = 1;
	unsigned int val = 0;

	//for (int i = 0; i < INPUT_NO; i++)
	//{
	//	Signal::addSignal(inputs[i], (val & (mask << i)) ? HIGH_LEVEL : LOW_LEVEL, false, true);
	//}

	string outputs[] = { "output0" };
	for (int i = 0; i < OUTPUT_NO; i++)
	{
		Signal::addSignal(outputs[i], UNKNOWN_VALUE, true, false);
	}

	Gate::appendGate(new NotGate(Signal::buildFromLabels({ "input1" }), Signal::getSignal("not1"), "not1"));

	Gate::appendGate(new AndGate(Signal::buildFromLabels({ "input0", "not1" }), Signal::getSignal("and1"), "and1"));
	Gate::appendGate(new AndGate(Signal::buildFromLabels({ "input2", "not1" }), Signal::getSignal("and2"), "and2"));

	Gate::appendGate(new NorGate(Signal::buildFromLabels({ "input3", "not1" }), Signal::getSignal("nor1"), "nor1"));
	Gate::appendGate(new NorGate(Signal::buildFromLabels({ "and1", "and2", "nor1" }), Signal::getSignal("output0"), "nor2"));


	for (val = 0; val < power(2, INPUT_NO); val++) {
		for (int i = 0; i < INPUT_NO; i++)
		{
			Signal::getSignal(inputs[i])->setValue((val & (mask << i)) ? HIGH_LEVEL : LOW_LEVEL);
		}

		Gate::setOutputOfAllGates();

		Signal* tmp;


		for (int i = 0; i < INPUT_NO; i++)
		{
			tmp = Signal::getSignal(inputs[i]);
			cout << "|" << tmp->getLabel() << "=" << getValueName(tmp->getValue());
		}
		cout << "|" << endl;

		for (int i = 0; i < OUTPUT_NO; i++)
		{
			tmp = Signal::getSignal(outputs[i]);
			cout << tmp->getLabel() << ": " << getValueName(tmp->getValue()) << endl;
		}

		Signal::unsetAllSignals();
	}
	

	//cout << "label: " << Signal::getSignal("asdf")->getLabel() << endl << "value: " << Signal::getSignal("asdf")->getValue() << endl;

	return 0;
}
