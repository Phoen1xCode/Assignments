#ifndef DAILYASSISTANT_H
#define DAILYASSISTANT_H

#include "../include/Course.h"
#include "../include/Memo.h"
#include "../include/Homework.h"
#include "../include/Schedule.h"

namespace DailylifeAssistant {

	class DailyAssistant {
	public:
		void mainDailylifeAssistant();

        void MainCourse();

        void MainMemos();

        void MainHomework();

        void MainSchedule();
	};

}
#endif