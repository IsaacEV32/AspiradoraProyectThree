// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlataformaMobil.generated.h"

UCLASS()
class ASPIRADORAGAME_API APlataformaMobil : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlataformaMobil();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector MovementOffset = FVector(0.0f, 0.0f, 300.0f);

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (ClampMin = "0.0"))
	float MovementSpeed = 100.0f;

	FVector PointA;
	FVector PointB;
	bool bMovingToB = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
