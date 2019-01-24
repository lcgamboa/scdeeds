#ifndef CPWINDOW1 
#define CPWINDOW1

#include<lxrad.h>

class CPWindow1:public CPWindow
{
  public:
//lxrad automatic generated block start, don't edit below!
  /*#Controls*/
  CMenu menu1;
  CStyledText styledtext1;
  CPMenu menu1_File;
  CPMenu menu1_Edit;
  CPMenu menu1_Build;
  CPMenu menu1_Options;
  CPMenu menu1_Help;
  CItemMenu menu1_File_New;
  CItemMenu menu1_File_Open;
  CItemMenu menu1_File_Save;
  CItemMenu menu1_File_SaveAs;
  CItemMenu menu1_File_Exit;
  CItemMenu menu1_Build_Compile;
  CItemMenu menu1_Build_RuninDeeds;
  CItemMenu menu1_Options_McEPath;
  CItemMenu menu1_Help_Contents;
  CItemMenu menu1_Help_Examples;
  CItemMenu menu1_Help_About;
  CFileDialog filedialog1;
  /*#Events*/
  void _EvOnCreate(CControl * control);
  void _EvOnDestroy(CControl * control);
  void _EvOnShow(CControl * control);
  void menu1_File_New_EvMenuActive(CControl * control);
  void menu1_File_Open_EvMenuActive(CControl * control);
  void menu1_File_Save_EvMenuActive(CControl * control);
  void menu1_File_SaveAs_EvMenuActive(CControl * control);
  void menu1_File_Exit_EvMenuActive(CControl * control);
  void menu1_Build_Compile_EvMenuActive(CControl * control);
  void menu1_Build_RuninDeeds_EvMenuActive(CControl * control);
  void menu1_Options_McEPath_EvMenuActive(CControl * control);
  void menu1_Help_Contents_EvMenuActive(CControl * control);
  void menu1_Help_Examples_EvMenuActive(CControl * control);
  void menu1_Help_About_EvMenuActive(CControl * control);
  void filedialog1_EvOnClose(const int retId);

  /*#Others*/
  CPWindow1(void);
//lxrad automatic generated block end, don't edit above!
  
  void saveprefs(String name, String value);
  void Configure(CControl * control, const char * home);
  
  String P_DeedsMCE;
  String P_scc8080;
  String P_8085asm;
  String P_sc2deeds;
  String P_filename;
  
  String OFilter;
  String OFilename;        
  
  CStringList prefs;
};

extern CPWindow1 Window1 ;

#endif /*#CPWINDOW1*/

