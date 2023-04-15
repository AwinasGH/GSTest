// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "Systems/Inventory/InventoryData.h"


#include "GS_InventoryDataComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);


/*
 *	Primitive inventory class for testing widget
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GSTEST_API UGS_InventoryDataComponent : public UActorComponent
{
	GENERATED_BODY()

//constructor
public:

	UGS_InventoryDataComponent();

	
//c++ values
private:
	
	TArray<FItemInfo> Items;

//c++ methods
protected:

	virtual void BeginPlay() override;

//c++ methods
private:
	
	void SpawnDefaultItems();

//>>...........................................................................................................................................<<//


//Blueprint methods
public:

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		const TArray<FItemInfo>& GetItems() const { return Items; };

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		int32 GetCurrentInventoryWeight();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		virtual void AddItemToInventory(const FItemInfo ItemInfo);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		virtual void RemoveItemFromInventory(const FItemInfo ItemInfo);
	
//Blueprint values
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
		UDataTable* ItemsToAddData;	

	UPROPERTY(BlueprintAssignable, Category = "Inventory|EventsForBind")
		FOnInventoryChanged OnInventoryChangedBind;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
		int32 MaxWeight = 100;
};
