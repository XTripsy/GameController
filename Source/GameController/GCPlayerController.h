// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <Kismet/GameplayStatics.h>
#include "GCPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IInterfacePlayer;
class IInterfaceGameMode;
class USerialCom;

UCLASS()
class GAMECONTROLLER_API AGCPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AGCPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* CursorAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

private:
	void Move(const FInputActionValue& Value);
	void Cursor(const FInputActionValue& Value);
	void CursorIdle(const FInputActionValue& value);
	void Shoot();
	void EndShoot();

	void OpenSerialPort(int32 PortId, int32 BaudRate);
	void SendData(TArray<uint8> Data);
	TArray<uint8> ReceiveData();
	void CloseSerialPort();

private:
	USerialCom* SerialPort;
	FVector2D vMousePosition;
	FVector vMouseWorldLocation;
	float fSensitivity;
	bool bIsShoot;

private:
	IInterfacePlayer* InterfacePlayer;
	IInterfaceGameMode* InterfaceGameMode;
};
