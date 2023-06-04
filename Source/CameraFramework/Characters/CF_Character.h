// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CF_Character.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UCameraShakeBase;


UCLASS()
class CAMERAFRAMEWORK_API ACF_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACF_Character();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	USpringArmComponent* SpringArm;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float DefaultSpeed = 600.0f; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintSpeed = 900.0f; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float TurnRate = 45.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float LookUpRate = 45.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TSubclassOf<UCameraShakeBase> SprintShake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TSubclassOf<UCameraShakeBase> LandShake;

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// MOVEMENT // 
	void MoveForward(float Value);
	void MoveRight(float Value);
	void SprintStart();
	void SprintEnd();

	// Look Axis //
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	virtual void Landed(const FHitResult& Hit) override;


	UPROPERTY(BlueprintReadWrite, Category = "Camera")
	UCameraShakeBase* CurrentSprintShake = nullptr;



	
};
