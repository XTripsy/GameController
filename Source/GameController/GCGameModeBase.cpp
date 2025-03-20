// Fill out your copyright notice in the Description page of Project Settings.


#include "GCGameModeBase.h"
#include "GCPlayerController.h"
#include "GCProjectile.h"
#include "GCPlayer.h"
#include "interface/InterfaceProjectile.h"

AGCGameModeBase::AGCGameModeBase()
{
	PlayerControllerClass = AGCPlayerController::StaticClass();
	DefaultPawnClass = AGCPlayer::StaticClass();

	fXCurrentLoc = 3480.0f;
}

void AGCGameModeBase::BeginPlay()
{
	for (int i = 0; i < 20; i++)
	{
		Projectiles.Add(GetWorld()->SpawnActor<AGCProjectile>(AGCProjectile::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, FActorSpawnParameters()));
	}
}

void AGCGameModeBase::ISetCurrentLocation(float value)
{
	fXCurrentLoc = value;
}

float AGCGameModeBase::IGetCurrentLocation()
{
	return fXCurrentLoc;
}

void AGCGameModeBase::ISpawnProjectile(FVector start, FVector end)
{
	if (IInterfaceProjectile* interface = Cast<IInterfaceProjectile>(Projectiles[0]))
	{
		Projectiles.RemoveAt(0);
		interface->IActivate(start, end);
	}
}

void AGCGameModeBase::IAddProjectile(UObject* projectile)
{
	Projectiles.Add(projectile);
}
