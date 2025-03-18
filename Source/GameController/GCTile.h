// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "interface/InterfaceGameMode.h"
#include "GCTile.generated.h"

class UPaperTileMapComponent;
class UPaperTileMap;
class UBoxComponent;
//class IInterfaceGameMode;

UCLASS()
class GAMECONTROLLER_API AGCTile : public AActor
{
	GENERATED_BODY()
	
public:
	AGCTile();

protected:
	virtual void BeginPlay() override;

private:
	UBoxComponent* BoxComponent;
	UPaperTileMapComponent* TileMapComponents;
	std::vector<UPaperTileMap*> TileMaps;

	IInterfaceGameMode* InterfaceGameMode;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
