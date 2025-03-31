// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "interface/InterfacePlayer.h"
#include "GCPlayer.generated.h"

class UCapsuleComponent;
class PaperZD;
class UPaperFlipbook;
class UPaperFlipbookComponent;
class UCameraComponent;
class USpringArmComponent;
class UPaperZDAnimationComponent;

UCLASS()
class GAMECONTROLLER_API AGCPlayer : public APawn, public IInterfacePlayer
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* PlayerCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* PlayerSpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Capsule, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* PlayerCapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* PlayerPaperComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	UPaperZDAnimationComponent* PaperAnimationComponent;

public:
	AGCPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPaperFlipbook* PaperTank;

private:
	void Slope(float deltatime);

private:
	virtual void IJump() override;
};
