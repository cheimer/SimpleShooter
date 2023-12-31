// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	AGun();

	void PullTrigger();

protected:
	virtual void BeginPlay() override;

private:
	bool GunTrace(FHitResult& OutHit, FVector& ShotDirection);

	AController* GetOwnerController();

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USceneComponent* GunRootComponent;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Particle")
	class UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, Category = "Particle")
	class UParticleSystem* HitFlash;

	UPROPERTY(EditAnywhere, Category = "Particle")
	float MaxRange = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "Particle")
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundBase* HitSound;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TEnumAsByte<ECollisionChannel> BulletCollisionChannel;
};
