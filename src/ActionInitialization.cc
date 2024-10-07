#include "../include/ActionInitialization.hh"
#include "../include/PrimaryGeneratorAction.hh"
#include "../include/RunAction.hh"
#include "../include/EventAction.hh"
#include "../include/SteppingAction.hh"
#include "../include/StackingAction.hh"






MyActionInitialization::MyActionInitialization(){}
MyActionInitialization::~MyActionInitialization(){}

void MyActionInitialization::Build() const{

      MyPrimaryGeneratorAction *generator = new MyPrimaryGeneratorAction ();
     SetUserAction(generator);

     MyRunAction *runAction = new MyRunAction();
	SetUserAction(runAction);

	MyEventAction *eventAction=new MyEventAction(runAction);
	SetUserAction(eventAction);

	MySteppingAction *steppingAction=new MySteppingAction(eventAction);
	SetUserAction(steppingAction);
	
	MyStackingAction *stackingAction=new MyStackingAction();
	SetUserAction(stackingAction);




}
void MyActionInitialization::BuildForMaster() const{
 
     MyRunAction *runAction = new MyRunAction();
     SetUserAction(runAction);
}