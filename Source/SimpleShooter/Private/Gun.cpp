// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"


AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = false;

	GunRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(GunRootComponent);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

}

void AGun::BeginPlay()
{
	Super::BeginPlay();


}

void AGun::PullTrigger()
{
	if (MuzzleFlash)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	}

	if (MuzzleSound)
	{
		UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
	}

	FHitResult HitInfo;
	FVector ShotDirection;

	bool bHit = GunTrace(HitInfo, ShotDirection);

	if (bHit)
	{
		if (HitFlash)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFlash, HitInfo.Location, ShotDirection.Rotation(), true);
		}

		if (HitSound)
		{
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), HitSound, HitInfo.Location);
		}

		if (!HitInfo.GetActor()) return;

		FPointDamageEvent DamageEvent(Damage, HitInfo, ShotDirection, nullptr);

		AController* OwnerController = GetOwnerController();
		HitInfo.GetActor()->TakeDamage(Damage, DamageEvent, OwnerController, this);
	}

}

bool AGun::GunTrace(FHitResult& OutHit, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();

	FVector ViewPointVec; FRotator ViewPointRot;
	OwnerController->GetPlayerViewPoint(ViewPointVec, ViewPointRot);
	if (!OwnerController) return false;

	ShotDirection = -ViewPointRot.Vector();

	FVector EndVec = ViewPointVec + ViewPointRot.Vector() * MaxRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(OutHit, ViewPointVec, EndVec, BulletCollisionChannel, Params);
}

AController* AGun::GetOwnerController()
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return nullptr;

	AController* OwnerController = OwnerPawn->GetController();
	if (!OwnerController) return nullptr;

	return OwnerController;
}
