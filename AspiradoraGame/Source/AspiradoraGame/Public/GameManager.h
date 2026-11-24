// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HUD/HUDView.h"
#include "Kismet/GameplayStatics.h"
#include "StatesOfGame.h"
#include "GameManager.generated.h"

/**
 * 
 */
UCLASS()
class ASPIRADORAGAME_API UGameManager : public UGameInstance
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay();
public: 
	UGameManager();
	UFUNCTION(BlueprintPure, Category = "Health")
	FText RequestChangeOfHealth();
	UFUNCTION()
	virtual void OnLifeChanged(int newLife, int maxLife);

	UPROPERTY()
	AStatesOfGame* changeGameStateManager;
private:
	UPROPERTY()
	AHUDView* hud; 

	int life;
	int maxLife;
	
};
