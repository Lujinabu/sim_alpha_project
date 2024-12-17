#ifndef EVENTACTION_HH
#define EVENTACTION_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"
#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include <G4UnitsTable.hh>
class MyEventAction : public G4UserEventAction{

	public:
		MyEventAction(MyRunAction*);
		~MyEventAction();

		// virtual void UpdateMap(G4int trackid, G4String parentName, G4int parenttrackID);
		// virtual G4String GetParentTrackParticleName(G4int trackid);
		// virtual G4int GetParentTrackID(G4int trackid);
		virtual void BeginOfEventAction(const G4Event*);
		virtual void EndOfEventAction(const G4Event*);
		// void addRnDesorptionIN() { RnDesorptionIN++; }
        // G4int getRnDesorptionIN() { return RnDesorptionIN; }

		std::map<G4int, G4ThreeVector> particlePos;
        std::map<G4int, G4ThreeVector> particleDist;
        std::map<G4int, G4ThreeVector> decayPos;
        std::map<G4int, G4int> parentParticle; //map to parent particle from radioactive decay
        std::vector<G4int> tracks;
	
	// private:

    		// std::map<G4int, G4String> mapping_parentTrack;//track id, parent name
    		// std::map<G4int, G4int> mapping_parentID;//track id, parent track id


};




#endif




