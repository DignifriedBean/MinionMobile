#include "MinionCharacter.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AMinionCharacter::AMinionCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
	UStaticMesh* SphereMesh = SphereMeshAsset.Object;
	UStaticMesh* CubeMesh = CubeMeshAsset.Object;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(SceneRoot);
	Body->SetStaticMesh(SphereMesh);
	Body->SetRelativeLocation(FVector(0.0f, 0.0f, 85.0f));
	Body->SetRelativeScale3D(FVector(0.55f, 0.55f, 0.85f));

	Head = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));
	Head->SetupAttachment(SceneRoot);
	Head->SetStaticMesh(SphereMesh);
	Head->SetRelativeLocation(FVector(0.0f, 0.0f, 165.0f));
	Head->SetRelativeScale3D(FVector(0.46f, 0.46f, 0.38f));

	LeftEye = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftEye"));
	LeftEye->SetupAttachment(Head);
	LeftEye->SetStaticMesh(SphereMesh);
	LeftEye->SetRelativeLocation(FVector(31.0f, -17.0f, 10.0f));
	LeftEye->SetRelativeScale3D(FVector(0.13f, 0.13f, 0.13f));

	RightEye = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightEye"));
	RightEye->SetupAttachment(Head);
	RightEye->SetStaticMesh(SphereMesh);
	RightEye->SetRelativeLocation(FVector(31.0f, 17.0f, 10.0f));
	RightEye->SetRelativeScale3D(FVector(0.13f, 0.13f, 0.13f));

	LeftLeg = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftLeg"));
	LeftLeg->SetupAttachment(SceneRoot);
	LeftLeg->SetStaticMesh(CubeMesh);
	LeftLeg->SetRelativeLocation(FVector(0.0f, -20.0f, 20.0f));
	LeftLeg->SetRelativeScale3D(FVector(0.18f, 0.18f, 0.42f));

	RightLeg = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightLeg"));
	RightLeg->SetupAttachment(SceneRoot);
	RightLeg->SetStaticMesh(CubeMesh);
	RightLeg->SetRelativeLocation(FVector(0.0f, 20.0f, 20.0f));
	RightLeg->SetRelativeScale3D(FVector(0.18f, 0.18f, 0.42f));
}
