#include "DetectorConstruction.hh"

MyDetectorConstruction::MyDetectorConstruction() {
    // Define dimensions (half-lengths)
    xWorld = 200*um;
    yWorld = 300*um;
    zWorld = 200*um;

    xIce = 180*um;
    yIce = 180*um;
    zIce = 180*um;

    xTissue=80*um;
	yTissue=1*um;
	zTissue=80*um;

    xVoxel = 1*um; // it was xVoxel and i changet to Voxel but there no differant 

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

    // Ice block volume
    solidIce = new G4Box("solidIce", xIce, yIce, zIce);
    logicIce = new G4LogicalVolume(solidIce, iceMat, "logicIce");
    physIce = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicIce, "physIce", logicWorld, false, 0, true);


    G4int xN=xTissue/xVoxel;
	G4int yN=yTissue/xVoxel;
	G4int zN=zTissue/xVoxel;

    G4int xI=xIce/xVoxel;
	G4int yI=yIce/xVoxel;
	G4int zI=zIce/xVoxel;



	G4int voxelId=0;



    // Set user limits for the ice block
    G4UserLimits* userLimits = new G4UserLimits();
    userLimits->SetMaxAllowedStep(20*nm); // it is about the limet for each step 
    logicIce->SetUserLimits(userLimits);
    logicUperTissue->SetUserLimits(userLimits);
    logicUnderTissue->SetUserLimits(userLimits);
    logicIce->SetUserLimits(userLimits);




    return physWorld;
}
