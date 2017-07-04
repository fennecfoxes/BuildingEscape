// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// How far to reach to pick up object (cm from player)
	float GrabberReach = 100.0f;
	
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* Input = nullptr;

	// Ray-cast and grab object within POV reach
	void Grab();

	// Called when grab key is released
	void Release();

	// Called to find physics handle component
	void FindPhysicsHandleComponent();

	// Called to find (assumed) attached input component and setup
	void FindInputComponent();

	// Returns first object within POV reach
	const FHitResult GetFirstPhysicsBodyWithinReach();

	// Get reach line end from player
	FVector GetLineTraceEnd();

	// Get reach line start from player
	FVector GetLineTraceStart();
};
