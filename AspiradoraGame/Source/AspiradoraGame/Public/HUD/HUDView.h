// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDView.generated.h"

/**
 * 
 */
UCLASS()
class ASPIRADORAGAME_API AHUDView : public AHUD
{
	GENERATED_BODY()
	
public:
	AHUDView();

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "Health")
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Health")
	class UUserWidget* CurrentWidget;
	
};
