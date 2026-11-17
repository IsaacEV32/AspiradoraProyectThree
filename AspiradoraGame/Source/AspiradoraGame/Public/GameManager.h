// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HUD/HUDPlayer.h"
#include "HUD/HUDView.h"
#include "AspiradoraGameCharacter.h"
#include "Kismet/GameplayStatics.h"
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
	UFUNCTION(BlueprintPure, Category = "Health")
	FText RequestChangeOfHealth();

private:
	UPROPERTY()
	UHUDPlayer* player;
	UPROPERTY()
	AHUDView* hud; 
	
	
};
