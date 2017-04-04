// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankMovementComponent.h"
#include "TankTurret.h"

void UTankMovementComponent::Initialize(UTankTrack* Left, UTankTrack* Right)
{
	if (!Left || !Right) { return; }

	LeftTrack = Left;
	RightTrack = Right;

}


void UTankMovementComponent::MoveFoward(float Throw)
{

	UE_LOG(LogTemp, Warning, TEXT("Move throttle at %f"),Throw);

}




