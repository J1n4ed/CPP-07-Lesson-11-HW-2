#include <iostream>
#include <fstream>
#include "hints.h"
#include <string>
#include <vector>
#include <cstdlib>
#include <locale>
#include <codecvt>
  

namespace jinx // ---------------------------------------------------------------
{

/* Функция чтения файла с вопросами и подсчёта количества вопросов в файле */
int get_quests_amount(std::string fileName)
{
  
  std::ifstream file;
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
  
} /* END OF get_quests_amount() ----------------------------------------------*/

/* Выгружает из файла слово для угадывания */
std::string read_word(std::string fileName, int num)
{

  std::ifstream file;
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
               
      } /* (fileline.find(("<"+ qWord + " " + std::to_string(num) + ">")) 
                                   != std::string::npos) */

    } /* END while (getline(file,fileline)) */
    
    file.seekg(0, file.beg);
    
    return fileline;
      
  } /* END if (file.is_open() */
  else
  {
      std::cerr << "ОШИБКА ЧТЕНИЯ ФАЙЛА!" << std::endl;
      throw std::string("ERROR READING FILE");
    
  } /* END else */
  
    file.close();
  
} /* END OF read_word() --------------------------------------------------------*/

/* Выгружает из файла подсказки для угадывания */
std::vector<std::string> read_hints(std::string fileName, int num)
{
  
  std::ifstream file;
  file.open(fileName, std::ios_base::in|std::ios_base::out);

    
  if (file.is_open()) 
  {
    std::string fileline;
    std::string qWord = "questHint";
    
    std::vector<std::string> hintLines;

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
        } // END if (i != std::string::npos)

        std::string::size_type j = fileline.find("</" + qWord + ">");

        if (j != std::string::npos)
        {
          fileline.erase(j, ("</" + qWord + ">").length());
        } // END if (j != std::string::npos)

        hintLines.push_back(fileline);
        
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
std::string read_word_outside(std::string fileName, int num)
{
  /* пример строки со словом 

  <questWord 1>брусника</questWord>

  */
  
  std::ifstream file; 
  
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

        return fileline;
               
      } /* END if (fileline.find(startWord) != std::string::npos) */

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
std::vector<std::string> read_hints_outside(std::string fileName, int num)
{  
  std::ifstream file;
  file.open(fileName, std::ios_base::in|std::ios_base::out);  
    
  if (file.is_open()) 
  {
    std::string fileline;
    std::string qWord = "questHint";
    std::string startWord = "<"+ qWord + " " + std::to_string(num) + ">" ;
    std::string endWord = "</"+ qWord + ">";
    
    std::vector<std::string> hintLines;
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
        
        hintLines.push_back(fileline);
        
      } /* END  if (fileline.find(startWord) != std::string::npos) */

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
  std::ifstream file;
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
        
      } /* END  if (fileline.find(startWord) != std::string::npos) */

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
} // END OF int get_number_of_hints(std::string, int) -----------------------------

/* Получить количество подсказок для текущего слова,
 Аттрибуты функции:
    1. Наименование файла для чтения записей
    2. Порядковый номер вопроса в файле

  ВЕРСИЯ ВНЕ КЛАССА
  */
  int get_number_of_hints_outside(std::string fileName, int num)
{
    std::ifstream file;
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
        
      } /* END  if (fileline.find(startWord) != std::string::npos) */

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
} // END OF int get_number_of_hints_outside(std::string, int) ----------------------

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
