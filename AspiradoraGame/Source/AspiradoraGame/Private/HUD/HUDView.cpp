// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/HUDView.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
AHUDView::AHUDView()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> HealthBarObj(TEXT("/Game/Widgets/HUD"));
	HUDWidgetClass = HealthBarObj.Class;
}

void AHUDView::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
			
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Viewport not initialized"));
		}
	}
}
