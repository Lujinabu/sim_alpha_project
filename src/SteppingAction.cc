#include "SteppingAction.hh"
#include "G4LogicalVolume.hh"
#include "G4EventManager.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Alpha.hh"


MySteppingAction::MySteppingAction(MyEventAction* eventAction){

	fEventAction = eventAction;


}
MySteppingAction::~MySteppingAction(){}

 void MySteppingAction::UserSteppingAction(const G4Step *aStep){

    G4LogicalVolume* volume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    G4Track* track = aStep->GetTrack();
    G4ParticleDefinition* particleType = track->GetDefinition();
    G4int trackID = track->GetTrackID();

  


        if(volume->GetName()=="logicUperTissue"|| volume->GetName()=="logicUnderTissue"|| volume->GetName()=="logicIce"){     
            G4int eventID = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();//the number of  the beam0
            G4double dE = aStep->GetTotalEnergyDeposit();
            G4double prekineticEnergy = aStep->GetPreStepPoint()->GetKineticEnergy();
            G4double postkineticEnergy = aStep->GetPostStepPoint()->GetKineticEnergy();
            G4ThreeVector prePoint = aStep->GetPreStepPoint()->GetPosition();
	         G4ThreeVector postPoint = aStep->GetPostStepPoint()->GetPosition();
           G4ThreeVector particleMomDirection = aStep->GetPostStepPoint()->GetMomentumDirection();
           G4ThreeVector particleMomPreDirection = aStep->GetPreStepPoint()->GetMomentumDirection();
           G4double cosTheta = particleMomPreDirection.dot(particleMomDirection) / (particleMomPreDirection.mag() * particleMomDirection.mag());
           G4double angle = std::acos(cosTheta); // 
           G4double distence = (postPoint - prePoint).mag(); // Calculate travel distance
           G4double stepLength = aStep->GetStepLength();
            G4int stepID = aStep->GetTrack()->GetCurrentStepNumber();
            G4int parentID = aStep->GetTrack()->GetParentID();
            G4int particleID = -1;

            G4String particleName = aStep->GetTrack()->GetParticleDefinition()->GetParticleName();





             G4String parentParticleName = "unknown";
            G4int parentParticleID = -1;
           if (parentID > 0) {
            parentParticleName = fEventAction->GetParentTrackParticleName(aStep->GetTrack()->GetParentID());
                 if (parentParticleName == "Ra224") {
                 parentParticleID = 0;
                  //    G4cout << parentParticleName << " Ra224" << G4endl;

                 } else if (parentParticleName == "Rn220") {
                 parentParticleID = 5;
                   //    G4cout << parentParticleName << "Rn220" << G4endl;

                  } else if (parentParticleName == "Po216") {
                 parentParticleID = 6;
                 //    G4cout << parentParticleName << "Po216" << G4endl;

                 } else if (parentParticleName == "Pb212") {
                  parentParticleID = 7;
                  //    G4cout << parentParticleName << " Pb212" << G4endl;
   
                  } else if (parentParticleName == "Bi212") {
                   parentParticleID = 8;
                 //    G4cout << parentParticleName << "Bi212" << G4endl;

                 } else if (parentParticleName == "Tl208") {
                 parentParticleID = 9;
                  //    G4cout << parentParticleName << " Tl208" << G4endl;

                 } else if (parentParticleName == "Pb208") {
                 parentParticleID = 10;
                 //    G4cout << parentParticleName << "Pb208" << G4endl;

                 } else if (parentParticleName == "alpha") {
                 parentParticleID = 1;
                 //    G4cout << parentParticleName << "alpha" << G4endl;

                 } else if (parentParticleName == "gamma") {
                 parentParticleID = 2;
                 //    G4cout << parentParticleName << "gamma" << G4endl;

                 } else if (parentParticleName == "e-") {
                 parentParticleID = 3;
                 //    G4cout << parentParticleName << " e-" << G4endl;

                 } else if (parentParticleName == "nu_e") {
                  parentParticleID = 4;
                 //    G4cout << parentParticleName << " nu_e" << G4endl;

                 } else {
                   // G4cout << parentParticleName << " not in list " << G4endl;
                 }
              }

		      if(particleName == "nu_e"){//no need to track
                    return;
              }
            
            
            
                // if (particleName == "Rn220"){
                //     particleID = 1;
                //    G4cout << particleName << " Ra224" << G4endl;

                // }else{ 
                if (particleName == "alpha" || particleName == "helium" || particleName == "alpha+") {
                   particleID = 1;
                  //    G4cout << particleName << " alpha" << G4endl;

                   }  else if (particleName == "gamma") {
                   particleID = 2;
                  //    G4cout << particleName << " gamma" << G4endl;

                  }  else if (particleName == "e-") { 
                   particleID = 3;  
                  //    G4cout << particleName << " e-" << G4endl;

                  }  else if (particleName == "nu_e") {
                   particleID = 4;
                  //    G4cout << particleName << " nu_e" << G4endl;

                  } else if (particleName == "Ra224") { // Adding Ra224 to start the decay chain
                   particleID = 0; // Unique ID for Ra224
                  //    G4cout << particleName << " Ra224" << G4endl;

                  } else if (particleName == "Rn220") { // Assuming Rn220 for Radon-220
                   particleID = 5;
                  //    G4cout << particleName << " Rn220" << G4endl;

                  } else if (particleName == "Po216") { // Daughter nucleus of Rn220
                   particleID = 6;
                  //    G4cout << particleName << " Po216" << G4endl;

                  } else if (particleName == "Pb212") { // Daughter nucleus of Po216
                   particleID = 7;
                  //    G4cout << particleName << "Pb212" << G4endl;

                  } else if (particleName == "Bi212") { // Daughter nucleus of Pb212
                   particleID = 8;
                  //    G4cout << particleName << "Bi212" << G4endl;

                  } else if (particleName == "Tl208") { // Daughter nucleus of Bi212
                   particleID = 9;
                  //    G4cout << particleName << " Tl208" << G4endl;

                  } else if (particleName == "Pb208") { // Stable end product of the decay chain
                   particleID = 10;
                    //    G4cout << particleName << "Pb208" << G4endl;
                    } else {
                     // G4cout << particleName << " outside not saved" << G4endl;
                    return;
                   }

        //   G4cout << "Event: " << eventID << " Particle: " << particleName << " Parent: " << parentParticleName << G4endl;
	
		G4int tempID=aStep->GetTrack()->GetTrackID();
		//G4cout<<G4endl;
	
           	G4AnalysisManager *man=G4AnalysisManager::Instance();


        
	          man->FillNtupleIColumn(0, 0, eventID); //eventID is consistent with the BeamOn X number
	          man->FillNtupleDColumn(0, 1, prekineticEnergy/keV);//particle kinetic energy in a given step, in keV
	          man->FillNtupleDColumn(0, 2, postkineticEnergy/keV);//particle kinetic energy in a given step, in keV
	          man->FillNtupleIColumn(0, 3, particleID);//particle ID
	          man->FillNtupleIColumn(0, 4, stepID);//particle name
           	man->FillNtupleDColumn(0, 5, prePoint[0]/nm);//pre step point of the particle 
           	man->FillNtupleDColumn(0, 6, prePoint[1]/nm);
           	man->FillNtupleDColumn(0, 7, prePoint[2]/nm);
           	man->FillNtupleDColumn(0, 8, postPoint[0]/nm);//post step point of the particle
           	man->FillNtupleDColumn(0, 9, postPoint[1]/nm);
           	man->FillNtupleDColumn(0, 10, postPoint[2]/nm);
            man->FillNtupleIColumn(0, 11, parentParticleID); // travel distance of the particle
	          man->FillNtupleDColumn(0, 12, stepLength/nm);//step length in nm
            man->FillNtupleDColumn(0, 13, particleMomDirection[0]);//post momentum direction of the particle
	          man->FillNtupleDColumn(0, 14, particleMomDirection[1]);
	          man->FillNtupleDColumn(0, 15, particleMomDirection[2]);


            // // man->FillNtupleDColumn(0, 12, angle); // Angle between initial and final momentum directions
            man->AddNtupleRow(0);




        // }else if (volume->GetName() == "logicIce") {

        //     man->FillNtupleIColumn(2, 0, eventID);
        //     man->FillNtupleDColumn(2, 1, prekineticEnergy / keV);
        //     man->FillNtupleDColumn(2, 2, postkineticEnergy / keV);
        //     man->FillNtupleIColumn(2, 3, particleID);
        //     man->FillNtupleSColumn(2, 4, particleName);
        //     man->FillNtupleIColumn(2, 5, stepID);
        //     man->FillNtupleDColumn(2, 6, prePoint[0] / nm);
        //     man->FillNtupleDColumn(2, 7, prePoint[1] / nm);
        //     man->FillNtupleDColumn(2, 8, prePoint[2] / nm);
        //     man->FillNtupleDColumn(2, 9, postPoint[0] / nm);
        //     man->FillNtupleDColumn(2, 10, postPoint[1] / nm);
        //     man->FillNtupleDColumn(2, 11, postPoint[2] / nm);
        //     man->FillNtupleDColumn(2, 12, distence / nm);
        //     man->FillNtupleSColumn(2, 13, parentParticleName);
        //     man->FillNtupleDColumn(2, 14, angle);
        //     man->AddNtupleRow(2);



    }  
} 
