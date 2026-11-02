// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HUDPlayer.generated.h"

UCLASS()
class ASPIRADORAGAME_API UHUDPlayer : public UActorComponent
{
	GENERATED_BODY()

private:
	bool bCanBeDamaged;

	FTimerHandle damageTimerHandle;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health");
	int maxLives;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health");
	int currentLives;
	virtual void BeginPlay();
public:
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealth();

	UFUNCTION(BlueprintPure, Category = "Health")
	FText GetHealthIntText();
	//Update health
	UFUNCTION(BlueprintCallable, Category = "Health")
	void UpdateHealth(int HealthChange);

	/** Damage Timer */
	UFUNCTION()
	void DamageTimer();

	/** Set Damage State */
	UFUNCTION()
	void SetDamageState();
	
	UFUNCTION()
	void ApplyDamage(bool IsDamaged, float Damage);
};
