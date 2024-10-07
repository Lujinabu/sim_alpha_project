#include "../include/EventAction.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"

MyEventAction::MyEventAction(MyRunAction*){


}

MyEventAction::~MyEventAction(){}

void MyEventAction::BeginOfEventAction(const G4Event*){

}

void MyEventAction::EndOfEventAction(const G4Event*){
	// mapping_parentTrack.erase(mapping_parentTrack.begin(), mapping_parentTrack.end());
	// mapping_parentID.erase(mapping_parentID.begin(), mapping_parentID.end());
    mapping_parentTrack.clear();
    mapping_parentID.clear();

    G4AnalysisManager *man=G4AnalysisManager::Instance();

    const MyPrimaryGeneratorAction* generatorAction     = static_cast<const MyPrimaryGeneratorAction*>(
        G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
    G4GeneralParticleSource* particlegun;
    G4ThreeVector posIon;

        if (generatorAction){
            particlegun= generatorAction->GetParticleGun();
            posIon=particlegun->GetParticlePosition();

        }  
	
    int seed=0;
    if(particlegun){
        std::stringstream pos_idX;
        std::stringstream pos_idY;
        std::stringstream pos_idZ;
        pos_idX << posIon[0]*1000; 
        pos_idY << posIon[1]*1000; 
        pos_idZ << posIon[2]*1000;
		
	//G4cout<<"stepL: "<<G4BestUnit(posIon, "Length")<<" "<<posIon<<G4endl;
        // man->FillNtupleDColumn(1, 0, posIon[0]);
        // man->FillNtupleDColumn(1, 1, posIon[1]);
        // man->FillNtupleDColumn(1, 2, posIon[2]);
        // man->AddNtupleRow(1);
         }
  
    
}

void MyEventAction::UpdateMap(G4int trackID, G4String parentName, G4int parenttrackID){
	
	//  mapping_parentTrack.insert(std::pair<G4int, G4String> (trackID, parentName));
	//  mapping_parentID.insert(std::pair<G4int, G4int> (trackID, parenttrackID));

        if (G4StrUtil::contains(parentName, "[")) // to catch excited states
      {
        parentName = parentName.substr(0, 5);
      }
    mapping_parentTrack[trackID] = parentName;
    mapping_parentID[trackID] = parenttrackID;
}

G4String MyEventAction::GetParentTrackParticleName(G4int trackid){
 if (mapping_parentTrack.find(trackid) != mapping_parentTrack.end()) {
        return mapping_parentTrack[trackid];
	// return mapping_parentTrack[trackid];

   }
    return "unknown";
}
G4int MyEventAction::GetParentTrackID(G4int trackid){

   if (mapping_parentID.find(trackid) != mapping_parentID.end()) {
        return mapping_parentID[trackid];
    }
    return -1;
}
