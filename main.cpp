#include "PasswordManagement/include/PasswordManager.h"
#include "ScheduleManagement/include/DailyAssistant.h"
#include "MoneyManagement/include/submain.h"

#include <cstdlib>
#include <vector>
#include <string>

std::vector<std::string> function_selection = {" 1.收支管理 "," 2.日程管理 "," 3.密码管理 "," 4.退出     "};
int main() {
    while(true){
        system("cls");
        int main_selection = 1;
        finance::help_selection(main_selection, function_selection);
        system("cls");
        switch (main_selection) {
            case 1: {
                finance::submain();
                break;
            }
            case 2: {

                DailylifeAssistant::DailyAssistant l;
                l.mainDailylifeAssistant();
                break;
            }
            case 3: {
                // 密码管理器实现部分
                PasswordManagement::PasswordManager passwordManager;
                if (!passwordManager.loginPasswordManagement())
                    return 0;
                else
                    passwordManager.managePasswords();
                break;
            }
            case 4: {
               break;
            }
        }
        if(main_selection == 4)
            break;
    }
    return 0;
}