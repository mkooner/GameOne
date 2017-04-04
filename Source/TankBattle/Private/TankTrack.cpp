// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	auto Name = GetName();

	//UE_LOG(LogTemp, Warning, TEXT("%s throttle at %f"), *Name, Throttle);


	//TODO Clamp actual throttle value so player can't over drive
	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}


