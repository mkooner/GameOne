// Mehrab Kooner Copyright
#pragma once

#include "Components/ActorComponent.h"
#include "TankAimComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked,
	Empty
};

class UTankBarrel; //Forward Declaration
class UTankTurret;
class AProjectile;
class UTankMovementComponent;

// Sets the aiming points for the tank
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKBATTLE_API UTankAimComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimComponent();
	UTankBarrel*  GetBarrelReference();
	void SetTurretReference(UTankTurret* TurretToSet);
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 5000.0;

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Setup")
		int32 GetAmmo();

	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus FiringState = EFiringStatus::Reloading;

	UPROPERTY(EditDefaultsOnly, Category = "State")
		int32 Ammo = 5;

	UPROPERTY(EditDefaultsOnly, Category = "State")
	float ReloadTime = 3.0;

	double LastFireTime = 0.0;

	bool IsBarrelMoving();

	FVector GlobalAimDirection = FVector();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector Hit);
	void MoveBarrel(FVector AimDirection);

	UFUNCTION(BlueprintCallable, Category = "Action")
		void Fire();

	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> Projectile;

	EFiringStatus GetFiringState() const; 
	
};
