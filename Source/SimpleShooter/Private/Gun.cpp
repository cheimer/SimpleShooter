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

void AGun::PullTrigger()
{
	if (MuzzleFlash)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	}

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return;

	auto OwnerController = OwnerPawn->GetController();
	if (!OwnerController) return;

	FVector ViewPointVec; FRotator ViewPointRot;
	OwnerController->GetPlayerViewPoint(ViewPointVec, ViewPointRot);

	FVector EndVec = ViewPointVec + ViewPointRot.Vector() * MaxRange;

	FHitResult HitInfo;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitInfo, ViewPointVec, EndVec, BulletCollisionChannel);

	if (bHit)
	{
		if (HitFlash)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFlash, HitInfo.Location, (-ViewPointRot.Vector()).Rotation(), true);
		}

		if (!HitInfo.GetActor()) return;

		FPointDamageEvent DamageEvent(Damage, HitInfo, ViewPointRot.Vector(), nullptr);
		HitInfo.GetActor()->TakeDamage(Damage, DamageEvent, OwnerController, this);
	}

}

void AGun::BeginPlay()
{
	Super::BeginPlay();

	
}
