// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "interface/InterfaceProjectile.h"
#include "DBTweenActor.h"
#include "GCProjectile.generated.h"

class UPaperFlipbookComponent;
class PaperZD;
class UPaperFlipbook;
class IInterfaceGameMode;
class IInterfacePlayer;
class USphereComponent;

UCLASS()
class GAMECONTROLLER_API AGCProjectile : public AActor, public IInterfaceProjectile
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* PaperComponent;

public:
	AGCProjectile();

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComponent;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPaperFlipbook* Projectile;
	UPaperFlipbook* HitProjectile;
	UDBTweenActor* TweenActor;
	IInterfaceGameMode* InterfaceGameMode;
	IInterfacePlayer* InterfacePlayer;
	FDamageEvent* DamageEvent;
	FVector Direction;

private:
	UFUNCTION()
	void UpdateProjectile();

	UFUNCTION()
	void EndProjectile();

private:
	virtual void IActivate(FVector start, FVector end) override;
};
