CPWindow1::CPWindow1(void)
{
//lxrad automatic generated block start, don't edit below!
  SetFOwner(this);
  SetClass(lxT("CPWindow"));
  SetName(lxT("window1"));
  SetTag(0);
  SetX(334);
  SetY(157);
  SetWidth(885);
  SetHeight(560);
  SetHint(lxT(""));
  SetEnable(1);
  SetVisible(1);
  SetColor(lxT("#000001"));
  SetPopupMenu(NULL);
  SetTitle(lxT("SCDeeds"));
  SetOverrideRedirect(0);
  EvOnCreate=EVONCREATE & CPWindow1::_EvOnCreate;
  EvOnDestroy=EVONDESTROY & CPWindow1::_EvOnDestroy;
  EvOnShow=EVONSHOW & CPWindow1::_EvOnShow;
  //menu1
  menu1.SetFOwner(this);
  menu1.SetClass(lxT("CMenu"));
  menu1.SetName(lxT("menu1"));
  menu1.SetTag(0);
  menu1.SetMenuItems(lxT("File,Edit,Build,Options,Help,"));
  CreateChild(&menu1);
  //styledtext1
  styledtext1.SetFOwner(this);
  styledtext1.SetClass(lxT("CStyledText"));
  styledtext1.SetName(lxT("styledtext1"));
  styledtext1.SetTag(0);
  styledtext1.SetX(6);
  styledtext1.SetY(5);
  styledtext1.SetWidth(864);
  styledtext1.SetHeight(512);
  styledtext1.SetHint(lxT(""));
  styledtext1.SetEnable(1);
  styledtext1.SetVisible(1);
  styledtext1.SetColor(lxT("#000001"));
  styledtext1.SetPopupMenu(NULL);
  styledtext1.SetReadOnly(0);
  CreateChild(&styledtext1);
  //menu1_File
  menu1_File.SetFOwner(this);
  menu1_File.SetClass(lxT("CPMenu"));
  menu1_File.SetName(lxT("menu1_File"));
  menu1_File.SetTag(0);
  menu1_File.SetText(lxT("File"));
  menu1_File.SetMenuItems(lxT("New,Open,Save,SaveAs,Exit,"));
  menu1.CreateChild(&menu1_File);
  //menu1_Edit
  menu1_Edit.SetFOwner(this);
  menu1_Edit.SetClass(lxT("CPMenu"));
  menu1_Edit.SetName(lxT("menu1_Edit"));
  menu1_Edit.SetTag(0);
  menu1_Edit.SetText(lxT("Edit"));
  menu1_Edit.SetMenuItems(lxT(""));
  //menu1.CreateChild(&menu1_Edit);
  //menu1_Build
  menu1_Build.SetFOwner(this);
  menu1_Build.SetClass(lxT("CPMenu"));
  menu1_Build.SetName(lxT("menu1_Build"));
  menu1_Build.SetTag(0);
  menu1_Build.SetText(lxT("Build"));
  menu1_Build.SetMenuItems(lxT("Compile,Run in Deeds,"));
  menu1.CreateChild(&menu1_Build);
  //menu1_Options
  menu1_Options.SetFOwner(this);
  menu1_Options.SetClass(lxT("CPMenu"));
  menu1_Options.SetName(lxT("menu1_Options"));
  menu1_Options.SetTag(0);
  menu1_Options.SetText(lxT("Options"));
  menu1_Options.SetMenuItems(lxT("McE Path,"));
  menu1.CreateChild(&menu1_Options);
  //menu1_Help
  menu1_Help.SetFOwner(this);
  menu1_Help.SetClass(lxT("CPMenu"));
  menu1_Help.SetName(lxT("menu1_Help"));
  menu1_Help.SetTag(0);
  menu1_Help.SetText(lxT("Help"));
  menu1_Help.SetMenuItems(lxT("Contents,Examples,About,"));
  menu1.CreateChild(&menu1_Help);
  //menu1_File_New
  menu1_File_New.SetFOwner(this);
  menu1_File_New.SetClass(lxT("CItemMenu"));
  menu1_File_New.SetName(lxT("menu1_File_New"));
  menu1_File_New.SetTag(0);
  menu1_File_New.SetText(lxT("New"));
  menu1_File_New.SetEnable(1);
  menu1_File_New.SetSubMenu(NULL);
  menu1_File_New.EvMenuActive=EVMENUACTIVE & CPWindow1::menu1_File_New_EvMenuActive;
  menu1_File.CreateChild(&menu1_File_New);
  //menu1_File_Open
  menu1_File_Open.SetFOwner(this);
  menu1_File_Open.SetClass(lxT("CItemMenu"));
  menu1_File_Open.SetName(lxT("menu1_File_Open"));
  menu1_File_Open.SetTag(0);
  menu1_File_Open.SetText(lxT("Open"));
  menu1_File_Open.SetEnable(1);
  menu1_File_Open.SetSubMenu(NULL);
  menu1_File_Open.EvMenuActive=EVMENUACTIVE & CPWindow1::menu1_File_Open_EvMenuActive;
  menu1_File.CreateChild(&menu1_File_Open);
  //menu1_File_Save
  menu1_File_Save.SetFOwner(this);
  menu1_File_Save.SetClass(lxT("CItemMenu"));
  menu1_File_Save.SetName(lxT("menu1_File_Save"));
  menu1_File_Save.SetTag(0);
  menu1_File_Save.SetText(lxT("Save"));
  menu1_File_Save.SetEnable(1);
  menu1_File_Save.SetSubMenu(NULL);
  menu1_File_Save.EvMenuActive=EVMENUACTIVE & CPWindow1::menu1_File_Save_EvMenuActive;
  menu1_File.CreateChild(&menu1_File_Save);
  //menu1_File_SaveAs
  menu1_File_SaveAs.SetFOwner(this);
  menu1_File_SaveAs.SetClass(lxT("CItemMenu"));
  menu1_File_SaveAs.SetName(lxT("menu1_File_SaveAs"));
  menu1_File_SaveAs.SetTag(0);
  menu1_File_SaveAs.SetText(lxT("SaveAs"));
  menu1_File_SaveAs.SetEnable(1);
  menu1_File_SaveAs.SetSubMenu(NULL);
  menu1_File_SaveAs.EvMenuActive=EVMENUACTIVE & CPWindow1::menu1_File_SaveAs_EvMenuActive;
  menu1_File.CreateChild(&menu1_File_SaveAs);
  //menu1_File_Exit
  menu1_File_Exit.SetFOwner(this);
  menu1_File_Exit.SetClass(lxT("CItemMenu"));
  menu1_File_Exit.SetName(lxT("menu1_File_Exit"));
  menu1_File_Exit.SetTag(0);
  menu1_File_Exit.SetText(lxT("Exit"));
  menu1_File_Exit.SetEnable(1);
  menu1_File_Exit.SetSubMenu(NULL);
  menu1_File_Exit.EvMenuActive=EVMENUACTIVE & CPWindow1::menu1_File_Exit_EvMenuActive;
  menu1_File.CreateChild(&menu1_File_Exit);
  //menu1_Build_Compile
  menu1_Build_Compile.SetFOwner(this);
  menu1_Build_Compile.SetClass(lxT("CItemMenu"));
  menu1_Build_Compile.SetName(lxT("menu1_Build_Compile"));
  menu1_Build_Compile.SetTag(0);
  menu1_Build_Compile.SetText(lxT("Compile"));
  menu1_Build_Compile.SetEnable(1);
  menu1_Build_Compile.SetSubMenu(NULL);
  menu1_Build_Compile.EvMenuActive=EVMENUACTIVE & CPWindow1::menu1_Build_Compile_EvMenuActive;
  menu1_Build.CreateChild(&menu1_Build_Compile);
  //menu1_Build_RuninDeeds
  menu1_Build_RuninDeeds.SetFOwner(this);
  menu1_Build_RuninDeeds.SetClass(lxT("CItemMenu"));
  menu1_Build_RuninDeeds.SetName(lxT("menu1_Build_RuninDeeds"));
  menu1_Build_RuninDeeds.SetTag(0);
  menu1_Build_RuninDeeds.SetText(lxT("Run in Deeds"));
  menu1_Build_RuninDeeds.SetEnable(1);
  menu1_Build_RuninDeeds.SetSubMenu(NULL);
  menu1_Build_RuninDeeds.EvMenuActive=EVMENUACTIVE & CPWindow1::menu1_Build_RuninDeeds_EvMenuActive;
  menu1_Build.CreateChild(&menu1_Build_RuninDeeds);
  //menu1_Options_McEPath
  menu1_Options_McEPath.SetFOwner(this);
  menu1_Options_McEPath.SetClass(lxT("CItemMenu"));
  menu1_Options_McEPath.SetName(lxT("menu1_Options_McEPath"));
  menu1_Options_McEPath.SetTag(0);
  menu1_Options_McEPath.SetText(lxT("McE Path"));
  menu1_Options_McEPath.SetEnable(1);
  menu1_Options_McEPath.SetSubMenu(NULL);
  menu1_Options_McEPath.EvMenuActive=EVMENUACTIVE & CPWindow1::menu1_Options_McEPath_EvMenuActive;
  menu1_Options.CreateChild(&menu1_Options_McEPath);
  //menu1_Help_Contents
  menu1_Help_Contents.SetFOwner(this);
  menu1_Help_Contents.SetClass(lxT("CItemMenu"));
  menu1_Help_Contents.SetName(lxT("menu1_Help_Contents"));
  menu1_Help_Contents.SetTag(0);
  menu1_Help_Contents.SetText(lxT("Contents"));
  menu1_Help_Contents.SetEnable(1);
  menu1_Help_Contents.SetSubMenu(NULL);
  menu1_Help_Contents.EvMenuActive=EVMENUACTIVE & CPWindow1::menu1_Help_Contents_EvMenuActive;
  //menu1_Help.CreateChild(&menu1_Help_Contents);
  //menu1_Help_Examples
  menu1_Help_Examples.SetFOwner(this);
  menu1_Help_Examples.SetClass(lxT("CItemMenu"));
  menu1_Help_Examples.SetName(lxT("menu1_Help_Examples"));
  menu1_Help_Examples.SetTag(0);
  menu1_Help_Examples.SetText(lxT("Examples"));
  menu1_Help_Examples.SetEnable(1);
  menu1_Help_Examples.SetSubMenu(NULL);
  menu1_Help_Examples.EvMenuActive=EVMENUACTIVE & CPWindow1::menu1_Help_Examples_EvMenuActive;
  menu1_Help.CreateChild(&menu1_Help_Examples);
  //menu1_Help_About
  menu1_Help_About.SetFOwner(this);
  menu1_Help_About.SetClass(lxT("CItemMenu"));
  menu1_Help_About.SetName(lxT("menu1_Help_About"));
  menu1_Help_About.SetTag(0);
  menu1_Help_About.SetText(lxT("About"));
  menu1_Help_About.SetEnable(1);
  menu1_Help_About.SetSubMenu(NULL);
  menu1_Help_About.EvMenuActive=EVMENUACTIVE & CPWindow1::menu1_Help_About_EvMenuActive;
  menu1_Help.CreateChild(&menu1_Help_About);
  //filedialog1
  filedialog1.SetFOwner(this);
  filedialog1.SetClass(lxT("CFileDialog"));
  filedialog1.SetName(lxT("filedialog1"));
  filedialog1.SetTag(0);
  filedialog1.SetFileName(lxT("untitled.c"));
  filedialog1.SetFilter(lxT("Smallc Files (*.c;*.h)|*.c;*.C;*.h;*.H"));
  filedialog1.SetType(129);
  filedialog1.EvOnClose=EVONCLOSE & CPWindow1::filedialog1_EvOnClose;
  CreateChild(&filedialog1);
  /*#Others*/
//lxrad automatic generated block end, don't edit above!
  OFilter=lxT("");
  OFilename=lxT("");
};
