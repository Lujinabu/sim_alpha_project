#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "RunAction.hh"

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4RunManager.hh"
#include "G4ToolsAnalysisManager.hh"
#include "G4AnalysisManager.hh"
#include "G4GenericMessenger.hh"
#include "G4UserLimits.hh"

class MyDetectorConstruction:public G4VUserDetectorConstruction{

	public:
		MyDetectorConstruction();
		~MyDetectorConstruction();

        virtual G4VPhysicalVolume *Construct();
		G4LogicalVolume* GetScoringVolume() const {return fScoringVolume;}
        G4double xWorld, yWorld, zWorld, xIce, yIce, zIce, xcell, ycell, zcell, xTissue, yTissue, zTissue, Voxel, margin;
    	G4Box *solidWorld, *solidIce, *solidUnderTissue, *solidUperTissue, *solidCellUnder, *solidCellUper;
		G4LogicalVolume *logicWorld, *logicIce, *logicUnderTissue, *logicUperTissue, *logicCellUnder, *logicCellUper, *fScoringVolume;
		G4VPhysicalVolume *physWorld, *physIce, *physUnderTissue, *physUperTissue, *physiCellUnder, *physiCellUper;
		G4Material *iceMat, *worldMat, *skinMat;


        void DefineMaterials();
	
};




#endif



// #ifndef DETECTOR_CONSTRUCTION_HH
// #define DETECTOR_CONSTRUCTION_HH

// #include "G4VUserDetectorConstruction.hh"
// #include "G4LogicalVolume.hh"
// #include "globals.hh"

// class DetectorConstruction : public G4VUserDetectorConstruction
// {
// public:
//     DetectorConstruction();
//     virtual ~DetectorConstruction();
    
//     virtual G4VPhysicalVolume* Construct();
// };

// #endif