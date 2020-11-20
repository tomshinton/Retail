// Tom Shinton - Retail 2020

#include "Retail/Public/RetailGameModeBase.h"

#include "Retail/Public/RetailPlayer.h"
#include "Retail/Public/RetailPlayerController.h"
#include "Retail/Public/RetailGameState.h"

ARetailGameModeBase::ARetailGameModeBase()
{
	PlayerControllerClass = ARetailPlayerController::StaticClass();
	DefaultPawnClass = ARetailPlayer::StaticClass();
	GameStateClass = ARetailGameState::StaticClass();
}
