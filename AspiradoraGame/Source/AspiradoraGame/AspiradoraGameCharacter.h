// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "NativeGameplayTags.h"
#include "GameplayTagContainer.h"
#include "Public/GameManager.h"
#include "AspiradoraGameCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Player);

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLifeChange, int, life, int, maxLife);

UCLASS(abstract)
class AAspiradoraGameCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	

	
protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* DashAction;

	////Absorber con la aspiradora
	//UPROPERTY(EditAnywhere, Category = "Input")
	//UInputAction* AbsorbAction;

	////Expular objeto absorvido
	//UPROPERTY(EditAnywhere, Category = "Input")
	//UInputAction* ReleaseAction;

public:

	/** Constructor */
	AAspiradoraGameCharacter();	

protected:

	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	virtual void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

public:

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoDash();

	UFUNCTION()
	void StopDashing();

	UFUNCTION()
	void ResetDash();

	UFUNCTION()
	void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "Life")
	void ReceiveDamage(int Amount);

	UFUNCTION(BlueprintCallable, Category = "Life")
	void Heal(int Amount);

	UFUNCTION(BlueprintPure, Category = "Life")
	bool IsDead() const { return life <= 0; }

	//Evento muerte
	UFUNCTION(BlueprintImplementableEvent, Category = "Life")
	void OnDeath();

	UFUNCTION()
	int32& GetCurrentLife();

	//UFUNCTION(BlueprintCallable, Category = "Aspiradora")
	//void Absorb();

	////Prueba si esta listo para absorber
	//UFUNCTION(BlueprintCallable, Category = "Aspiradora")
	//bool TryAbsorb(AActor* Target);

	////Expulsa el objeto absorvido 
	//UFUNCTION(BlueprintCallable, Category = "Aspiradora")
	//AActor* Release();

	////Devuelve la cantidad de objetos absorvidos
	//UFUNCTION(BlueprintPure, Category = "Aspiradora")
	//int GetAbsorbedCount() const { return absorbedObjects.Num(); }

	////Devuelve si esta llena la aspiradora
	//UFUNCTION(BlueprintPure, Category = "Aspiradora")
	//bool IsVacuumFull() const { return absorbedObjects.Num() >= maxAbsorbedObjects; }

	////Evento Abosrber
	//UFUNCTION(BlueprintImplementableEvent, Category = "Aspiradora")
	//void OnObjectAbsorbed(AActor* Object);

	////Evento Expulsar
	//UFUNCTION(BlueprintImplementableEvent, Category = "Aspiradora")
	//void OnObjectReleased(AActor* Object);

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FGameplayTagContainer InteractableTags;

	///////////

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Life", meta = (ClampMin = "1"))
	int maxLife;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Life", meta = (ClampMin = "0"))
	int life;


	//Delegate for any change in the players health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Life")
	FOnLifeChange onLifeChange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameManager")
	UGameManager* gameManager;
	UPROPERTY(EditAnywhere)
	float dashDistance;

	UPROPERTY(EditAnywhere)
	float dashCooldown;

	UPROPERTY()
	bool canDash;

	UPROPERTY(EditAnywhere)
	float dashStop;

	UPROPERTY()
	FTimerHandle unusedHandle;
	
	//Lista de objetos absorvidos
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Aspiradora")
	TArray<TObjectPtr<AActor>> absorbedObjects;

	//Maximo de objetos absorvibles
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aspiradora", meta = (ClampMin = "1"))
	int maxAbsorbedObjects;
};

