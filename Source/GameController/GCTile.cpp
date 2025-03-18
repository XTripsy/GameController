// Fill out your copyright notice in the Description page of Project Settings.


#include "GCTile.h"
#include <Kismet/GameplayStatics.h>
#include "PaperTileMapComponent.h"
#include "PaperTileMap.h"
#include "Components/BoxComponent.h"
#include "GameFramework/GameModeBase.h"

AGCTile::AGCTile()
{
	static ConstructorHelpers::FObjectFinder<UPaperTileMap>tile_map1(TEXT("/Game/Asset/Tile_1"));
	TileMaps.push_back(tile_map1.Object);
	static ConstructorHelpers::FObjectFinder<UPaperTileMap>tile_map2(TEXT("/Game/Asset/Tile_2"));
	TileMaps.push_back(tile_map2.Object);
	static ConstructorHelpers::FObjectFinder<UPaperTileMap>tile_map3(TEXT("/Game/Asset/Tile_3"));
	TileMaps.push_back(tile_map3.Object);

	TileMapComponents = CreateDefaultSubobject<UPaperTileMapComponent>(TEXT("TileMapComponents"));
	RootComponent = TileMapComponents;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->InitBoxExtent(FVector(700, 32, 385));
	BoxComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComponent->SetGenerateOverlapEvents(true);
	BoxComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	BoxComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &AGCTile::OnOverlapBegin);
	BoxComponent->SetRelativeLocation(FVector(1700, 0, -375));
}

void AGCTile::BeginPlay()
{
	Super::BeginPlay();

	InterfaceGameMode = Cast<IInterfaceGameMode>(GetWorld()->GetAuthGameMode());

	int rage = (int)FMath::FRandRange(0.0f, 2.0f);
	TileMapComponents->SetTileMap(TileMaps[rage]);
}

void AGCTile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	int rage = (int)FMath::FRandRange(0.0f, 2.0f);
	TileMapComponents->SetTileMap(TileMaps[rage]);

	FVector loc = this->GetActorLocation();
	float xLoc = InterfaceGameMode->IGetCurrentLocation();
	this->SetActorLocation(FVector(xLoc + 1750, loc.Y, loc.Z));
	loc = this->GetActorLocation();
	InterfaceGameMode->ISetCurrentLocation(loc.X);
}
