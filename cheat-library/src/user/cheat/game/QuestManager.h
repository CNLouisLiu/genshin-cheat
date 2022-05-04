#pragma once
namespace cheat::feature
{
	struct s_Quest
	{
		uint32_t  QuestID;
		uintptr_t  QuestOBJ;
	};
	class QuestManager : public Feature
	{
	public:
		static QuestManager& GetInstance();
		std::string GetQuestObjective(uint32_t QuestID);
		const FeatureGUIInfo& GetGUIInfo() const override;
		void DrawMain() override;
		virtual bool NeedStatusDraw() const override;
		void DrawStatus() override;
	private:
		std::map<std::string, std::string>QuestList;
		app::String* GetQuestName(s_Quest* QuestObject);
		app::String* GetQuestObjectiveName(void* QuestObjectiveObject);
		template<class T>
		static T readmem(uintptr_t add) {
			try
			{
				return *(T*)add;
			}
			catch (...)
			{
				return 0;
			}

		}
		QuestManager();
	};
}