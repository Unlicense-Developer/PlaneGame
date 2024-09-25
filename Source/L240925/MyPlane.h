// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "MyPlane.generated.h"

UCLASS()
class L240925_API AMyPlane : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPlane();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void MoveFoward(float AxisValue);
	void RotateBody(float AxisValue);
	void RotateCamera();
	void YawCamera(float AxisValue);
	void PitchCamera(float AxisValue);
	void RotatePropeller();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY()
	UStaticMeshComponent* Body;

	UPROPERTY()
	UStaticMeshComponent* Propeller1;

	UPROPERTY()
	UStaticMeshComponent* Propeller2;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	FVector2D CameraInput;
};
