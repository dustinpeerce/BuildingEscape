// Copyright Work-Pending Games 2016

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	
private:

	APlayerController* PlayerController;

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	FVector LineTraceEnd;

	float Reach = 100.0f;

	bool IsHoldingObject = false;
	AActor* ActorBeingHeld;

	UPhysicsHandleComponent * PhysicsHandle = nullptr;
	UInputComponent * InputHandle = nullptr;


	void Grab();
	void Release();
	void FindPhysicsHandleComponent();
	void SetupInputComponent();
	const FHitResult GetFirstPhysicsBodyInReach();
};
