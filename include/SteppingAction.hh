#ifndef STEPPINGACTION_HH
#define STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "EventAction.hh"
#include <map>
#include <set>
#include "G4Track.hh"

class MySteppingAction : public G4UserSteppingAction {
public:
    MySteppingAction(MyEventAction* eventAction);
    virtual ~MySteppingAction();

    virtual void UserSteppingAction(const G4Step* step) override;

// private:
    MyEventAction* fEventAction;

  std::ofstream PSfile18Dec;
  void savePoint(const G4Track *track, const G4ThreeVector & newPos, const G4ThreeVector & boxMomentum, const G4int & copy, const G4double & particleEnergy, const G4double & time, const G4int & originParticle);
  G4ThreeVector transformDirection(const G4ThreeVector & position, const G4ThreeVector & worldMomentum);
  MyDetectorConstruction *fDetector;
  G4double calculateDistanceToExitBox(const G4ThreeVector & preStepPosition, const G4ThreeVector & preStepMomentumDirection);

    std::map<G4int, G4ThreeVector> initialPositionMap;
    std::set<G4int> decayedParticles;

      std::map<G4String, G4int> particleMap{
      {"e-", 1},
      {"gamma", 2},
      {"alpha", 3},
      {"Rn220", 4},
      {"Po216", 5},
      {"Pb212", 6},
      {"Bi212", 7},
      {"Tl208", 8},
      {"Po212", 9},
      {"Pb208", 10},
      {"e+", 11},

      {"At211", 12},
      {"Po211", 13},
      {"Bi207", 14},
      {"Pb207", 15},


      };

  std::map<G4String, G4int> particleOriginMap{
      {"Ra224", 1},
      {"Rn220", 2},
      {"Po216", 3},
      {"Pb212", 4},
      {"Bi212", 5},
      {"Tl208", 6},
      {"Po212", 7},
      {"Pb208", 8},
      {"alphaRa224", 9},
      {"alphaRn220", 10},
      {"alphaPo216", 11},
      {"alphaBi212", 12},
      {"alphaPo212", 13},
      {"e-Rn220", 14},
      {"e-Po216", 15},
      {"e-Pb212", 16},
      {"e-Bi212", 17},
      {"e-Tl208", 18},
      {"e-Po212", 19},
      {"e-Pb208", 20},
      {"gammaRn220", 21},
      {"gammaPo216", 22},
      {"gammaPb212", 23},
      {"gammaBi212", 24},
      {"gammaTl208", 25},
      {"gammaPo212", 26},
      {"gammaPb208", 27},
      {"e+", 28},

      {"At211", 29},
      {"Po211", 30},
      {"Bi207", 31},
      {"Pb207", 32},
      {"alphaAt211", 33},
      {"alphaPo211", 34},
      {"e-At211", 35},
      {"e-Po211", 36},
      {"e-Bi207", 37},
      {"e-Pb207", 38},

      {"gammaAt211", 39},
      {"gammaPo211", 40},
      {"gammaBi207", 41},
      {"gammaPb207", 42},
      





      
      };

  std::map<G4int, G4String> reverseParticleOriginMap{
      {1, "Ra224"},
      {2, "Rn220"},
      {3, "Po216"},
      {4, "Pb212"},
      {5, "Bi212"},
      {6, "Tl208"},
      {7, "Po212"},
      {8, "Pb208"},


      {29, "At211"},
      {30, "Po211"},
      {31, "Bi207"},
      {32, "Pb207"},


  };
};

#endif
