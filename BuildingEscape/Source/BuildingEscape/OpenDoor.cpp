// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "BuildingEscape.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"


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
	// Play has begun when this code runs

	Super::BeginPlay();

	// set the owner on begin play find the actor and get the owner for every instance of this class (every door)
	Owner = GetOwner();

	// Because a pawn IS an actor, we can fetch the pawn and store it in an AActor type
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

}

// This function is of class type UOpenDoor
void UOpenDoor::OpenDoor()
{

	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor::CloseDoor()
{
	// Set the door rotation
	Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume - if triggered, open the door and store when you opened the door
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	//check if it's time to close the door
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
	}
}

