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
	
	
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 400000; //Assume 40T tank at 1g acceleration 

	
};
