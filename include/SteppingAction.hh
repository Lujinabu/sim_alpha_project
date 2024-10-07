#ifndef STEPPINGACTION_HH
#define STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "EventAction.hh"
#include <map>
#include <set>

class MySteppingAction : public G4UserSteppingAction {
public:
    MySteppingAction(MyEventAction* eventAction);
    virtual ~MySteppingAction();

    virtual void UserSteppingAction(const G4Step* step) override;

private:
    MyEventAction* fEventAction;

    std::map<G4int, G4ThreeVector> initialPositionMap;
    std::set<G4int> decayedParticles;
};

#endif
