#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MinionMobileGameMode.generated.h"

UCLASS()
class MINIONMOBILE_API AMinionMobileGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

private:
	void SpawnFloor();
	void SpawnMinions();
};
