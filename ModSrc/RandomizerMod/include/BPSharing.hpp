/**
 * @author Yaranorgoth
 * @brief Share information between C++ functions and UE Blueprint functions
 */

#pragma once

using namespace RC;
using namespace RC::Unreal;


namespace BPSharing {
	/**
	 * @brief Detect when a specific function name is called from UE Blueprints
	 * @param Context: The optional UE Object
	 * @param Stack: All information on the stacked caller (function, parameters, outputs, ...)
	 * @param RESULT_DECL: The optional output value (must be named exactly "ReturnValue" in the Blueprints)
	 */
	void ManageHook([[maybe_unused]] Unreal::UObject* Context, Unreal::FFrame& Stack, [[maybe_unused]] void* RESULT_DECL);
	
	/**
	 * @brief Set references to Blueprint elements related to the Actor class "BP_ItemManager_C"
	 * @note All references break at game reload, then set to NULL when the BP function "GameReloadedCpp" fires
	 */
	void SetBPObjects();
}
