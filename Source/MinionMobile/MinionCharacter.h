#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MinionCharacter.generated.h"

class UStaticMeshComponent;

UCLASS()
class MINIONMOBILE_API AMinionCharacter : public AActor
{
	GENERATED_BODY()

public:
	AMinionCharacter();

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Body;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Head;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LeftEye;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* RightEye;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LeftLeg;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* RightLeg;
};
