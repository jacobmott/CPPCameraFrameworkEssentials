// Fill out your copyright notice in the Description page of Project Settings.


#include "CF_Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACF_Character::ACF_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
  //SpringArm->TargetArmLength = 1000;
  //SpringArm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);


}

// Called when the game starts or when spawned
void ACF_Character::BeginPlay()
{
	Super::BeginPlay();

	DefaultSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

// Called every frame
void ACF_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACF_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// ACTIONS // 
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ACF_Character::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ACF_Character::SprintEnd);

	// AXIS // 
	PlayerInputComponent->BindAxis("MoveForward", this, &ACF_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACF_Character::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &ACF_Character::LookUpAtRate);
	PlayerInputComponent->BindAxis("Turn", this, &ACF_Character::TurnAtRate);


}

void ACF_Character::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Yaw(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ACF_Character::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Yaw(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ACF_Character::SprintStart()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed; 

	if (SprintShake && GetVelocity().Length() != 0) {
    CurrentSprintShake = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(SprintShake, 1);
  }

}

void ACF_Character::SprintEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed; 


	if (CurrentSprintShake) {
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StopCameraShake(CurrentSprintShake, true);
    CurrentSprintShake = nullptr;
	}

}

void ACF_Character::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * TurnRate * GetWorld()->GetDeltaSeconds());
}

void ACF_Character::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * LookUpRate * GetWorld()->GetDeltaSeconds());
}

void ACF_Character::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if (LandShake) {
		UGameplayStatics::PlayWorldCameraShake(this, LandShake, GetActorLocation(), 400, 2000);
	}


}




