#include "Duck.h"

int main()
{
    //1. I create a mallard duck class
    //Notice how I code to the interface, not the implementation
    DuckClass* mallard = new MallardDuckClass();

    //3. performFly prints that the mallard duck does fly
    mallard->performFly();

    //4. Now I'm going to create a new behaviors which takes away the quacking and flying from the mallard duck

    FlyBehavior* nowICantFly = new CanNotFly();

    //5. I'm going to set the new quack behaviors to the mallard duck
    mallard->setFlyBehavior(nowICantFly);

    //8. performFly prints that the mallard duck does NOT fly
    mallard->performFly();


	return 0;
}