// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

void UGameManager::BeginPlay()
{
	ACharacter* characterInstance = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (characterInstance == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACharacter is null"));
	}
	player = Cast<AAspiradoraGameCharacter>(characterInstance)->GetHUDComponent();
	
	hud = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AHUDView>();

}

FText UGameManager::RequestChangeOfHealth()
{
	if (player == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("The hud component is not available"));
		FText textNull;
		ACharacter* characterInstance = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		player = Cast<AAspiradoraGameCharacter>(characterInstance)->GetHUDComponent();
			return textNull;
	}

	return hud->GetHealthIntText(player->GetHealth());
}
