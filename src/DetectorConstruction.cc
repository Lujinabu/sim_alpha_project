#include "DetectorConstruction.hh"

// using namespace std;
// using CLHEP::angstrom;
// using CLHEP::degree;
// using CLHEP::micrometer;
// using CLHEP::mm;
// using CLHEP::nanometer;


MyDetectorConstruction::MyDetectorConstruction() {
    // Define dimensions (half-lengths)
    xWorld = 800*um;
    yWorld = 800*um;
    zWorld = 800*um;

    xIce = 60*um;
    yIce = 40*um;
    zIce = 60*um;

    xTissue=120*um;
	yTissue=120*um;
	zTissue=120*um;

    xcell=120*um;
    ycell=0.15*um;
    zcell=120*um;

    Voxel = 0.15*um; 
    margin = 0*nm;
    // Voxel = 1*um;  




//   fDetectorMessenger = new DetectorMessenger(this);


    DefineMaterials();
}

MyDetectorConstruction::~MyDetectorConstruction() {}

void MyDetectorConstruction::DefineMaterials() {
    // Get materials from NIST database
    G4NistManager* nist = G4NistManager::Instance();

    worldMat = nist->FindOrBuildMaterial("G4_AIR");
    iceMat = nist->FindOrBuildMaterial("G4_WATER");  // Ice is modeled as water
    // iceMat = new G4Material("Ice", 0.92 * g/cm3, 2);
    // iceMat->AddElement(nist->FindOrBuildElement("H"), 2);
    // iceMat->AddElement(nist->FindOrBuildElement("O"), 1);
    
    skinMat = nist->FindOrBuildMaterial("G4_WATER");

}

G4VPhysicalVolume* MyDetectorConstruction::Construct() {
    // World volume
    solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);
    logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    physWorld = new G4PVPlacement(0, G4ThreeVector(0,0,0), logicWorld, "physWorld", 0, false, 0, true);

    

    solidUperTissue = new G4Box("solidUperTissue", xTissue, yTissue, zTissue);
    logicUperTissue = new G4LogicalVolume(solidUperTissue, skinMat, "logicUperTissue");
    physUperTissue = new G4PVPlacement(0, G4ThreeVector(0,yTissue+yIce, 0), logicUperTissue, "physUperTissue", logicWorld, false, 0, true);


    solidUnderTissue = new G4Box("solidUnderTissue", xTissue, yTissue, zTissue);
    logicUnderTissue = new G4LogicalVolume(solidUnderTissue, skinMat, "logicUnderTissue");
    physUnderTissue = new G4PVPlacement(0, G4ThreeVector(0, -yIce-yTissue, 0), logicUnderTissue, "physUnderTissue", logicWorld, false, 0, 1);
    //this mean the center of the physUnderTissue will be (0,-90,0)for the world , but when I mad the logicUnderTissue a mother for a valum 
    //the center for it will be 0,0,0 then i can desaedie what the center of the new value acording to the logicUnderTissue.  
    G4cout << "yIce-yTissue " << yIce-yTissue << G4endl; // Debugging output
    // Ice block volume
    solidIce = new G4Box("solidIce", xIce, yIce, zIce);
    logicIce = new G4LogicalVolume(solidIce, iceMat, "logicIce");
    physIce = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicIce, "physIce", logicWorld, false, 0, true);

    // Set user limits for the ice block

     G4double maxStep = 0.01*Voxel;
     auto fStepLimit = new G4UserLimits(maxStep);// it will be 3nm for each step 
  
    solidCellUnder = new G4Box("solidCellUnder", xcell, ycell, zcell);
    logicCellUnder = new G4LogicalVolume(solidCellUnder, skinMat, "logicCellUnder");

    // Place the under cells
    for (G4int i = 0; i < 25; ++i) {
        G4double yOffset = -(i + 1) * 5 * um + yTissue;  // Adjust offset to place within Under Tissue
        physiCellUnder = new G4PVPlacement(0, G4ThreeVector(0, yOffset, 0), logicCellUnder, "physiCellUnder", logicUnderTissue, false, i+1, true);
        G4cout << "copy = " << i+1 <<" offset = " <<yOffset << G4endl; 

    }

    // Upper cells
    solidCellUper = new G4Box("solidCellUper", xcell, ycell, zcell);
    logicCellUper = new G4LogicalVolume(solidCellUper, skinMat, "logicCellUper");

   for (G4int i = 0; i < 25; ++i) {
    G4double yOffset = (i + 1) * 5 * um - yTissue;  // Adjust offset to place within Uper Tissue
    physiCellUper = new G4PVPlacement(0, G4ThreeVector(0, yOffset, 0), logicCellUper, "physiCellUper", logicUperTissue, false, i+100, true);
    G4cout << "copy = " << i+100 <<" offset = " <<yOffset << G4endl; 
    }


    G4int xN=xTissue/Voxel;
	G4int yN=yTissue/Voxel;
	G4int zN=zTissue/Voxel;

    G4int xI=xIce/Voxel;
	G4int yI=yIce/Voxel;
	G4int zI=zIce/Voxel;





	G4int voxelId=0;

    

    // G4UserLimits* userLimits = new G4UserLimits();
    // userLimits->SetMaxAllowedStep(20*nm); // it is about the limet for each step 
    // logicIce->SetUserLimits(userLimits);
    // logicUperTissue->SetUserLimits(userLimits);
    // logicUnderTissue->SetUserLimits(userLimits);
    // logicIce->SetUserLimits(userLimits);




    return physWorld;
}
