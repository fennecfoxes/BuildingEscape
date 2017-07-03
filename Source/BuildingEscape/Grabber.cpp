// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

// Needed for GetWorld()
#include "Engine/World.h"

// Needed for input component
#include "Components/InputComponent.h"

// Needed for DrawDebugLine()
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h" 

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	/// Look for attached physics handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to find physics handle for %s"), *GetOwner()->GetName());
	}

	/// Look for attached input component (only appears at run-time)
	Input = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!Input)
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to find input component for %s"), *GetOwner()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Found input component for %s"), *GetOwner()->GetName());

		/// Bind the input axis
		Input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	FVector PlayerViewPointLocation;
	FVector LineTraceDirection;
	FVector LineTraceEnd;
	FRotator PlayerViewPointRotation;

	/// Get player view point
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	LineTraceDirection = PlayerViewPointRotation.Vector();
	// UE_LOG(LogTemp, Warning, TEXT("Location at %s	Rotation at %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());

	/// Draw red trace to visualize reach
	LineTraceEnd = PlayerViewPointLocation + (LineTraceDirection * GrabberReach);
	// Debug line to visually see what we can pick up
	// DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.0f, 0.0f, 1.0f);
	
	/// Setup query parameters
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	/// Ray-cast out to reach distance 
	FHitResult LineTraceHit;
	bool isHit = GetWorld()->LineTraceSingleByObjectType(OUT LineTraceHit, PlayerViewPointLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);

	/// See what we hit
	if (isHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *LineTraceHit.GetActor()->GetName());
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"), *GetOwner()->GetName());

}

