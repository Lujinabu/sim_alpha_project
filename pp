
G4ThreeVector G4RadioactiveDecay::calculateDiffusion(const G4double diffusionTime, const G4double Dwater, const G4Track &theTrack)
{
    // G4double tolerance = 1e-12; // tolerance for checking time for intersection with seed to avoid rounding errors

    G4ThreeVector changePosition = G4ThreeVector();
    G4String startVolume = theTrack.GetVolume()->GetName();

    if (currentVolume == "physIce")
    {
        // Assumed no diffusion in the ice so no change in position
        return changePosition;
    }
    // generate random direction vector for the total diffusion
    G4ThreeVector direction = G4ThreeVector(G4UniformRand() - 0.5, G4UniformRand() - 0.5, G4UniformRand() - 0.5);// why 0.5 ??
    direction = direction * 1 / direction.mag();//normalize the direaction

    G4ThreeVector startPos = theTrack.GetPosition();

            G4double distWaterDiff = abs(G4RandGauss::shoot(0, sqrt(6 * Dwater * diffusionTime / s)));//The distance the particle diffuses is sampled from a Gaussian distribution
            changePosition = distWaterDiff * direction;



    return changePosition;
}

/////////////////////////////////////////////////////

G4ThreeVector G4RadioactiveDecay::calculateDiffusion(const G4double diffusionTime, const G4double Dwater, const G4Track &theTrack)
{
    G4ThreeVector changePosition = G4ThreeVector(); // Default no movement
    G4String currentVolume = theTrack.GetVolume()->GetName(); // Get current volume name
    G4ThreeVector startPos = theTrack.GetPosition(); // Initial position

        // If the particle is already inside physIce, assume no diffusion
    if (currentVolume == "physIce")
    {
        // No diffusion in ice
        return changePosition;
    }

    // Define the bounds of physIce as per detector construction
    G4double xIceHalf = 10 * mm; // Half-length of physIce in x
    G4double yIceHalf = 40 * um; // Half-length of physIce in y
    G4double zIceHalf = 10 * mm; // Half-length of physIce in z

    G4ThreeVector physIceCenter(0, 0, 0); // Center of physIce in world coordinates

    // Generate random diffusion direction
    G4ThreeVector direction = G4ThreeVector(G4UniformRand() - 0.5, G4UniformRand() - 0.5, G4UniformRand() - 0.5).unit();
    G4double distWaterDiff = abs(G4RandGauss::shoot(0, sqrt(6 * Dwater * diffusionTime / s))); // Diffusion distance
    changePosition = distWaterDiff * direction;

    // Calculate the particle's new position after diffusion
    G4ThreeVector newPosition = startPos + changePosition;

    // Check if particle crosses into physIce
    bool wasOutsidePhysIce = 
        fabs(startPos.x() - physIceCenter.x()) > xIceHalf ||
        fabs(startPos.y() - physIceCenter.y()) > yIceHalf ||
        fabs(startPos.z() - physIceCenter.z()) > zIceHalf;

    bool isInsidePhysIce = 
        fabs(newPosition.x() - physIceCenter.x()) <= xIceHalf &&
        fabs(newPosition.y() - physIceCenter.y()) <= yIceHalf &&
        fabs(newPosition.z() - physIceCenter.z()) <= zIceHalf;

    if (wasOutsidePhysIce && isInsidePhysIce)
    {
        // Reflection: Calculate normal at entry point
        G4ThreeVector entryPoint = startPos + direction * ((newPosition - startPos).mag() * 0.5);
        G4ThreeVector normal(0, 0, 0); // Placeholder for normal

        if (fabs(entryPoint.x() - physIceCenter.x()) >= xIceHalf) normal = G4ThreeVector((entryPoint.x() > physIceCenter.x() ? 1 : -1), 0, 0);
        else if (fabs(entryPoint.y() - physIceCenter.y()) >= yIceHalf) normal = G4ThreeVector(0, (entryPoint.y() > physIceCenter.y() ? 1 : -1), 0);
        else if (fabs(entryPoint.z() - physIceCenter.z()) >= zIceHalf) normal = G4ThreeVector(0, 0, (entryPoint.z() > physIceCenter.z() ? 1 : -1));

        // Reflect direction
        direction = direction - 2 * (direction.dot(normal)) * normal;
        direction = direction.unit();

        // Recalculate new position after reflection
        G4double remainingDist = distWaterDiff - (entryPoint - startPos).mag();
        newPosition = entryPoint + direction * remainingDist;

        // Update changePosition to reflect new position
        changePosition = newPosition - startPos;
    }

    return changePosition;
}




























G4ThreeVector G4RadioactiveDecay::calculateDiffusion(const G4double diffusionTime, const G4double Dwater, const G4Track &theTrack)
{
    G4ThreeVector changePosition = G4ThreeVector(); // Default no movement
    G4String currentVolume = theTrack.GetVolume()->GetName(); // Get current volume name
    G4ThreeVector startPos = theTrack.GetPosition(); // Initial position

        // If the particle is already inside physIce, assume no diffusion
    if (currentVolume == "physIce")
    {
        // No diffusion in ice
        return changePosition;
    }

    // Define the bounds of physIce as per detector construction
    G4double xIceHalf = 10 * mm; // Half-length of physIce in x
    G4double yIceHalf = 40 * um; // Half-length of physIce in y
    G4double zIceHalf = 10 * mm; // Half-length of physIce in z

    G4ThreeVector physIceCenter(0, 0, 0); // Center of physIce in world coordinates

    // Generate random diffusion direction
    G4ThreeVector direction = G4ThreeVector(G4UniformRand() - 0.5, G4UniformRand() - 0.5, G4UniformRand() - 0.5).unit();
    direction = direction * 1 / direction.mag();

    G4double distWaterDiff = abs(G4RandGauss::shoot(0, sqrt(6 * Dwater * diffusionTime / s))); // Diffusion distance
    changePosition = distWaterDiff * direction;

    // Calculate the particle's new position after diffusion
    G4ThreeVector newPosition = startPos + changePosition;

    if (newPosition.y() >= -yIceHalf)
    {
        //Calculate The entry point
        G4double distoenter = ( -yIceHalf - startPos.y() ) / direction.y();
        G4ThreeVector entryPoint = startPos + direction * distoenter;

        G4ThreeVector normal(0, 0, 0); // Placeholder for normal

        // if (fabs(entryPoint.x() - physIceCenter.x()) >= xIceHalf) normal = G4ThreeVector((entryPoint.x() > physIceCenter.x() ? 1 : -1), 0, 0);
        if (fabs(entryPoint.y() - physIceCenter.y()) >= yIceHalf) normal = G4ThreeVector(0, (entryPoint.y() > physIceCenter.y() ? 1 : -1), 0);
        // else if (fabs(entryPoint.z() - physIceCenter.z()) >= zIceHalf) normal = G4ThreeVector(0, 0, (entryPoint.z() > physIceCenter.z() ? 1 : -1));

        // Reflect direction
        direction = direction - 2 * (direction.dot(normal)) * normal;
        direction = direction.unit();

        // Recalculate new position after reflection
        G4double remainingDist = distWaterDiff - (entryPoint - startPos).mag();
        newPosition = entryPoint + direction * remainingDist;

        // Update changePosition to reflect new position
        changePosition = newPosition - startPos;
    }

    return changePosition;
}