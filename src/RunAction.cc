#include "../include/RunAction.hh"
#include "G4ios.hh"
#include "../include/DetectorConstruction.hh"
#include "../include/EventAction.hh"

MyRunAction::MyRunAction() {}
MyRunAction::~MyRunAction() {}

void MyRunAction::BeginOfRunAction(const G4Run*) {
    G4AnalysisManager *man = G4AnalysisManager::Instance();

  
   man->OpenFile("26sepwithoutDFIceisWater.root");  

    // Create Ntuple for "UperTissue"
    man->CreateNtuple("Uper&underTissue", "Depth");
    man->CreateNtupleIColumn("Event");//1
    man->CreateNtupleDColumn("prekineticEnergy");
    man->CreateNtupleDColumn("postkineticEnergy");//2
    man->CreateNtupleIColumn("particleID");//3
    man->CreateNtupleSColumn("particleName");//4
    man->CreateNtupleIColumn("stepID");//5
    man->CreateNtupleDColumn("prePoint_x_nm");//6  // Corrected column names
    man->CreateNtupleDColumn("prePoint_y_nm");//7
    man->CreateNtupleDColumn("prePoint_z_nm");//8
    man->CreateNtupleDColumn("postPoint_x_nm");//9
    man->CreateNtupleDColumn("postPoint_y_nm");//10
    man->CreateNtupleDColumn("postPoint_z_nm");//11
    man->CreateNtupleIColumn("parentParticleID");//12
    man->CreateNtupleSColumn("parentparticleName");//13
    man->CreateNtupleDColumn("Angle");//14
    man->CreateNtupleDColumn("eDep_eV");
	man->CreateNtupleDColumn(0, 16, stepLength/nm);//step length in nm
    man->CreateNtupleDColumn(0, 17, particleMomDirection[0]);//post momentum direction of the particle
	man->CreateNtupleDColumn(0, 18, particleMomDirection[1]);
	man->CreateNtupleDColumn(0, 19, particleMomDirection[2]);


    man->FinishNtuple(0);

    // // Create Ntuple for "UnderTissue"
    // man->CreateNtuple("Ice", "Depth");
    // man->CreateNtupleIColumn("Event_No");
    // man->CreateNtupleDColumn("prekineticEnergy");
    // man->CreateNtupleDColumn("postkineticEnergy");
    // man->CreateNtupleIColumn("particleID");
    // man->CreateNtupleSColumn("particleName");
    // man->CreateNtupleIColumn("stepID");
    // man->CreateNtupleDColumn("prePoint_x_nm");  // Corrected column names
    // man->CreateNtupleDColumn("prePoint_y_nm");
    // man->CreateNtupleDColumn("prePoint_z_nm");
    // man->CreateNtupleDColumn("postPoint_x_nm");
    // man->CreateNtupleDColumn("postPoint_y_nm");
    // man->CreateNtupleDColumn("postPoint_z_nm");
    // man->CreateNtupleDColumn("distence_nm");
    // man->CreateNtupleSColumn("parentparticleName");
    // man->CreateNtupleDColumn("Angle");


    // man->FinishNtuple(1);

 
      // Your existing code for particle gun and position (optional)
       const MyPrimaryGeneratorAction* generatorAction = static_cast<const MyPrimaryGeneratorAction*>(
        G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
    G4GeneralParticleSource* particlegun;
    G4ThreeVector posIon;

       if (generatorAction) {
        particlegun = generatorAction->GetParticleGun();
        posIon = particlegun->GetParticlePosition();
        }
}

void MyRunAction::EndOfRunAction(const G4Run*) {
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    const auto detConstruction = static_cast<const MyDetectorConstruction*>(
    G4RunManager::GetRunManager()->GetUserDetectorConstruction());

    // Write and close file
    man->Write();
    man->CloseFile();
}
