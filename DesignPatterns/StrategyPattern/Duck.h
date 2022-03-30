#pragma once

class FlyBehavior {
public:
    virtual void fly() = 0;
};

class TenSecFly :public FlyBehavior {
private:

public:
    TenSecFly() {};
    ~TenSecFly() {};

    void fly();
};

class CanNotFly :public FlyBehavior {
private:

public:
    CanNotFly() {};
    ~CanNotFly() {};

    void fly();
};

class DuckClass {

protected: // Can Used Only in its subclasses

    FlyBehavior *flyBehavior = 0;
    // QuackBehavior* quackBehavior;  // Not used in this example;

public:
    DuckClass() {};
    ~DuckClass() {};

    void performFly();
    
    // void performQuack();  // Not used in this example;

    void setFlyBehavior(FlyBehavior *uFlyBehavior);

    //setQuackBehavior(QuackBehavior* uQuackBehavior);  // Not used in this example;
};



class MallardDuckClass : public DuckClass {

private:

public:

    MallardDuckClass() {
        //1. Create instances of the desired behaviors
        flyBehavior = new TenSecFly();

    };

    ~MallardDuckClass() {};

};