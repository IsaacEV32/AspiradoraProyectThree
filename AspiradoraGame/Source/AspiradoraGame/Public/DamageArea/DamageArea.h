// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "DamageArea.generated.h"

UCLASS()
class ASPIRADORAGAME_API ADamageArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageArea();
public: 
	UPROPERTY(EditAnywhere)
	UBoxComponent* collisionArea;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UDamageType> collisionDamage;

	UPROPERTY(EditAnywhere)
	AActor* player;

	UPROPERTY(EditAnywhere)
	FHitResult hit;

	bool bCanApplyDamage;
	FTimerHandle damageTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	/*virtual void Tick(float DeltaTime) override;*/

	UFUNCTION()
	void OnActorOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnActorOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void ApplyDamage();
};
