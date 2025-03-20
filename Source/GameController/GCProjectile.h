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

UCLASS()
class GAMECONTROLLER_API AGCProjectile : public AActor, public IInterfaceProjectile
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* PlayerPaperComponent;

public:
	AGCProjectile();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPaperFlipbook* PaperTank;
	UDBTweenActor* TweenActor;
	IInterfaceGameMode* InterfaceGameMode;


private:
	UFUNCTION()
	void EndProjectile();

private:
	virtual void IActivate(FVector start, FVector end) override;
};
