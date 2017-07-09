// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Needed for GetWorld()
#include "Engine/World.h"
#include "GameFramework/PlayerController.h" 

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	door = GetOwner();

	if (!door)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: door not set"), *FString(__func__));
		return;
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: PressurePlate not set"), *FString(__func__));
		return;
	}

	// Poll trigger volume every frame to see if total mass is in trigger volume
	// if so, open door
	if (GetTotalMassOfActorsOnPlate() > TriggerMass)
	{
		OnOpenRequest.Broadcast();
	}
	else
	{
		OnCloseRequest.Broadcast(); // close door
	}
}

// Get total pass of actors on trigger volume
float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.0f;
	TArray<AActor*> OverlappingActors;

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: PressurePlate not set"), *FString(__func__));
		return TotalMass;
	}

	// Find all overlapping actors in trigger area
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	// Add and return mass of actors
	for (const auto* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("Mass of %s actor is %f, total mass = %f"), *Actor->GetName(), Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass(), TotalMass);
	}

	return TotalMass;
}