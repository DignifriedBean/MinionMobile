#include "MinionMobileGameMode.h"

#include "Engine/StaticMeshActor.h"
#include "Engine/World.h"
#include "MinionCharacter.h"
#include "Components/StaticMeshComponent.h"

void AMinionMobileGameMode::BeginPlay()
{
	Super::BeginPlay();

	SpawnFloor();
	SpawnMinions();
}

void AMinionMobileGameMode::SpawnFloor()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	AStaticMeshActor* Floor = World->SpawnActor<AStaticMeshActor>(
		AStaticMeshActor::StaticClass(),
		FVector(0.0f, 0.0f, -10.0f),
		FRotator::ZeroRotator);

	if (!Floor)
	{
		return;
	}

	UStaticMesh* CubeMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cube.Cube"));
	Floor->GetStaticMeshComponent()->SetStaticMesh(CubeMesh);
	Floor->GetStaticMeshComponent()->SetRelativeScale3D(FVector(34.0f, 34.0f, 0.2f));
#if WITH_EDITOR
	Floor->SetActorLabel(TEXT("PrimitiveFloor"));
#endif
}

void AMinionMobileGameMode::SpawnMinions()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	constexpr int32 Rows = 10;
	constexpr int32 Columns = 10;
	constexpr float Spacing = 260.0f;
	constexpr int32 ExpectedMinionCount = Rows * Columns;

	int32 SpawnedMinions = 0;
	const FVector GridOffset(
		-(Rows - 1) * Spacing * 0.5f,
		-(Columns - 1) * Spacing * 0.5f,
		0.0f);

	for (int32 Row = 0; Row < Rows; ++Row)
	{
		for (int32 Column = 0; Column < Columns; ++Column)
		{
			const FVector Location = GridOffset + FVector(Row * Spacing, Column * Spacing, 0.0f);
			AMinionCharacter* Minion = World->SpawnActor<AMinionCharacter>(
				AMinionCharacter::StaticClass(),
				Location,
				FRotator(0.0f, 180.0f, 0.0f));

			if (Minion)
			{
#if WITH_EDITOR
				Minion->SetActorLabel(FString::Printf(TEXT("PrimitiveMinion_%03d"), SpawnedMinions + 1));
#endif
				++SpawnedMinions;
			}
		}
	}

	checkf(SpawnedMinions == ExpectedMinionCount, TEXT("Expected exactly 100 primitive minions, spawned %d."), SpawnedMinions);
}
