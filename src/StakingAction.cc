#include "StackingAction.hh"
#include "G4Track.hh"
#include "G4NeutrinoE.hh"

MyStackingAction::MyStackingAction(){ }
MyStackingAction::~MyStackingAction(){ }
G4ClassificationOfNewTrack MyStackingAction::ClassifyNewTrack(const G4Track* track){
	MyEventAction *eventaction=(MyEventAction*)G4RunManager::GetRunManager()->GetUserEventAction();	
	eventaction->UpdateMap(track->GetTrackID(), track->GetDefinition()->GetParticleName(), track->GetParentID());
	RE01TrackInformation* trackInfo=new RE01TrackInformation(track);
	trackInfo->SetSourceTrackInformation(track);
	track->SetUserInformation(trackInfo);
//MyTrackInformation* trackInfo= new MyTrackInformation(track);
      	//trackInfo = (RE01TrackInformation*)(aTrack->GetUserInformation());
      	//trackInfo->SetTrackingStatus(0);
      	//trackInfo->SetSourceTrackInformation(aTrack);	
	return fUrgent;
 }
