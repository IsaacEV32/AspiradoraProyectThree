#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnemigoPawn.generated.h"

class UCapsuleComponent;
class UFloatingPawnMovement;
class UStaticMeshComponent;

UCLASS()
class ASPIRADORAGAME_API AEnemigoPawn : public APawn
{
	GENERATED_BODY()

public:
	AEnemigoPawn();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCapsuleComponent> Capsula;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Malla;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UFloatingPawnMovement> Movimiento;

	// Distancia a la que empieza a perseguir
	UPROPERTY(EditAnywhere, Category = "IA")
	float RadioDeteccion = 800.f;

	// Distancia a la que deja de perseguir (mayor que la anterior)
	UPROPERTY(EditAnywhere, Category = "IA")
	float RadioPerdida = 1200.f;

	UPROPERTY(EditAnywhere, Category = "IA")
	float Velocidad = 250.f;

	UPROPERTY(EditAnywhere, Category = "IA")
	float IntervaloComprobacion = 0.2f;

	FTimerHandle TimerComprobacion;
	bool bPersiguiendo = false;

	void ComprobarJugador();
};
