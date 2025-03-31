// Fill out your copyright notice in the Description page of Project Settings.

#include "GCTile.h"
#include <Kismet/GameplayStatics.h>
#include "PaperTileMapComponent.h"
#include "PaperTileMap.h"
#include "Components/BoxComponent.h"
#include "GameFramework/GameModeBase.h"

AGCTile::AGCTile()
{
	Tags.Add("Ground");

	static ConstructorHelpers::FObjectFinder<UPaperTileMap>tile_map1(TEXT("/Game/Assets/Tile/Tileset/Tilemap/Road_1"));
	TileMaps.push_back(tile_map1.Object);
	//static ConstructorHelpers::FObjectFinder<UPaperTileMap>tile_map2(TEXT("/Game/Assets/Tile/Tileset/Tilemap/Road_2"));
	//TileMaps.push_back(tile_map2.Object);
	//static ConstructorHelpers::FObjectFinder<UPaperTileMap>tile_map3(TEXT("/Game/Assets/Tile/Tileset/Tilemap/Road_3"));
	//TileMaps.push_back(tile_map3.Object);
	static ConstructorHelpers::FObjectFinder<UPaperTileMap>tile_map4(TEXT("/Game/Assets/Tile/Tileset/Tilemap/Road_4"));
	TileMaps.push_back(tile_map4.Object);
	static ConstructorHelpers::FObjectFinder<UPaperTileMap>tile_map5(TEXT("/Game/Assets/Tile/Tileset/Tilemap/Road_5"));
	TileMaps.push_back(tile_map5.Object);
	static ConstructorHelpers::FObjectFinder<UPaperTileMap>tile_map6(TEXT("/Game/Assets/Tile/Tileset/Tilemap/Road_6"));
	TileMaps.push_back(tile_map6.Object);
	static ConstructorHelpers::FObjectFinder<UPaperTileMap>tile_map7(TEXT("/Game/Assets/Tile/Tileset/Tilemap/Road_7"));
	TileMaps.push_back(tile_map7.Object);
	static ConstructorHelpers::FObjectFinder<UPaperTileMap>tile_map8(TEXT("/Game/Assets/Tile/Tileset/Tilemap/Road_8"));
	TileMaps.push_back(tile_map8.Object);
	static ConstructorHelpers::FObjectFinder<UPaperTileMap>tile_map9(TEXT("/Game/Assets/Tile/Tileset/Tilemap/Road_9"));
	TileMaps.push_back(tile_map9.Object);
	static ConstructorHelpers::FObjectFinder<UPaperTileMap>tile_map10(TEXT("/Game/Assets/Tile/Tileset/Tilemap/Road_10"));
	TileMaps.push_back(tile_map10.Object);

	TileMapComponents = CreateDefaultSubobject<UPaperTileMapComponent>(TEXT("TileMapComponents"));
	RootComponent = TileMapComponents;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->InitBoxExtent(FVector(700.0f, 32.0f, 1000.0f));
	BoxComponent->SetCollisionProfileName(TEXT("NoCollision"));
	BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComponent->SetGenerateOverlapEvents(true);
	BoxComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	BoxComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &AGCTile::OnOverlapBegin);
	BoxComponent->SetRelativeLocation(FVector(3200.0f, 0, -500.0f));
}

void AGCTile::BeginPlay()
{
	Super::BeginPlay();

	InterfaceGameMode = Cast<IInterfaceGameMode>(GetWorld()->GetAuthGameMode());

	int rage = (int)FMath::FRandRange(0.0f, (float)TileMaps.size()-1);
	TileMapComponents->SetTileMap(TileMaps[rage]);
}

void AGCTile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	int rage = (int)FMath::FRandRange(0.0f, (float)TileMaps.size() - 1);
	TileMapComponents->SetTileMap(TileMaps[rage]);

	FVector loc = this->GetActorLocation();
	float xLoc = InterfaceGameMode->IGetCurrentLocation();
	this->SetActorLocation(FVector(xLoc + 3490.0f, loc.Y, loc.Z));
	loc = this->GetActorLocation();
	InterfaceGameMode->ISetCurrentLocation(loc.X);
}
