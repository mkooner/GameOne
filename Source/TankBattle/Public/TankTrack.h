// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank Tracks is used to set maxium driving force, and apply forces to tank 
 */

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable, Category="Input")
	void SetThrottle(float Throttle);
	UTankTrack(); 
	void DriveTrack();
	
	
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 400000; //Assume 40T tank at 1g acceleration 

protected:
	virtual void BeginPlay() override;
	void ApplySidewaysForce(float DeltaTime);
	float CurrentThrottle = 0.0;
	
private:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
