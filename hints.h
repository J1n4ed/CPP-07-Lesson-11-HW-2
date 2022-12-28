#ifndef HINTSH
#define HINTSH

#include <string>
#include <vector>
#include <locale>
#include <codecvt>
// #include "nowide/args.hpp"
// #include "nowide/fstream.hpp"
// #include "nowide/iostream.hpp"
// #include "nowide/config.hpp"

namespace jinx // ---------------------------------------------------------------
{

/*
������� ������ ����� � ��������� � �������� ���������� �������� � �����
���������:
1. std::string - ������ � ������ �����
������������ ��������:
1. int, ����� ��������� ����
*/
int get_quests_amount(std::string);

/*

����� ������ ���������� �����, ���������, ���������� ��������� �
�������� ������� ��� ��������� ������ ������.

��������� ���������:

1. std::string questWord - ��������� �����, ����������
2. std::vector<std::string> hintsList - ������ �� ������� ���������
3. int numberOfHints - ����� ���������� ���������� ��������� ��������� ��� �������� �����

��������� �������: 

1. WordQuest make_quest(std::string, int) - ������� ��������� ������

*/
class WordQuest
{

private: // ------------- PRIVATE PART -------------------------

  /* ��������� �� ����� ����� ��� ����������,
  ��������� �������:
    1. ������������ ����� ��� ������ �������
    2. ���������� ����� ������� � �����
  ����������:
    1. �������� ���� std::string
  */
  std::string read_word(std::string, int);

  /* ��������� �� ����� ��������� ��� ����������,
  ��������� �������:
    1. ������������ ����� ��� ������ �������
    2. ���������� ����� ������� � �����
  */
  std::vector<std::string> read_hints(std::string, int);

  /* �������� ���������� ��������� ��� �������� �����,
 ��������� �������:
    1. ������������ ����� ��� ������ �������
    2. ���������� ����� ������� � �����

  ������ � ������
  */
  int get_number_of_hints(std::string, int);  

public: // ---------- OPEN PART ---------------------------------

  std::string questWord;                  // ��������� ����� ��� ����������
  std::vector<std::string> hintsList;     // ������ ���������
  int numberOfHints;                       // ���������� ���������

  /* ��������� ������ ��� ���������� �����,
    ��������� �������:
    1. ������������ ����� ��� ������ �������
    2. ���������� ����� ������� � �����
  */
  WordQuest make_quest(std::string, int);

  // Constructor
  WordQuest()
   {

     // CONVERTER STRING-2-STRING AND BACK
     //std::string_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    // std::string narrow = converter.to_bytes(wide_utf16_source_string);
    // std::string wide = converter.from_bytes(narrow_utf8_source_string);
     
     questWord = "�����";
     numberOfHints = 7;

     for (int i = 0; i < 7; ++i) // MAKE ARRAY
       {
         hintsList.push_back( ("hint 1/" + std::to_string(numberOfHints) + " ���� - ����� �����") );
       } // END IF
   } // END of Constructor

  // Destructor
  ~WordQuest()
  {
      hintsList.clear();
  } // END of Destructor

}; /* END OF CLASS WordQuest */

/* ��������� �� ����� ����� ��� ����������
��������� �������:
1. ������������ ����� ��� ������ �������
2. ���������� ����� ������� � �����
����������:
1. �������� ���� std::string

������ ��� ������
*/
std::string read_word_outside(std::string, int);

/* ��������� �� ����� ��������� ��� ����������
��������� �������:
1. ������������ ����� ��� ������ �������
2. ���������� ����� ������� � �����

������ ��� ������
*/
std::vector<std::string> read_hints_outside(std::string, int);

/* �������� ���������� ��������� ��� �������� �����,
 ��������� �������:
    1. ������������ ����� ��� ������ �������
    2. ���������� ����� ������� � �����

  ������ ��� ������
  */
int get_number_of_hints_outside(std::string, int);

} /* END OF JINX NAMESPACE ------------------------------------------------------ */

#endif /* END OF HINTSH */