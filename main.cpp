/*  
  Version 1.3 simplified
  Curios Ye Ye
*/

/* ПРОГРАММА - УГАДАЙ СЛОВО

Назначение: 

Программа выгружает вопросы и подсказки из файла, указываемого из консоли
Пользователю выдаются выгруженные задачи по порядку, в случае неправильного ответа даются подсказки. После угадывания каждого из слов предлагается выбор - выйти или продолжить.

Программа завершается либо после выбора выйти либо после исчеорпания всех вопросов.

Ограничения и проблемы:

1. В файле с вопросами необходимо использовать специальные тэги

*/

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <locale>
#include <codecvt>

/* HINTS.H CONTENTS --------------------------------- */

// #include "nowide/args.hpp"
#include "nowide/fstream.hpp"
#include "nowide/iostream.hpp"
#include "nowide/config.hpp"

namespace jinx // ---------------------------------------------------------------
{

/*
Функция чтения файла с вопросами и подсчёта количества вопросов в файле
Аттрибуты:
1. std::wstring - строка с именем файла
Возвращаемое значение:
1. int, число найденных слов
*/
int get_quests_amount(std::string);

/*

Класс задачи содержащий слово, подсказки, количество подсказок и
основные функции для генерации класса задачи.

Публичные аттрибуты:

1. std::wstring questWord - Квестовое слово, переменная
2. std::vector<std::wstring> hintsList - Массив со списком подсказок
3. int numberOfHints - Число содержащее количество считанных подсказок для текущего слова

Публичные функции: 

1. WordQuest make_quest(std::wstring, int) - функция генерации класса

*/
class WordQuest
{

private: // ------------- PRIVATE PART -------------------------

  /* Выгружает из файла слово для угадывания,
  Аттрибуты функции:
    1. Наименование файла для чтения записей
    2. Порядковый номер вопроса в файле
  Возвращает:
    1. Значение типа std::wstring
  */
  std::wstring read_word(std::string, int);

  /* Выгружает из файла подсказки для угадывания,
  Аттрибуты функции:
    1. Наименование файла для чтения записей
    2. Порядковый номер вопроса в файле
  */
  std::vector<std::wstring> read_hints(std::string, int);

  /* Получить количество подсказок для текущего слова,
 Аттрибуты функции:
    1. Наименование файла для чтения записей
    2. Порядковый номер вопроса в файле

  ВЕРСИЯ В КЛАССЕ
  */
  int get_number_of_hints(std::string, int);  

public: // ---------- OPEN PART ---------------------------------

  std::wstring questWord;                  // Квестовое слово для угадывания
  std::vector<std::wstring> hintsList;     // Массив подсказок
  int numberOfHints;                       // Количество подсказок

  /* Генерация класса для угадывания слова,
    Аттрибуты функции:
    1. Наименование файла для чтения записей
    2. Порядковый номер вопроса в файле
  */
  WordQuest make_quest(std::string, int);

  // Constructor
  WordQuest()
   {

     // CONVERTER STRING-2-WSTRING AND BACK
   std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    // std::string narrow = converter.to_bytes(wide_utf16_source_string);
    // std::wstring wide = converter.from_bytes(narrow_utf8_source_string);
     
     questWord = converter.from_bytes("ложка");
     numberOfHints = 7;

     for (int i = 0; i < 7; ++i) // MAKE ARRAY
       {
         hintsList.push_back( converter.from_bytes(("hint 1/" + std::to_string(numberOfHints) + 
                             " тест - слово ложка")) );
       } // END IF
   } // END of Constructor

  // Destructor
  ~WordQuest()
  {
      hintsList.clear();
  } // END of Destructor

}; /* END OF CLASS WordQuest */

/* Выгружает из файла слово для угадывания
Аттрибуты функции:
1. Наименование файла для чтения записей
2. Порядковый номер вопроса в файле
Возвращает:
1. Значение типа std::wstring

ВЕРСИЯ ВНЕ КЛАССА
*/
std::wstring read_word_outside(std::string, int);

/* Выгружает из файла подсказки для угадывания
Аттрибуты функции:
1. Наименование файла для чтения записей
2. Порядковый номер вопроса в файле

ВЕРСИЯ ВНЕ КЛАССА
*/
std::vector<std::wstring> read_hints_outside(std::string, int);

/* Получить количество подсказок для текущего слова,
 Аттрибуты функции:
    1. Наименование файла для чтения записей
    2. Порядковый номер вопроса в файле

  ВЕРСИЯ ВНЕ КЛАССА
  */
int get_number_of_hints_outside(std::string, int);

} /* END OF JINX NAMESPACE ------------------------------------------------------ */


/* END OF HINTS.H CONTENTS -------------------------- */

int main() /* MAIN FUNCTION -------------------------------------------------------*/
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

/* HINTS.CPP CONTENTS --------------------------------- */


// CONVERTER STRING-2-WSTRING AND BACK
  // std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  // std::string narrow = converter.to_bytes(wide_utf16_source_string);
  // std::wstring wide = converter.from_bytes(narrow_utf8_source_string);

namespace jinx // ---------------------------------------------------------------
{

/* Функция чтения файла с вопросами и подсчёта количества вопросов в файле */
int get_quests_amount(std::string fileName)
{
  
  nowide::ifstream file;
  file.open(fileName, std::ios_base::in|std::ios_base::out);
    
  if (file.is_open()) 
  {

    int counter = 0;
    std::string fileline;
    std::string qWord = "questWord";

    file.seekg(0, file.beg);

    while (getline(file,fileline))
    {
      if (fileline.find(("<"+ qWord + " ")) != std::string::npos)
      {
        counter++;
      }
      
    } // END OF while (getline(file,fileline))
    file.clear();
    file.seekg(0, file.beg);
    return counter;

  } // END OF if (file.is_open())
  else
  {
    std::cerr << "ОШИБКА ЧТЕНИЯ ФАЙЛА!" << std::endl;
    throw std::string("ERROR READING FILE");
  }
  file.clear();
  file.seekg(0, file.beg);
  file.close();

  return -1;
  
} /* END OF get_quests_amount() ----------------------------------------------*/

/* Выгружает из файла слово для угадывания */
std::wstring read_word(std::string fileName, int num)
{

  nowide::ifstream file;
  file.open(fileName, std::ios_base::in|std::ios_base::out);

  if (file.is_open()) 
  {
    std::string fileline;
    std::string qWord = "questWord";

    file.seekg(0, file.beg);
      
    while (getline(file,fileline))
    {
      if (fileline.find(("<"+ qWord + " " + std::to_string(num) + ">")) != std::string::npos)
      {        
        std::string::size_type i = fileline.find("<" + qWord + std::to_string(num) + ">");

        if (i != std::string::npos)
           fileline.erase(i, ("<" + qWord + " " + std::to_string(num) + ">").length());

        std::string::size_type j = fileline.find("</" + qWord + ">");

        if (i != std::string::npos)
           fileline.erase(i, ("</" + qWord + ">").length());
               
      } /* (fileline.find(("<"+ qWord + " " + std::to_wstring(num) + ">")) 
                                   != std::string::npos) */

    } /* END while (getline(file,fileline)) */
    
    file.seekg(0, file.beg);

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    
    return converter.from_bytes(fileline);
      
  } /* END if (file.is_open() */
  else
  {
      std::cerr << "ОШИБКА ЧТЕНИЯ ФАЙЛА!" << std::endl;
      throw std::string("ERROR READING FILE");
    
  } /* END else */
  
    file.close();
  
} /* END OF read_word() --------------------------------------------------------*/

/* Выгружает из файла подсказки для угадывания */
std::vector<std::wstring> read_hints(std::string fileName, int num)
{
  
  nowide::ifstream file;
  file.open(fileName, std::ios_base::in|std::ios_base::out);

    
  if (file.is_open()) 
  {
    std::string fileline;
    std::string qWord = "questHint";
    
    std::vector<std::wstring> hintLines;

    file.clear();
    file.seekg(0, file.beg);
      
    while (getline(file,fileline))
    {
      if (fileline.find(("<"+ qWord + " " + std::to_string(num) + ">")) != std::string::npos)
      {        
        std::string::size_type i = fileline.find("<" + qWord + std::to_string(num) + ">");

        if (i != std::string::npos)
        {
          fileline.erase(i, ("<"+ qWord + " " + std::to_string(num) + ">").length());
        } // END if (i != std::wstring::npos)

        std::string::size_type j = fileline.find("</" + qWord + ">");

        if (j != std::string::npos)
        {
          fileline.erase(j, ("</" + qWord + ">").length());
        } // END if (j != std::wstring::npos)

        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        hintLines.push_back(converter.from_bytes(fileline));
        
      } /* END if (fileline == ("[questword " + std::to_string(num) + "]")) */

    } /* END while (getline(file,fileline)) */
    file.seekg(0, file.beg);
    return hintLines;
      
  } /* END if (file.is_open() */
  else
  {
      std::cerr << "ОШИБКА ЧТЕНИЯ ФАЙЛА!" << std::endl;
      throw std::string("ERROR READING FILE");
    
  } /* END else */
  
    file.seekg(0, file.beg);
    file.close();
  
} /* END OF readHints() */

/* Выгружает из файла слово для угадывания */
// ВЕРСИЯ ВНЕ КЛАССА
std::wstring read_word_outside(std::string fileName, int num)
{
  /* пример строки со словом 

  <questWord 1>брусника</questWord>

  */
  
  nowide::ifstream file; 
  
  file.open(fileName, std::ios_base::in|std::ios_base::out);    
  if (file.is_open()) 
  {      
    std::string fileline;
    std::string qWord = "questWord";
    std::string startWord = "<"+ qWord + " " + std::to_string(num) + ">" ;
    std::string endWord = "</"+ qWord + ">";

    // std::cout << "<"+ qWord + " " + std::to_string(num) + ">" << std::endl;

    file.seekg(0, file.beg);    
      
    while (getline(file,fileline))
    {      
      if (fileline.find(startWord) != std::string::npos)
      {        
        std::string::size_type i = fileline.find(startWord);

        if (i != std::string::npos)
           fileline.erase(i, (startWord).length());

        std::string::size_type j = fileline.find(endWord);

        if (j != std::string::npos)
           fileline.erase(j, (endWord).length());

        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        return converter.from_bytes(fileline);
               
      } /* END if (fileline.find(startWord) != std::wstring::npos) */

    } /* END while (getline(file,fileline)) */    

    return 0;
      
  } /* END if (file.is_open() */
  else
  {
      std::cerr << "ОШИБКА ЧТЕНИЯ ФАЙЛА!" << std::endl;
      throw std::string("ERROR READING FILE");
    
  } /* END else */
  
    file.seekg(0, file.beg);
    file.close();
  
} /* END OF read_word_outside() ---------------------------------------------*/

/* Выгружает из файла подсказки для угадывания */
// ВЕРСИЯ ВНЕ КЛАССА
std::vector<std::wstring> read_hints_outside(std::string fileName, int num)
{  
  nowide::ifstream file;
  file.open(fileName, std::ios_base::in|std::ios_base::out);  
    
  if (file.is_open()) 
  {
    std::string fileline;
    std::string qWord = "questHint";
    std::string startWord = "<"+ qWord + " " + std::to_string(num) + ">" ;
    std::string endWord = "</"+ qWord + ">";
    
    std::vector<std::wstring> hintLines;
    file.clear();
    file.seekg(0, file.beg);
      
    while (getline(file,fileline))
    {
      if (fileline.find(startWord) != std::string::npos)
      {     
        std::string::size_type i = fileline.find(startWord);

        if (i != std::string::npos)
        {
          fileline.erase(i, startWord.length());
        } // END if (i != std::string::npos)        

        std::string::size_type j = fileline.find(endWord);

        if (j != std::string::npos)
        {
          fileline.erase(j, endWord.length());
        } // END if (j != std::string::npos)

        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        hintLines.push_back(converter.from_bytes(fileline));
        
      } /* END  if (fileline.find(startWord) != std::wstring::npos) */

    } /* END while (getline(file,fileline)) */
    
    file.seekg(0, file.beg);
    return hintLines;
      
  } /* END if (file.is_open() */
  else
  {
      std::cerr << "ОШИБКА ЧТЕНИЯ ФАЙЛА!" << std::endl;
      throw std::string("ERROR READING FILE");
    
  } /* END else */
  
    file.close();
  
} /* END OF read_hints_outside() -------------------------------------------------*/

/* Получить количество подсказок для текущего слова,
 Аттрибуты функции:
    1. Наименование файла для чтения записей
    2. Порядковый номер вопроса в файле

  ВЕРСИЯ В КЛАССE
  */
int get_number_of_hints(std::string fileName, int num)
{
  nowide::ifstream file;
  file.open(fileName, std::ios_base::in|std::ios_base::out);  
    
  if (file.is_open()) 
  {
    std::string fileline;
    std::string qWord = "questHint";
    std::string startWord = "<"+ qWord + " " + std::to_string(num) + ">" ;
    std::string endWord = "</"+ qWord + ">";
    int counter = 0;
    
    file.clear();
    file.seekg(0, file.beg);
      
    while (getline(file,fileline))
    {
      if (fileline.find(startWord) != std::string::npos)
      {     
        counter++;       
        
      } /* END  if (fileline.find(startWord) != std::wstring::npos) */

    } /* END while (getline(file,fileline)) */    
    
    file.seekg(0, file.beg);
    return counter;

  } /* END if (file.is_open() */
  else
  {
    std::cerr << "ОШИБКА ЧТЕНИЯ ФАЙЛА!" << std::endl;
    throw std::string("ERROR READING FILE");
    
  } /* END else */
  
  file.close();
} // END OF int get_number_of_hints(std::wstring, int) -----------------------------

/* Получить количество подсказок для текущего слова,
 Аттрибуты функции:
    1. Наименование файла для чтения записей
    2. Порядковый номер вопроса в файле

  ВЕРСИЯ ВНЕ КЛАССА
  */
  int get_number_of_hints_outside(std::string fileName, int num)
{
    nowide::ifstream file;
  file.open(fileName, std::ios_base::in|std::ios_base::out);  
    
  if (file.is_open()) 
  {
    std::string fileline;
    std::string qWord = "questHint";
    std::string startWord = "<"+ qWord + " " + std::to_string(num) + ">" ;
    std::string endWord = "</"+ qWord + ">";
    int counter = 0;
    
    file.clear();
    file.seekg(0, file.beg);
      
    while (getline(file,fileline))
    {
      if (fileline.find(startWord) != std::string::npos)
      {     
        counter++;       
        
      } /* END  if (fileline.find(startWord) != std::wstring::npos) */

    } /* END while (getline(file,fileline)) */    
    
    file.seekg(0, file.beg);
    return counter;
    
  } /* END if (file.is_open() */
  else
  {
    std::cerr << "ОШИБКА ЧТЕНИЯ ФАЙЛА!" << std::endl;
    throw std::string("ERROR READING FILE");
    
  } /* END else */
  
  file.close();
} // END OF int get_number_of_hints_outside(std::wstring, int) ----------------------

  /* Генерация класса для угадывания слова */
jinx::WordQuest make_quest(std::string fileName, int num)
{
  jinx::WordQuest newQuest;

  newQuest.questWord = jinx::read_word_outside(fileName, num);
  newQuest.hintsList = jinx::read_hints_outside(fileName, num);
  newQuest.numberOfHints = jinx::get_number_of_hints_outside(fileName, num);
  
  return newQuest;
} /* END OF make_quest() -------------------------------------------------------*/


} /* END OF JINX NAMESPACE ------------------------------------------------------ */


/* END OF HINTS.CPP CONTENTS -------------------------- */