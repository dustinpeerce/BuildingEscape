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

}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = GetWorld()->GetFirstPlayerController();

	FindPhysicsHandleComponent();

	SetupInputComponent();
}


// Look for attached Physics Handle
void UGrabber::FindPhysicsHandleComponent() {
	
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!PhysicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("Physics Handle missing from %s"), *(GetOwner()->GetName()));
	}
}


// Find Input Component and Bind Actions
void UGrabber::SetupInputComponent() {
	InputHandle = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputHandle) {
		// Bind the input action
		InputHandle->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputHandle->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Input Handle missing from %s"), *(GetOwner()->GetName()));
	}
}


void UGrabber::Grab() {
	auto HitResult = GetFirstPhysicsBodyInReach();
	ActorBeingHeld = HitResult.GetActor();

	if (ActorBeingHeld) {
		auto ComponentToGrab = HitResult.GetComponent();

		PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
	}

}


void UGrabber::Release() {
	ActorBeingHeld = nullptr;
	PhysicsHandle->ReleaseComponent();
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) {
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	UpdateLineTrace();

	if (PhysicsHandle->GrabbedComponent) {
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}

}


const FHitResult UGrabber::GetFirstPhysicsBodyInReach() {
	// Store the object that was hit
	FHitResult Hit;

	FCollisionObjectQueryParams ObjectQueryParams(ECollisionChannel::ECC_PhysicsBody);	// Basically the LayerMask in Unity terms
	FCollisionQueryParams QueryParams(FName(TEXT("")), false, GetOwner());	// I don't really know

	GetWorld()->LineTraceSingleByObjectType(Hit, PlayerViewPointLocation, LineTraceEnd, ObjectQueryParams, QueryParams);

	return Hit;
}


void UGrabber::UpdateLineTrace() {
	// Get Player view point
	PlayerController->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	// Get Ray Trace Path
	LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}
