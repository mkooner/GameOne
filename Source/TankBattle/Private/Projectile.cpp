// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	//CollisionMesh->SetVisibility(false);

	Blast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Blast"));
	Blast->AttachToComponent(CollisionMesh, FAttachmentTransformRules::KeepRelativeTransform);

	Impact = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact"));
	Impact->AttachToComponent(CollisionMesh, FAttachmentTransformRules::KeepRelativeTransform);
	Impact->bAutoActivate = false;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false; 

	Force = CreateDefaultSubobject<URadialForceComponent>(FName("Force"));
	Force->AttachToComponent(CollisionMesh, FAttachmentTransformRules::KeepRelativeTransform);


}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::Launch(float Speed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
}

// This method is only called when the Projectile Hits somthing
void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	Blast->Deactivate();
	Impact->Activate();
	Force->FireImpulse();

	SetRootComponent(Blast);
	CollisionMesh->DestroyComponent();

	FTimerHandle Timer;

	//GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::OnTimerExpire, DestroyTime, false);
	GetWorldTimerManager().SetTimer(Timer, this, &AProjectile::OnTimerExpire, DestroyTime, false);
}

void AProjectile::OnTimerExpire()
{
	Destroy();
}