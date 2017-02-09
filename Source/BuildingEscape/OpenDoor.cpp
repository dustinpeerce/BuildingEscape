// Copyright Work-Pending Games 2016

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// Find owner of this object
	Owner = GetOwner();


}

void UOpenDoor::OpenDoor() {

	// Set the door rotation
	// Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
	OnOpenRequest.Broadcast();
}

void UOpenDoor::CloseDoor() {

	// Set the door rotation
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	CurrentTime = GetWorld()->GetTimeSeconds();

	// Poll the Trigger Volume
	if (GetTotalMassofActorsOnPlate() > TriggerMass) {
		OpenDoor();
		LastDoorOpenTime = CurrentTime;
	}

	// If enough time has passed, close the door
	if (CurrentTime - LastDoorOpenTime > DoorCloseDelay) {
		CloseDoor();
	}
		
}

float UOpenDoor::GetTotalMassofActorsOnPlate() {
	float TotalMass = 0.f;

	// Find all overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OverlappingActors);

	// Iterate through them adding their masses
	for (auto& Actor : OverlappingActors) {
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

