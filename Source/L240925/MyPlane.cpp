// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlane.h"

// Sets default values
AMyPlane::AMyPlane()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> BodyMesh(TEXT("/Game/SM_P38_Body.SM_P38_Body"));

	if (BodyMesh.Succeeded())
	{
		Body->SetStaticMesh(BodyMesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> PlaneMaterial(TEXT("/Game/M_P38.M_P38"));

	if (PlaneMaterial.Succeeded())
	{
		Body->SetMaterial(0, PlaneMaterial.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> PropellerMesh(TEXT("/Game/SM_P38_Propeller.SM_P38_Propeller"));
	Propeller1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Propeller1"));
	Propeller2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Propeller2"));

	if (PropellerMesh.Succeeded())
	{
		Propeller1->SetStaticMesh(PropellerMesh.Object);
		Propeller2->SetStaticMesh(PropellerMesh.Object);
		Propeller1->SetupAttachment(Body);
		Propeller2->SetupAttachment(Body);
	}
	
	Propeller1->SetRelativeLocation(FVector(37.0f, -21.0f, 1.0f));
	Propeller2->SetRelativeLocation(FVector(37.0f, 21.0f, 1.0f));


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Body);
	Camera->SetRelativeLocation(FVector(-80.0f, 0.0f, 50.0f));
	Camera->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void AMyPlane::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotatePropeller();
	RotateCamera();
}

// Called to bind functionality to input
void AMyPlane::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("CameraYaw"), this, &AMyPlane::YawCamera);
	PlayerInputComponent->BindAxis(TEXT("CameraPitch"), this, &AMyPlane::PitchCamera);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyPlane::MoveFoward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyPlane::RotateBody);
}

void AMyPlane::MoveFoward(float AxisValue)
{
	AddActorWorldOffset(GetActorForwardVector() * AxisValue * 5.0f);
}

void AMyPlane::RotateBody(float AxisValue)
{
	AddActorWorldRotation(FRotator(0.0f,  2.0f * AxisValue, 0.0f));
	//FRotator NewRotator = FRotator(0.0f, GetActorRotation().Yaw, 0.0f);
	//NewRotator.Yaw = FMath::Clamp(NewRotator.Yaw, -30.0f, 30.0f);
	//SetActorRotation(NewRotator);
}

void AMyPlane::RotateCamera()
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Pitch += CameraInput.Y;
	SetActorRotation(NewRotation);
}

void AMyPlane::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}

void AMyPlane::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void AMyPlane::RotatePropeller()
{
	Propeller1->AddLocalRotation(FRotator(0.0f, 0.0f, 5.0f));
	Propeller2->AddLocalRotation(FRotator(0.0f, 0.0f, 5.0f));
}

