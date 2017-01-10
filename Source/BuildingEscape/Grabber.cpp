// Copyright Work-Pending Games 2016

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = GetWorld()->GetFirstPlayerController();

	UE_LOG(LogTemp, Warning, TEXT("Grabber Ready!"));

	// Look for attached Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle) {

	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Physics Handle missing from %s"), *(GetOwner()->GetName()));
	}

	InputHandle = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputHandle) {
		// Bind the input action
		InputHandle->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Input Handle missing from %s"), *(GetOwner()->GetName()));
	}
}


void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed"));
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Get Player view point
	PlayerController->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	//UE_LOG(LogTemp, Warning, TEXT("Position: %s ... Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());

	// Draw a red line to visualize
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.0f, 0.0f, 10.0f);

	if (IsHoldingObject) {

		// Update location of object being held

		// Check for input to drop the object
	}
	else {

		// Check for input to pick up object
		FHitResult Hit; // Store the object that was hit

		FCollisionObjectQueryParams ObjectQueryParams(ECollisionChannel::ECC_PhysicsBody);	// Basically the LayerMask in Unity terms
		FCollisionQueryParams QueryParams(FName(TEXT("")), false, GetOwner());	// I don't really know

		GetWorld()->LineTraceSingleByObjectType(Hit, PlayerViewPointLocation, LineTraceEnd, ObjectQueryParams, QueryParams);

		AActor * ActorHit = Hit.GetActor();

		if (ActorHit) {
			UE_LOG(LogTemp, Warning, TEXT("Line Trace Hit: %s"), *(ActorHit->GetName()));
		}
	}
}

