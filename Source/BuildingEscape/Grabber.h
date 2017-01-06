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

	float Reach = 100.0f;

	bool IsHoldingObject = false;
	AActor* ObjectBeingHeld;

	UPhysicsHandleComponent * PhysicsHandle = nullptr;

};
