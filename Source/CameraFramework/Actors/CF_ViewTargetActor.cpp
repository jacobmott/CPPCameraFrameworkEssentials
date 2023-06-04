// Fill out your copyright notice in the Description page of Project Settings.


#include "CF_ViewTargetActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACF_ViewTargetActor::ACF_ViewTargetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));


}

// Called when the game starts or when spawned
void ACF_ViewTargetActor::BeginPlay()
{
	Super::BeginPlay();

  OverlapBox->SetGenerateOverlapEvents(true);
	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &ACF_ViewTargetActor::OnOverlapBegin);
	OverlapBox->OnComponentEndOverlap.AddDynamic(this, &ACF_ViewTargetActor::OnOverlapEnd);

  PC = UGameplayStatics::GetPlayerController(this, 0);

}

void ACF_ViewTargetActor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
  if (ViewTarget && PC) {
    PC->SetViewTargetWithBlend(ViewTarget, BlendTime);
    bIsOverlapped = true;
    //PC->SetViewTarget(ViewTarget);
  }
}

void ACF_ViewTargetActor::OnOverlapEnd(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
  if (PC) {
    PC->SetViewTargetWithBlend(PC->GetPawn(), BlendTime);
    bIsOverlapped = false;
    //PC->SetViewTarget(ViewTarget);
  }
}

// Called every frame
void ACF_ViewTargetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
  if (!ViewTarget && !bIsDynamic) {
    return;
  }

  if (bIsOverlapped) {
    FRotator Rot = UKismetMathLibrary::FindLookAtRotation(ViewTarget->GetActorLocation(), PC->GetPawn()->GetActorLocation());
    ViewTarget->SetActorRotation(Rot);
  }

}

