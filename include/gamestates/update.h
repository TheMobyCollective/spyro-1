#ifndef __GAMESTATE_UPDATE_H
#define __GAMESTATE_UPDATE_H

/// @brief Updates level transition gems and text
void func_8002DA74(void);

/// @brief Main game loop update dispatcher, handles all gamestate logic
void GamestateUpdate(void);

void CheckMemcardsExist(void);
int func_80032AB0(void);

#endif // !__GAMESTATE_UPDATE_H
