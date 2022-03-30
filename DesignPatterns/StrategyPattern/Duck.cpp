#pragma once
#include "Duck.h"
#include <iostream>
using namespace std;

void TenSecFly::fly() {
	cout << "Only Ten sec I can fly" << endl;
}


void CanNotFly::fly() {
	cout << "I cannot fly" << endl;
}

void DuckClass::performFly() {
	flyBehavior->fly();
}

void DuckClass::setFlyBehavior(FlyBehavior* uFlyBehavior) {
	flyBehavior = uFlyBehavior;
}