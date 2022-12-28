/*
  15.12.2022
  Занятие 11
  Работа 2, Угадайка
  Version 1.1 (16.12.2022)
  CPP-07
  Curios Ye Ye
*/

/* ПРОГРАММА - УГАДАЙ СЛОВО

Назначение: 

Программа выгружает вопросы и подсказки из файла, указываемого из консоли
Пользователю выдаются выгруженные задачи по порядку, в случае неправильного ответа даются подсказки. После угадывания каждого из слов предлагается выбор - выйти или продолжить.

Программа завершается либо после выбора выйти либо после исчеорпания всех вопросов.

Основные функции объявлены в файле hints.h 

Ограничения и проблемы:

1. В файле с вопросами необходимо использовать специальные тэги
*/

#include "hints.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <unistd.h>
#include <locale>
#include <codecvt>

int main() 
{

  // SetConsoleCP(1251);
  // SetConsoleOutputCP(1251);

  std::vector<jinx::WordQuest> Questions;  
  std::string fileName;
  int num = 0;
  
  std::system("clear");
  std::cout << "---------------------------------------------------------------\n\n";
  std::cout << "                  >>> Игра Угадай-ка! <<<\n\n";
  std::cout << "---------------------------------------------------------------\n\n";
  std::cout << "> Введите название файла с вопросами (def: quest.txt)\n: ";
  std::cin >> fileName;
  
  num = jinx::get_quests_amount(fileName);

  std::cout << "> Количество обнаруженных вопросов равно " << num << std::endl;

  for (int i = 1; i <= num; ++i)
    {
      jinx::WordQuest temp;
      // temp = temp.make_quest(fileName, i);
      temp.questWord = jinx::read_word_outside(fileName, i);
      temp.hintsList = jinx::read_hints_outside(fileName, i);
      temp.numberOfHints = jinx::get_number_of_hints_outside(fileName, i);
      
      Questions.push_back(temp);
    } // END OF for (int i = 1; i <= num; ++i)

  // --------------- ГЛАВНЫЙ ЦИКЛ ИГРЫ -----------------------------------

  bool gameContinue = true;
  bool gotWordRight = false;
  bool surrenderWithExit = false;
  int hintCount = 0;
  int gameToken = 1;
  std::string playerInput;
  srand(time(NULL));
  std::string keyChar;

  // CONVERTER STRING-2-WSTRING AND BACK
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  // std::string narrow = converter.to_bytes(wide_utf16_source_string);
  // std::wstring wide = converter.from_bytes(narrow_utf8_source_string);

  // Exit line - выход
  std::string playerLineExit = "выход";
  // Exit line - да
  std::string playerLineYes = "да";
  // Exit line - нет
  std::string playerLineNo = "нет";
   // Exit line - н
  std::string playerLineN = "н";
   // Exit line - д
  std::string playerLineY = "д";  

  while (gameContinue)
    {      
      std::system("clear");
      std::cout << "---------------------------------------------------------------\n\n";
      std::cout << "                  >>> Игра Угадай-ка! <<<\n\n";
      std::cout << "В процессе игры у вас будет 7 подсказок, сейчас использовано: " << hintCount << "\n\n";
      std::cout << "---------------------------------------------------------------\n\n";

      gameToken = ( rand() % ( num + 1 ) );
      if (gameToken == 0)
      gameToken+= 1;

      gotWordRight = false;
      surrenderWithExit = false;
      hintCount = 0;

      int wordLength = Questions[gameToken -1].questWord.length();

      nowide::cout << "\nСлово №" << (gameToken);
      nowide::cout << "\n\nУгадайте слово, длинна слова: " << wordLength << "\n\n";

      do
        {
          nowide::cin >> playerInput;
          if ( playerInput == ( converter.to_bytes(Questions[gameToken -1].questWord) ) )
          {
            std::cout << "Поздравляю! Вы угадали слово " << converter.to_bytes(Questions[gameToken -1].questWord) << " использовав " 
                      << hintCount << " подсказок.\n\n";
            gotWordRight = true;
          } else // end (playerInput == Questions[gameToken -1].questWord)
          {
            if (hintCount < Questions[gameToken - 1].numberOfHints)
            {
              nowide::cout << "Не верно. Подсказка № " << (hintCount + 1) << ": " << converter.to_bytes( Questions[gameToken -1].hintsList[hintCount] )
                        << std::endl;
              hintCount++;
            } 
            else
            {
              if ( !playerInput.compare(playerLineExit) )
              {
                gotWordRight = true;
                surrenderWithExit = true;
              } // END if (playerInput == std::to_wstring("выход"))
              std::cout << "Не верно. Подсказки кончились! Но может вам повезёт!\nВведите 'выход' если сдаётесь!\n" << std::endl;
            } // END ELSE
          } // END ELSE
        } while (!gotWordRight);
      
      do {

          if (!surrenderWithExit)
          {
            std::cout << "Вы угадали слово, будете продолжать? (д (да) / н (нет))\n>";
          }
          else
          {
            std::cout << "В другой раз повезёт, будете продолжать? (д (да) / н (нет))\n>";
          }
      
          nowide::cin >> keyChar;

        } while ( keyChar.compare(playerLineY) && keyChar.compare(playerLineN) && keyChar.compare(playerLineYes) && keyChar.compare(playerLineNo) ); 

      if ( !keyChar.compare(playerLineN) || !keyChar.compare(playerLineNo) ) 
      {
        gameContinue = false;
      } 
      
    } // END OF while (gameContinue)

 
  // -------------------- ЗАВЕРШЕНИЕ РАБОТЫ ------------------

   
    std::system("clear");
    std::cout << "---------------------------------------------------------------\n\n";
    std::cout << "                  >>> Игра Угадай-ка! <<<\n\n";
    std::cout << "---------------------------------------------------------------\n\n";
    std::cout << "                        ИГРА ОКОНЧЕНА" << std::endl;

    Questions.clear();
  
  return 0;
} // END OF int main() 