// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

// Needed for GetWorld()
#include "Engine/World.h"
#include "GameFramework/PlayerController.h" 


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

	// ...
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get player view point
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
	
	UE_LOG(LogTemp, Warning, TEXT("Location at %s	Rotation at %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());
	
	// Ray-cast out to reach distance

	// See what we hit
}

