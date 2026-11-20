#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CheckpointSubsystem.generated.h"

class ACheckpoint;

UCLASS()
class ASPIRADORAGAME_API UCheckpointSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void SetCheckpoint(ACheckpoint* NewCheckpoint);
	bool HasCheckpoint() const { return CurrentCheckpoint.IsValid(); }

	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	void RespawnPlayer(AController* Controller);

private:
	TWeakObjectPtr<ACheckpoint> CurrentCheckpoint;
};
