// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CF_ViewTargetActor.generated.h"

class UBoxComponent;

UCLASS()
class CAMERAFRAMEWORK_API ACF_ViewTargetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACF_ViewTargetActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* OverlapBox;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ViewTarget")
	bool bIsDynamic = false; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ViewTarget")
	AActor* ViewTarget = nullptr;
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ViewTarget")
	float BlendTime = 1.0f; 


  UFUNCTION()
  void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult);


  UFUNCTION()
  void OnOverlapEnd(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
    int32 OtherBodyIndex);


private:
  APlayerController* PC;
  bool bIsOverlapped = false;


};
