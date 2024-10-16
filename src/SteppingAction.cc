#include "SteppingAction.hh"
#include "G4LogicalVolume.hh"
#include "G4EventManager.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Alpha.hh"
// #include "CommandLineParser.hh"





MySteppingAction::MySteppingAction(MyEventAction* eventAction){

	fEventAction = eventAction;
  G4String fileName{"PSfile.bin"};

  PSfile.open(fileName, std::ios::out | std::ios::binary); 


}
MySteppingAction::~MySteppingAction(){ PSfile.close();}

 void MySteppingAction::UserSteppingAction(const G4Step *step){
    G4String volume = step->GetPreStepPoint()->GetPhysicalVolume()->GetName();
    G4Track* track = step->GetTrack();
    G4String particleName = step->GetTrack()->GetParticleDefinition()->GetParticleName();
    // G4cout << particleName << G4endl;

    G4ParticleDefinition* particleType = track->GetDefinition();
    G4int TrackID = step->GetTrack()->GetTrackID();
  if ((fEventAction->parentParticle.find(TrackID) == fEventAction->parentParticle.end()) && (step->GetTrack()->GetCreatorProcess() != nullptr))
  {
    // track ID not found, save to map, trackID: creator particle from decay (e-,alpha, gamma) for split of DNA damage by source
    if (step->GetTrack()->GetCreatorProcess()->GetProcessName() == "RadioactiveDecay")
    {
      if (G4StrUtil::contains(particleName, "[")) // to catch excited states
      {
        fEventAction->parentParticle.insert(std::pair<G4int, G4int>(TrackID, particleOriginMap[particleName.substr(0, 5)]));
      }
      else if ((particleName == "e-") || (particleName == "gamma") || (particleName == "alpha") || (particleName == "e+")) // save product and parent names
      {
        G4String parentName = reverseParticleOriginMap[fEventAction->parentParticle[step->GetTrack()->GetParentID()]];
        G4String combinedName = particleName + parentName;

        fEventAction->parentParticle.insert(std::pair<G4int, G4int>(TrackID, particleOriginMap[combinedName]));
      }
      else
      {
        fEventAction->parentParticle.insert(std::pair<G4int, G4int>(TrackID, particleOriginMap[particleName]));
      }
    }
    else
    {
      // not radioactive decay so another process so parent ID should be in mapping
      G4int parentParticle = fEventAction->parentParticle[step->GetTrack()->GetParentID()];
      // add current track with parent particle
      fEventAction->parentParticle.insert(std::pair<G4int, G4int>(TrackID, parentParticle));
    }
  }

  // Retrieve the copy number from the volume
  G4int copyNo = step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();  // This is the copy number

  // Save phase space file in the DNA box reference frame. Particle entry position into the box is saved to the phase space file, and the distance travelled from this point in the DNA box reference frame tracked until a boundary is crossed. Particles are saved to the phase space file in the adjacent box.

  if ((volume =="physUnderTissue"|| volume=="physUperTissue") && (
  (step->GetPostStepPoint()->GetPhysicalVolume()->GetName() == "physiCellUnder") ||
  (step->GetPostStepPoint()->GetPhysicalVolume()->GetName() == "physiCellUper"))&& 
  (step->GetPreStepPoint()->GetKineticEnergy() > 0)) // the step is going from the water into the cell. save all steps entering rings  
  {
    G4ThreeVector worldPos = step->GetPostStepPoint()->GetPosition();
    G4double newX = (G4UniformRand() * .00015 * 2) - .00015;
    G4double newZ = (G4UniformRand() * .00015 * 2) - .00015;

    // G4double Cell = std::pow(worldPos.x() * worldPos.x() + worldPos.y() * worldPos.y(), 0.5);
  //  G4cout<<"here"<<G4endl;
    G4int copyNo = step->GetPostStepPoint()->GetPhysicalVolume()->GetCopyNo();
    G4double newY;
  //  G4cout<<copyNo<<G4endl;

    if (volume == "physUnderTissue") {
    newY = (copyNo * 5 * um) - 0.3*um; // for cells under
    } else if (volume == "physUperTissue") {
    newY = -(copyNo * 5 * um) + 0.3*um; // for cells above
    }
    else
    {
      G4cout << "shouldnt be here" << volume << G4endl;
    }


    // pick position in box frame
    G4ThreeVector newPos = G4ThreeVector(newX, newY, newZ);
  //  G4cout<<newPos<<G4endl;

    savePoint(step->GetTrack(), newPos, step->GetPostStepPoint()->GetMomentumDirection(), step->GetPostStepPoint()->GetPhysicalVolume()->GetCopyNo(), step->GetPostStepPoint()->GetKineticEnergy(), step->GetPostStepPoint()->GetGlobalTime(), fEventAction->parentParticle[TrackID]);
  }
  else if ((volume == "physiCellUnder"||volume == "physiCellUper") && (step->IsFirstStepInVolume()) && (particleName != "gamma") && (step->GetPreStepPoint()->GetProcessDefinedStep() == nullptr)) // save particles created in the cell or nucleus. If from radioactive decay as not simulated in RBE. Secondary particles are not saved as these are simulated in RBE, but secondaries leaving the DNA box and entering the adjacent box are saved in the phase space file. if prestep process is nullptr this is the first step of particle created by interaction in the cell - only save those created by processes in cell not in other volumes
  {
    if ((step->GetTrack()->GetCreatorProcess()->GetProcessName() == "RadioactiveDecay") && (((const G4Ions *)(step->GetTrack()->GetParticleDefinition()))->GetExcitationEnergy() < 1e-15))
    {
      // only save products of radioactive decay other products are from parents which are saved on entering the cell and will be tracked in DNA simulation. Excited states are not saved as de-excitation is not simulated in RBE, products are saved to phase space file.

      G4int parentID = step->GetTrack()->GetParentID();

      G4ThreeVector worldPos = step->GetPreStepPoint()->GetPosition();

      // decay products should start in the same place in box reference frame, check if is first product
      if (fEventAction->decayPos.find(parentID) == fEventAction->decayPos.end())
      {
        // parent ID not found, is first product, pick new position and save
        G4double newX = (G4UniformRand() * .00015 * 2) - .00015;
        G4double newZ = (G4UniformRand() * .00015 * 2) - .00015;

        G4double Cell = std::pow(worldPos.x() * worldPos.x() + worldPos.y() * worldPos.y(), 0.5);
        G4ThreeVector newPos = G4ThreeVector();
       if (volume == "physiCellUnder") {

       G4double newY = (copyNo * 5 * um) - 0.3*um; // for cells under
        newPos = G4ThreeVector(newX, newY, newZ);
        // G4cout <<newX<< G4endl;//There is error here that all the newy not here 


       } else if (volume == "physiCellUper") {
       G4double newY = -(copyNo * 5 * um) + 0.3*um; // for cells above
        newPos = G4ThreeVector(newX, newY, newZ);
        // G4cout <<"newYfor the under"<<newY<< G4endl;//There is error here that all the newy will be same

       }
       else{
        G4cout << "There an somthing wrong"<< G4endl;

       }
        // pick position in box frame
        // G4ThreeVector newPos = G4ThreeVector(newX, newY, newZ);

        // save
        fEventAction->decayPos.insert(std::pair<int, G4ThreeVector>(parentID, newPos));

        G4ThreeVector newMomentum = step->GetPostStepPoint()->GetMomentumDirection();(worldPos, step->GetPreStepPoint()->GetMomentumDirection());

        savePoint(step->GetTrack(), newPos, newMomentum, step->GetPreStepPoint()->GetPhysicalVolume()->GetCopyNo(), step->GetPreStepPoint()->GetKineticEnergy(), step->GetPreStepPoint()->GetGlobalTime(), fEventAction->parentParticle[TrackID]);
      }
      else
      {
        // parent ID found, look up new position
        G4ThreeVector newPos = fEventAction->decayPos[parentID];

        G4ThreeVector newMomentum = step->GetPostStepPoint()->GetMomentumDirection();(worldPos, step->GetPreStepPoint()->GetMomentumDirection());

        savePoint(step->GetTrack(), newPos, newMomentum, step->GetPreStepPoint()->GetPhysicalVolume()->GetCopyNo(), step->GetPreStepPoint()->GetKineticEnergy(), step->GetPreStepPoint()->GetGlobalTime(), fEventAction->parentParticle[TrackID]);
      }
    }
    else
    {
      // track secondaries created in a box so they enter the adjacent box.
      G4int parentID = step->GetTrack()->GetParentID();

      G4ThreeVector worldPos = step->GetPreStepPoint()->GetPosition();

      // random position for secondary in original box, will not be added to phase space file until adjacent box, where DNA is not continuous.

      G4double newX = (G4UniformRand() * .00015 * 2) - .00015;
      G4double newZ = (G4UniformRand() * .00015 * 2) - .00015;

      G4double Cell = std::pow(worldPos.x() * worldPos.x() + worldPos.y() * worldPos.y(), 0.5);
      G4ThreeVector newPos = G4ThreeVector();
      if (volume == "physiCellUnder") {
       G4double newY = (copyNo * 5 * um) - 0.3*um; // for cells under
       newPos = G4ThreeVector(newX, newY, newZ);
        // G4cout <<"newYfor the under"<<newY<< G4endl;//There is error here that all the newy will be same 

        // G4cout <<"newYfor the under"<< newY<< G4endl;//There is error here that all the newy will be same 

      } else if (volume == "physiCellUper") {
        G4double newY = -(copyNo * 5 * um) + 0.3*um; // for cells above
        newPos = G4ThreeVector(newX, newY, newZ);
        // G4cout <<"newYfor the uper" << newY << G4endl;//There is an error here that there nothing in newy 

      }
      else{


      }



      // save creation position and distance travelled
      fEventAction->particlePos.erase(step->GetTrack()->GetTrackID()); // erase current saved box entry position for this track

      fEventAction->particlePos.insert(std::pair<int, G4ThreeVector>(step->GetTrack()->GetTrackID(), newPos)); // add current box entry position for this track

      fEventAction->particleDist.erase(step->GetTrack()->GetTrackID()); // erase distance travelled for this track in the box
      fEventAction->particleDist.insert(std::pair<int, G4ThreeVector>(step->GetTrack()->GetTrackID(), G4ThreeVector())); // made initial distance travelled zero

      fEventAction->tracks.push_back(step->GetTrack()->GetTrackID()); // add to tracks which are followed for box crossing
    }
  }
  else if ((volume == "physiCellUnder"||volume == "physiCellUper") && ((std::find(fEventAction->tracks.begin(), fEventAction->tracks.end(), TrackID) != fEventAction->tracks.end())) && (particleName != "gamma") && (step->GetPreStepPoint()->GetKineticEnergy() > 0)) // is a step in the cell but not first and it is a track which has previously been saved i.e. not a secondary created in the box, check if crosses virtual box boundary, if it does it is saved as if entering the box from the side faces.
  {
    G4ThreeVector entryPosition = fEventAction->particlePos[step->GetTrack()->GetTrackID()]; // look up position in box frame from last step

    G4ThreeVector deltaWorld = step->GetPostStepPoint()->GetPosition() - step->GetPreStepPoint()->GetPosition(); // change in position in world frame
    G4ThreeVector boxMomentumPre = step->GetPostStepPoint()->GetMomentumDirection();(step->GetPreStepPoint()->GetPosition(), step->GetPreStepPoint()->GetMomentumDirection()); // particle momentum in box frame

    G4ThreeVector delta = deltaWorld.mag() * boxMomentumPre; // change in position in box frame

    G4ThreeVector postStepBox = entryPosition + (fEventAction->particleDist)[step->GetTrack()->GetTrackID()] + delta;              // post step position in box frame
    if ((std::abs(postStepBox.x()) >= 0.00015) || (std::abs(postStepBox.y()) >= 0.00015) || (std::abs(postStepBox.z()) >= 0.00015)) // if >=0.00015 has crossed the boundary
    {
      // save particle, new position and distance saved
      G4ThreeVector preStepBox = entryPosition + (fEventAction->particleDist)[step->GetTrack()->GetTrackID()]; // pre step point position in box frame

      if (std::abs(preStepBox.y()) >= 0.00015)
      {
        // Particles which scatter back into the box are not added to the phase space file as scattering is included in the DNA simulation
        return;
      }

      G4double distanceToExit = calculateDistanceToExitBox(preStepBox, boxMomentumPre);

      if (distanceToExit == DBL_MAX)
      // exit y
      // update start position to y exit point and zero distance travelled, in case scattering changes direction
      {
        G4double tYneg = (-.00015 - preStepBox.y()) / boxMomentumPre.y();
        G4double tYpos = (.00015 - preStepBox.y()) / boxMomentumPre.y();
        tYneg = tYneg > 1e-15 ? tYneg : DBL_MAX;
        tYpos = tYpos > 1e-15 ? tYpos : DBL_MAX;

        G4double distanceToExit = std::min({tYpos, tYneg}); // shortest distance travelled to cross y box surface

        G4ThreeVector newPos = preStepBox + (distanceToExit * boxMomentumPre);

        fEventAction->particleDist.erase(step->GetTrack()->GetTrackID());
        fEventAction->particleDist.insert(std::pair<int, G4ThreeVector>()); // travelled (0,0,0) from the new starting position

        fEventAction->particlePos.erase(step->GetTrack()->GetTrackID()); // erase current saved box entry position for this track
        fEventAction->particlePos.insert(std::pair<int, G4ThreeVector>(step->GetTrack()->GetTrackID(), newPos));

        return;
      }
      else // crosses x or z
      {
        G4double stepDistance = step->GetStepLength();

        G4ThreeVector newPos = preStepBox + (distanceToExit * boxMomentumPre);

        // check which side of the box was crossed and change sign as particle is entering adjacent box
        if ((newPos.x() > 0) && (std::abs(newPos.x() - 0.00015) < 1e-15))
          newPos.setX(-0.00015);
        else if ((newPos.x() < 0) && (std::abs(newPos.x() + 0.00015) < 1e-15))
          newPos.setX(+0.00015);

        else if ((newPos.z() > 0) && (std::abs(newPos.z() - 0.00015) < 1e-15))
          newPos.setZ(-0.00015);
        else if ((newPos.z() < 0) && (std::abs(newPos.z() + 0.00015) < 1e-15))
          newPos.setZ(+0.00015);

        G4double percentageOfStep = distanceToExit / stepDistance;

        // calculate KE at point where crossing occurs
        G4double newKE = step->GetPreStepPoint()->GetKineticEnergy() - (step->GetPreStepPoint()->GetKineticEnergy() - step->GetPostStepPoint()->GetKineticEnergy()) * percentageOfStep;

        // calculate time at point where crossing occurs
        G4double newTime = step->GetPreStepPoint()->GetGlobalTime() + (step->GetDeltaTime() * percentageOfStep);

        savePoint(step->GetTrack(), newPos, boxMomentumPre, step->GetPreStepPoint()->GetPhysicalVolume()->GetCopyNo(), newKE, newTime, fEventAction->parentParticle[TrackID]);

        G4double percentageAccountedFor = percentageOfStep;

        while (percentageAccountedFor < 1)
        {
          G4ThreeVector restOfStep = newPos + (stepDistance - distanceToExit) * boxMomentumPre;

          if ((std::abs(restOfStep.x()) < 0.00015) && (std::abs(restOfStep.y()) < 0.00015) && (std::abs(restOfStep.z()) < 0.00015))
          {
            // remainder of step is contained in the adjacent box
            // save remainder of track travel to next box
            fEventAction->particleDist.erase(step->GetTrack()->GetTrackID());
            fEventAction->particleDist.insert(std::pair<int, G4ThreeVector>(step->GetTrack()->GetTrackID(), G4ThreeVector()));

            fEventAction->particlePos.erase(step->GetTrack()->GetTrackID()); // erase current saved box entry position for this track

            fEventAction->particlePos.insert(std::pair<int, G4ThreeVector>(step->GetTrack()->GetTrackID(), newPos + (stepDistance - distanceToExit) * boxMomentumPre)); // add current box entry position for this track
            percentageAccountedFor = 1;
          }
          else
          {
            // crosses another boundary
            // find which boundary
            G4double distanceToExitRemainder = calculateDistanceToExitBox(newPos, boxMomentumPre);

            if (distanceToExitRemainder == DBL_MAX) // exit y
            // update start position to y exit point and zero distance travelled, in case scattering changes direction
            {
              G4double tYneg = (-.00015 - preStepBox.y()) / boxMomentumPre.y();
              G4double tYpos = (.00015 - preStepBox.y()) / boxMomentumPre.y();
              tYneg = tYneg > 1e-15 ? tYneg : DBL_MAX;
              tYpos = tYpos > 1e-15 ? tYpos : DBL_MAX;

              G4double distanceToExit = std::min({tYpos, tYneg}); // shortest distance travelled to cross y box surface

              G4ThreeVector newPos = preStepBox + (distanceToExit * boxMomentumPre);

              fEventAction->particleDist.erase(step->GetTrack()->GetTrackID());
              fEventAction->particleDist.insert(std::pair<int, G4ThreeVector>()); // travelled (0,0,0) from the new starting position

              fEventAction->particlePos.erase(step->GetTrack()->GetTrackID()); // erase current saved box entry position for this track
              fEventAction->particlePos.insert(std::pair<int, G4ThreeVector>(step->GetTrack()->GetTrackID(), newPos));

              percentageAccountedFor = 1;

              return;
            }

            newPos += (distanceToExitRemainder * boxMomentumPre);

            // check which side of the box was crossed and change sign as particle is entering adjacent box
            if ((newPos.x() > 0) && (std::abs(newPos.x() - 0.00015) < 1e-15))
              newPos.setX(-0.00015);
            else if ((newPos.x() < 0) && (std::abs(newPos.x() + 0.00015) < 1e-15))
              newPos.setX(+0.00015);

            else if ((newPos.z() > 0) && (std::abs(newPos.z() - 0.00015) < 1e-15))
              newPos.setZ(-0.00015);
            else if ((newPos.z() < 0) && (std::abs(newPos.z() + 0.00015) < 1e-15))
              newPos.setZ(+0.00015);

            percentageOfStep = distanceToExitRemainder / stepDistance;

            newKE = newKE - (newKE - step->GetPostStepPoint()->GetKineticEnergy()) * percentageOfStep;

            newTime += (step->GetDeltaTime() * percentageOfStep);
            distanceToExit += distanceToExitRemainder;

            savePoint(step->GetTrack(), newPos, boxMomentumPre, step->GetPreStepPoint()->GetPhysicalVolume()->GetCopyNo(), newKE, newTime, fEventAction->parentParticle[TrackID]);

            percentageAccountedFor += percentageOfStep;
          }
        }
      }
    }

    else
    {
      //  if position hasn't crossed the box bounday update distance travelled in box
      G4ThreeVector previousDelta = (fEventAction->particleDist)[step->GetTrack()->GetTrackID()];

      fEventAction->particleDist.erase(step->GetTrack()->GetTrackID());
      fEventAction->particleDist.insert(std::pair<int, G4ThreeVector>(step->GetTrack()->GetTrackID(), previousDelta + delta));
    }
  }
        
		G4int tempID=step->GetTrack()->GetTrackID();
          
    }  
   void MySteppingAction::savePoint(const G4Track *track, const G4ThreeVector &newPos, const G4ThreeVector &boxMomentum, const G4int &copy, const G4double &particleEnergy, const G4double &time, const G4int &originParticle)
  { // save particle to phase space file in box reference frame
   fEventAction->particlePos.erase(track->GetTrackID()); // erase current saved box entry position for this track

  fEventAction->particlePos.insert(std::pair<int, G4ThreeVector>(track->GetTrackID(), newPos)); // add current box entry position for this track

  fEventAction->particleDist.erase(track->GetTrackID()); // erase distance travelled for this track in the box
  fEventAction->particleDist.insert(std::pair<int, G4ThreeVector>(track->GetTrackID(), G4ThreeVector())); // made initial distance travelled zero

  G4int eventID = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();

  G4String particleName = track->GetParticleDefinition()->GetParticleName();

  G4float particleID = particleMap[particleName];
  if (particleID == 0)
    {
    // G4cout << particleName << "  not saved" << G4endl;
    return;
    }

  double output[12];
  output[0] = newPos.x() / mm;
  output[1] = newPos.y() / mm;
  output[2] = newPos.z() / mm;
  output[3] = boxMomentum.x();
  output[4] = boxMomentum.y();
  output[5] = boxMomentum.z();
  output[6] = particleEnergy / MeV;
  output[7] = eventID;
  output[8] = particleID;
  output[9] = copy;
  output[10] = time / s;
  output[11] = originParticle;

  PSfile.write((char *)&output, sizeof(output));
  fEventAction->tracks.push_back(track->GetTrackID());

  G4cout << particleName << " saved at = " << newPos / mm << " with KE = " << particleEnergy << " with momentum " << boxMomentum << " TracKID = " << track->GetTrackID() << " originParticle " << originParticle << " copy " << copy << G4endl;
}

G4double MySteppingAction::calculateDistanceToExitBox(const G4ThreeVector &preStepPosition, const G4ThreeVector &preStepMomentumDirection)
{
  // does step exit box in x, y or z?
  G4double tXneg = (-.00015 - preStepPosition.x()) / preStepMomentumDirection.x();
  G4double tXpos = (.00015 - preStepPosition.x()) / preStepMomentumDirection.x();

  G4double tYneg = (-.00015 - preStepPosition.y()) / preStepMomentumDirection.y();
  G4double tYpos = (.00015 - preStepPosition.y()) / preStepMomentumDirection.y();

  G4double tZneg = (-.00015 - preStepPosition.z()) / preStepMomentumDirection.z();
  G4double tZpos = (.00015 - preStepPosition.z()) / preStepMomentumDirection.z();

  // G4cout << tXneg << " " << tXpos << " " << tYneg << " " << tYpos << " " << tZneg << " " << tZpos << " " << G4endl;

  tXneg = tXneg > 1e-15 ? tXneg : DBL_MAX;
  tXpos = tXpos > 1e-15 ? tXpos : DBL_MAX;
  tYneg = tYneg > 1e-15 ? tYneg : DBL_MAX;
  tYpos = tYpos > 1e-15 ? tYpos : DBL_MAX;
  tZneg = tZneg > 1e-15 ? tZneg : DBL_MAX;
  tZpos = tZpos > 1e-15 ? tZpos : DBL_MAX;

  G4double distanceToExit = std::min({tXneg, tXpos, tZneg, tZpos}); // shortest distance travelled to cross box surface

  // G4cout << tXneg << " " << tXpos << " " << tYneg << " " << tYpos << " " << tZneg << " " << tZpos << " " << G4endl;
  if ((tYneg <= distanceToExit) || (tYpos <= distanceToExit)) // exit y
  {
    return DBL_MAX;
  }

  return distanceToExit;
}

