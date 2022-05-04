#include "pch-il2cpp.h"
#include "QuestManager.h"

#include <helpers.h>
#include <cheat/events.h>

namespace cheat::feature
{

	QuestManager::QuestManager() : Feature()
	{
		//events::GameUpdateEvent += MY_METHOD_HANDLER(QuestManager::OnGameUpdate);
	}

	const FeatureGUIInfo& QuestManager::GetGUIInfo() const
	{
		static const FeatureGUIInfo info{ "QuestList", "Debug", true };
		return info;
	}

	void QuestManager::DrawMain()
	{
		if (ImGui::CollapsingHeader("QuestManager", ImGuiTreeNodeFlags_None))
		{
			uintptr_t QuestModule = il2cppi_get_base_address();
			//DO_TYPEDEF(0x0B37E7D0, ABOHKHIKBDI);
			QuestModule = readmem<uintptr_t>(QuestModule + 0xB37E7D0);
			if (QuestModule > 0)
			{
				QuestModule = readmem<uintptr_t>(QuestModule + 0xA0);
				if (QuestModule > 0) {
					QuestModule = readmem<uintptr_t>(QuestModule + 0x30);
					if (QuestModule > 0)
					{
						QuestModule = readmem<uintptr_t>(QuestModule + 0x28);
						int QuestNumver = readmem<int>(QuestModule + 0x18);
						auto clipSize = min(3, 3) + 1;
						static ImGuiTableFlags flags =
							ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable
							| ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_NoBordersInBody
							| ImGuiTableFlags_ScrollY;
						if (ImGui::BeginTable("QuestTable", 3, flags, ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * clipSize), 0.0f))
						{
							ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed, 0.0f, 3);
							ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed, 0.0f, 3);
							ImGui::TableSetupColumn("NowObjective", ImGuiTableColumnFlags_WidthFixed, 0.0f, 3);
							ImGui::TableSetupScrollFreeze(0, 1);
							ImGui::TableHeadersRow();

							for (size_t i = 0; i < QuestNumver; i++) {
								uintptr_t QuestObject = readmem<uintptr_t>(QuestModule + i * 0x8 + 0x20);
								if ((QuestObject > 0) && readmem<uintptr_t>(QuestObject + 0x20))
								{

									QuestObject = readmem<uintptr_t>(QuestObject + 0x20);
									bool Execution = readmem<bool>(QuestObject + 0x7C);
									int QuestID = readmem<int>(QuestObject + 0x10);
									ImGui::PushID(QuestID);
									ImGui::TableNextRow();
									ImGui::TableNextColumn();
									s_Quest Temp;
									Temp.QuestID = QuestID;
									Temp.QuestOBJ = QuestObject;
									std::string QuestName = il2cppi_to_string(GetQuestName(&Temp));
									std::string ObjectiveName = GetQuestObjective(QuestID);
									ImGui::Text("%d", QuestID);
									ImGui::TableNextColumn();
									ImGui::Text("%s", QuestName.c_str());
									ImGui::TableNextColumn();
									ImGui::Text("%s", ObjectiveName.c_str());
									ImGui::PopID();
								}
							}
							ImGui::EndTable();
						}
					}
				}
			}
		}
		
	}

	bool QuestManager::NeedStatusDraw() const
	{
		return true;
	}

	void QuestManager::DrawStatus()
	{
	}

	QuestManager& QuestManager::GetInstance()
	{
		static QuestManager instance;
		return instance;
	}
	app::String* QuestManager::GetQuestName(s_Quest* QuestObject) {
		try
		{
			uintptr_t UserAssembly = il2cppi_get_base_address();
			typedef app::String* (*call_GetQuestName)(void* obj);
			call_GetQuestName getquestname = (call_GetQuestName)(UserAssembly + 0x26D9310);
			return getquestname(QuestObject);
		}
		catch (...)
		{
			return reinterpret_cast<app::String*>(il2cpp_string_new("Error"));
		}
	}
	app::String* QuestManager::GetQuestObjectiveName(void* QuestObjectiveObject) {
		try
		{
			uintptr_t UserAssembly = il2cppi_get_base_address();
			typedef app::String* (*call_GetQuestObjectiveName)(void* obj);
			call_GetQuestObjectiveName getquestname = (call_GetQuestObjectiveName)(UserAssembly + 0x220C200);
			return getquestname(QuestObjectiveObject);
		}
		catch (...)
		{
			return reinterpret_cast<app::String*>(il2cpp_string_new("Error"));
		}
	}



	//DO_APP_FUNC(0x029F2020, List_1_MoleMole_QuestProxy_ *, HHMJPCFFJJG_OFLACMDDLHB, (HHMJPCFFJJG * __this, uint32_t MHKDNJMKACM, MethodInfo * method));
	//Get Quest objectives
	std::string QuestManager::GetQuestObjective(uint32_t QuestID) {
		auto HHMJPCFFJJG = GET_SINGLETON(HHMJPCFFJJG);
		try
		{
			app::List_1_MoleMole_QuestProxy_* Test = app::HHMJPCFFJJG_OFLACMDDLHB(HHMJPCFFJJG, QuestID, nullptr);
			auto Objectives = TO_UNI_LIST(Test, app::QuestProxy*);
			auto v_Objective = Objectives->vec();
			for (auto ObjectiveObj : v_Objective)
			{
				if (ObjectiveObj->fields._inited)
				{
					std::string ObjectiveName = il2cppi_to_string(GetQuestObjectiveName((void*)&ObjectiveObj->fields));
					return ObjectiveName;
				}
			}
		}
		catch (...)
		{
		}
	}

}