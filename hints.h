#ifndef HINTSH
#define HINTSH

#include <string>
#include <vector>
#include <locale>
#include <codecvt>
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

#endif /* END OF HINTSH */