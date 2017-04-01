// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankTurret.h"




void UTankTurret::Rotate(float DegreesPerSecond)
{
	//Bound Speed of movement
	DegreesPerSecond = FMath::Clamp<float>(DegreesPerSecond, -1, 1);

	//Move the barrel the right amount this frame
	//Give a max elevation speed and the frame time
	auto RotationChange = DegreesPerSecond * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawRotation = RelativeRotation.Yaw + RotationChange;

	//auto Rotation = FMath::Clamp<float>(RawRotation, MinRotation, MaxRotation);

	SetRelativeRotation(FRotator(0, RawRotation, 0));

}