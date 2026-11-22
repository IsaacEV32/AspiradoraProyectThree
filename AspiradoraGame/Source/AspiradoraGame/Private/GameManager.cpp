// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
UGameManager::UGameManager()
{
	life = 3;
	maxLife = 3;
}
void UGameManager::BeginPlay()
{
	ACharacter* characterInstance = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (characterInstance == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACharacter is null"));
	}
	player = Cast<AAspiradoraGameCharacter>(characterInstance)->GetHUDComponent();
	playerCharacter = Cast<AAspiradoraGameCharacter>(characterInstance);
	playerCharacter->onLifeChange.AddUniqueDynamic(this, &UGameManager::OnLifeChanged);
	hud = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AHUDView>();
}

FText UGameManager::RequestChangeOfHealth()
{
	if (!IsValid(player))
	{
		UE_LOG(LogTemp, Warning, TEXT("The hud component is not available"));
		FText textNull = FText::FromString("Cargando");
		ACharacter* characterInstance = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		player = Cast<AAspiradoraGameCharacter>(characterInstance)->GetHUDComponent();
		playerCharacter = Cast<AAspiradoraGameCharacter>(characterInstance);
		if (IsValid(playerCharacter))
		{
			playerCharacter->onLifeChange.AddUniqueDynamic(this, &UGameManager::OnLifeChanged);
		}
		return textNull;
	}
	if (playerCharacter == nullptr)
	{
		FText textNull = FText::FromString("Cargando player");
		ACharacter* characterInstance = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		player = Cast<AAspiradoraGameCharacter>(characterInstance)->GetHUDComponent();
		playerCharacter = Cast<AAspiradoraGameCharacter>(characterInstance);
		UE_LOG(LogTemp, Warning, TEXT("The player character is null"));
		return textNull;
	}
	return hud->GetHealthIntText(playerCharacter->GetCurrentLife());

}

void UGameManager::OnLifeChanged(int newLife, int _maxLife)
{
	UE_LOG(LogTemp, Warning, TEXT("OnChangeHealth: life = %d, maxLife = %d"), life, maxLife);
	life = newLife;
	maxLife = _maxLife;
}
