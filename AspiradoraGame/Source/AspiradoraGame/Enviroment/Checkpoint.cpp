// Fill out your copyright notice in the Description page of Project Settings.


#include "Enviroment/Checkpoint.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Character.h"
#include "Enviroment/CheckpointSubsystem.h"


// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	SetRootComponent(Trigger);
	Trigger->SetBoxExtent(FVector(100.f, 200.f, 150.f));
	Trigger->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	SpawnArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnArrow"));
	SpawnArrow->SetupAttachment(Trigger);

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnTriggerOverlap);
}

FTransform ACheckpoint::GetRespawnTransform() const
{
	return SpawnArrow->GetComponentTransform();
}

void ACheckpoint::OnTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bActivated) return;

	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (!Character || !Character->IsPlayerControlled()) return;

	bActivated = true;
	if (UCheckpointSubsystem* Subsystem = GetWorld()->GetSubsystem<UCheckpointSubsystem>())
	{
		Subsystem->SetCheckpoint(this);
	}
}

