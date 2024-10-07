#include "PrimaryGeneratorAction.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

MyPrimaryGeneratorAction::MyPrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction()
{
 particleSource = new G4GeneralParticleSource();   
}

MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction()
{
	delete particleSource;

}

void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	particleSource->GeneratePrimaryVertex(anEvent);

}
