//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file runAndEvent/RE01/include/RE01TrackInformation.hh
/// \brief Definition of the RE01TrackInformation class
//
//
//

#ifndef RE01TrackInformation_h
#define RE01TrackInformation_h 1

#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4Track.hh"
#include "G4Allocator.hh"
#include "G4VUserTrackInformation.hh"

class RE01TrackInformation : public G4VUserTrackInformation 
{
public:
  RE01TrackInformation();
  RE01TrackInformation(const G4Track* aTrack);
  RE01TrackInformation(const RE01TrackInformation* aTrackInfo);
  virtual ~RE01TrackInformation();
   
  inline void *operator new(size_t);
  inline void operator delete(void *aTrackInfo);

  RE01TrackInformation& operator =(const RE01TrackInformation& right);
  
  void SetSourceTrackInformation(const G4Track* aTrack);

public:
//  inline G4int GetTrackingStatus() const {return fTrackingStatus;}
//  inline void  SetTrackingStatus(G4int i) {fTrackingStatus = i;}
//  inline G4int GetParentTrackID() const {return fSourceTrackID;}
//  inline void  SetSuspendedStepID(G4int i) {fSuspendedStepID = i;}
//  inline G4int GetSuspendedStepID() const {return fSuspendedStepID;}
  inline G4String GetTrackParticleName()const {return fParticleDefinition->GetParticleName();}
  inline G4int GetTrack_ID()const {return fTrackID;}
  inline G4int GetParent_ID()const {return fSourceTrackID;}
private:
  G4int                 fTrackID;  // Track ID 
  G4ParticleDefinition* fParticleDefinition;

  G4int                 fSourceTrackID;//parent track id
};

extern G4ThreadLocal
 G4Allocator<RE01TrackInformation> * aTrackInformationAllocator;

inline void* RE01TrackInformation::operator new(size_t)
{
  if(!aTrackInformationAllocator)
    aTrackInformationAllocator = new G4Allocator<RE01TrackInformation>;
  return (void*)aTrackInformationAllocator->MallocSingle();
}

inline void RE01TrackInformation::operator delete(void *aTrackInfo)
{ aTrackInformationAllocator->FreeSingle((RE01TrackInformation*)aTrackInfo);}

#endif
