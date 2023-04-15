// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Inventory/InventoryDataComponent/GS_InventoryDataComponent.h"

#include "Systems/Inventory/InventoryData.h"


UGS_InventoryDataComponent::UGS_InventoryDataComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGS_InventoryDataComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnDefaultItems();
}


void UGS_InventoryDataComponent::SpawnDefaultItems()
{
	if( !IsValid(ItemsToAddData) ) return;

	TArray<FItemInfo*> SpawnItems;
	ItemsToAddData->GetAllRows<FItemInfo>("GetItems", SpawnItems);

	for( const FItemInfo* ItemRow : SpawnItems )
	{
		AddItemToInventory(*ItemRow);
	}
}

int32 UGS_InventoryDataComponent::GetCurrentInventoryWeight()
{
	int32 CurrentWeight = 0;
	
	for( const auto& Item : Items )
	{
		CurrentWeight += Item.Weight;
	}

	return CurrentWeight;
}

void UGS_InventoryDataComponent::AddItemToInventory(const FItemInfo ItemInfo)
{
	const float CurrentWeight = GetCurrentInventoryWeight();
	
	if( CurrentWeight + ItemInfo.Weight > MaxWeight ) return;
	
	Items.Add(ItemInfo);

	OnInventoryChangedBind.Broadcast();
}

void UGS_InventoryDataComponent::RemoveItemFromInventory(const FItemInfo ItemInfo)
{
	Items.RemoveSingle(ItemInfo);

	OnInventoryChangedBind.Broadcast();
}




