/*
  15.12.2022
  ������� 11
  ������ 2, ��������
  Version 1.1 (16.12.2022)
  CPP-07
  Curios Ye Ye
*/

/* ��������� - ������ �����

����������: 

��������� ��������� ������� � ��������� �� �����, ������������ �� �������
������������ �������� ����������� ������ �� �������, � ������ ������������� ������ ������ ���������. ����� ���������� ������� �� ���� ������������ ����� - ����� ��� ����������.

��������� ����������� ���� ����� ������ ����� ���� ����� ����������� ���� ��������.

�������� ������� ��������� � ����� hints.h 

����������� � ��������:

1. � ����� � ��������� ���������� ������������ ����������� ����
*/

#include "hints.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
// #include <unistd.h>
#include <locale>
#include <codecvt>
#include <Windows.h>

int main() 
{
  
  setlocale(LC_ALL, "Russian");
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  system("chcp 1251");

  std::vector<jinx::WordQuest> Questions;  
  std::string fileName;
  int num = 0;
  
  std::system("CLS");
  std::cout << "---------------------------------------------------------------\n\n";
  std::cout << "                  >>> ���� ������-��! <<<\n\n";
  std::cout << "---------------------------------------------------------------\n\n";
  std::cout << "> ������� �������� ����� � ��������� (def: quest.txt)\n: ";
  std::cin >> fileName;
  
  num = jinx::get_quests_amount(fileName);

  std::cout << "> ���������� ������������ �������� ����� " << num << std::endl;

  for (int i = 1; i <= num; ++i)
    {
      jinx::WordQuest temp;
      // temp = temp.make_quest(fileName, i);
      temp.questWord = jinx::read_word_outside(fileName, i);
      temp.hintsList = jinx::read_hints_outside(fileName, i);
      temp.numberOfHints = jinx::get_number_of_hints_outside(fileName, i);
      
      Questions.push_back(temp);
    } // END OF for (int i = 1; i <= num; ++i)

  // --------------- ������� ���� ���� -----------------------------------

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

  // Exit line - �����
  std::string playerLineExit = "�����";
  // Exit line - ��
  std::string playerLineYes = "��";
  // Exit line - ���
  std::string playerLineNo = "���";
   // Exit line - �
  std::string playerLineN = "�";
   // Exit line - �
  std::string playerLineY = "�";  

  while (gameContinue)
    {      
      std::system("CLS");
      std::cout << "---------------------------------------------------------------\n\n";
      std::cout << "                  >>> ���� ������-��! <<<\n\n";
      std::cout << "� �������� ���� � ��� ����� 7 ���������, ������ ������������: " << hintCount << "\n\n";
      std::cout << "---------------------------------------------------------------\n\n";

      gameToken = ( rand() % ( num + 1 ) );
      if (gameToken == 0)
      gameToken+= 1;

      gotWordRight = false;
      surrenderWithExit = false;
      hintCount = 0;

      int wordLength = Questions[gameToken -1].questWord.length();

      std::cout << "\n����� �" << (gameToken);
      std::cout << "\n\n�������� �����, ������ �����: " << wordLength << "\n\n";

      do
        {
          std::cin >> playerInput;
          if ( playerInput == ( Questions[gameToken -1].questWord) )
          {
            std::cout << "����������! �� ������� ����� " << Questions[gameToken -1].questWord << " ����������� " 
                      << hintCount << " ���������.\n\n";
            gotWordRight = true;
          } else // end (playerInput == Questions[gameToken -1].questWord)
          {
            if (hintCount < Questions[gameToken - 1].numberOfHints)
            {
              std::cout << "�� �����. ��������� � " << (hintCount + 1) << ": " <<  Questions[gameToken -1].hintsList[hintCount] 
                        << std::endl;
              hintCount++;
            } 
            else
            {
              if ( !playerInput.compare(playerLineExit) )
              {
                gotWordRight = true;
                surrenderWithExit = true;
              } // END if (playerInput == std::to_string("�����"))
              std::cout << "�� �����. ��������� ���������! �� ����� ��� ������!\n������� '�����' ���� �������!\n" << std::endl;
            } // END ELSE
          } // END ELSE
        } while (!gotWordRight);
      
      do {

          if (!surrenderWithExit)
          {
            std::cout << "�� ������� �����, ������ ����������? (� (��) / � (���))\n>";
          }
          else
          {
            std::cout << "� ������ ��� ������, ������ ����������? (� (��) / � (���))\n>";
          }
      
          std::cin >> keyChar;

        } while ( keyChar.compare(playerLineY) && keyChar.compare(playerLineN) && keyChar.compare(playerLineYes) && keyChar.compare(playerLineNo) ); 

      if ( !keyChar.compare(playerLineN) || !keyChar.compare(playerLineNo) ) 
      {
        gameContinue = false;
      } 
      
    } // END OF while (gameContinue)

 
  // -------------------- ���������� ������ ------------------

   
    std::system("CLS");
    std::cout << "---------------------------------------------------------------\n\n";
    std::cout << "                  >>> ���� ������-��! <<<\n\n";
    std::cout << "---------------------------------------------------------------\n\n";
    std::cout << "                        ���� ��������" << std::endl;

    Questions.clear();

    system("pause");
  
  return 0;
} // END OF int main() 