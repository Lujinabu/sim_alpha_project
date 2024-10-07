#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class MyActionInitialization : public G4VUserActionInitialization
{
public:
    MyActionInitialization();
     ~MyActionInitialization();
    //  ~MyActionInitialization();
    // virtual void Build() const;


    virtual void BuildForMaster() const override;
    virtual void Build() const override;
    
};

#endif
