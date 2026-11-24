// Fill out your copyright notice in the Description page of Project Settings.


#include "PlataformaMobil.h"


// Sets default values
APlataformaMobil::APlataformaMobil()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlataformaMobil::BeginPlay()
{
	Super::BeginPlay();

	PointA = GetActorLocation();
	PointB = PointA + MovementOffset;
	SetActorLocation(PointA);
}

// Called every frame
void APlataformaMobil::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector TargetLocation = bMovingToB ? PointB : PointA;
	const FVector NewLocation = FMath::VInterpConstantTo(GetActorLocation(), TargetLocation, DeltaTime, MovementSpeed);

	SetActorLocation(NewLocation);

	if (NewLocation.Equals(TargetLocation, 1.0f))
	{
		SetActorLocation(TargetLocation);
		bMovingToB = !bMovingToB;
	}
}

