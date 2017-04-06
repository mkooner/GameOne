// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


class UTankAimComponent;
/**
 * 
 */
UCLASS()
class TANKBATTLE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimComponent* AimCompRef);

	
private:
	void AimTowardsCrosshair(); //Starts the tank moving the barrel
	bool GetSightRayHitLocation(FVector& Hit) const;

	UPROPERTY(EditAnywhere)
		float CrosshairX = 0.5;
	UPROPERTY(EditAnywhere)
		float CrosshairY = 0.333333;

	UPROPERTY(EditAnywhere)
		float LineLength = 1000000.0;

};
