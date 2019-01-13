
#include"scdeeds1.h"
#include"scdeeds1_d.cc"
#include<wx/stc/stc.h>
#include <lxrad/cstyledtext.h>
#include <lxrad_SDL2/ccontrol.h>


CPWindow1 Window1;


//Implementation
const int ANNOTATION_STYLE = wxSTC_STYLE_LASTPREDEFINED + 1;

void
CPWindow1::_EvOnCreate (CControl * control)
{

 wxStyledTextCtrl * text = (wxStyledTextCtrl*) styledtext1.GetWidget ();

 text->StyleClearAll ();
 text->SetLexer (wxSTC_LEX_CPP);

 text->SetMarginWidth (0, 20);
 text->StyleSetForeground (wxSTC_STYLE_LINENUMBER, wxColour (75, 75, 75));
 text->StyleSetBackground (wxSTC_STYLE_LINENUMBER, wxColour (220, 220, 220));
 text->SetMarginType (0, wxSTC_MARGIN_NUMBER);


 text->SetWrapMode (wxSTC_WRAP_WORD); // other choice is wxSCI_WRAP_NONE

 text->StyleSetForeground (wxSTC_C_STRING, wxColour (150, 0, 0));
 text->StyleSetForeground (wxSTC_C_PREPROCESSOR, wxColour (165, 105, 0));
 text->StyleSetForeground (wxSTC_C_IDENTIFIER, wxColour (40, 0, 60));
 text->StyleSetForeground (wxSTC_C_NUMBER, wxColour (0, 150, 0));
 text->StyleSetForeground (wxSTC_C_CHARACTER, wxColour (150, 0, 0));
 text->StyleSetForeground (wxSTC_C_WORD, wxColour (0, 0, 150));
 text->StyleSetForeground (wxSTC_C_WORD2, wxColour (0, 150, 0));
 text->StyleSetForeground (wxSTC_C_COMMENT, wxColour (150, 150, 150));
 text->StyleSetForeground (wxSTC_C_COMMENTLINE, wxColour (150, 150, 150));
 text->StyleSetForeground (wxSTC_C_COMMENTDOC, wxColour (150, 150, 150));
 text->StyleSetForeground (wxSTC_C_COMMENTDOCKEYWORD, wxColour (0, 0, 200));
 text->StyleSetForeground (wxSTC_C_COMMENTDOCKEYWORDERROR, wxColour (0, 0, 200));
 text->StyleSetBold (wxSTC_C_WORD, true);
 text->StyleSetBold (wxSTC_C_WORD2, true);
 text->StyleSetBold (wxSTC_C_COMMENTDOCKEYWORD, true);

 // a sample list of keywords, I haven't included them all to keep it short...
 text->SetKeyWords (0, wxT ("break case continue default do else extern for goto if new null return sizeof switch this typeof while"));
 text->SetKeyWords (1, wxT ("char const double enum float int long short static struct unsigned void"));

 // annotations style
 text->StyleSetBackground (ANNOTATION_STYLE, wxColour (244, 220, 220));
 text->StyleSetForeground (ANNOTATION_STYLE, *wxBLACK);
 text->StyleSetSizeFractional (ANNOTATION_STYLE, (text->StyleGetSizeFractional (wxSTC_STYLE_DEFAULT)*4) / 5);
 text->AnnotationSetVisible (wxSTC_ANNOTATION_BOXED);

 P_filename = wxT ("");
 menu1_File_Save.SetEnable (0);
 //TODO ler preferências
 P_scc8080 = wxT ("../SmallC-85/smallC/scc8080");
 P_sc2deeds = wxT ("sc2deeds/sc2deeds");
 P_8085asm = wxT ("../8085asm/8085asm");
 P_DeedsMCE = wxT ("wine /home/win/Arquivos\\ de\\ programas/DeedsSuite/DeedsMCE.exe");
}

void
CPWindow1::_EvOnShow (CControl * control)
{
 styledtext1.SetWidth (GetWidth () - 20);
 styledtext1.SetHeight (GetHeight () - 70);
}

void
CPWindow1::menu1_File_Open_EvMenuActive (CControl * control)
{
 filedialog1.SetType (lxFD_OPEN | lxFD_CHANGE_DIR);
 filedialog1.Run ();
}

void
CPWindow1::menu1_File_Save_EvMenuActive (CControl * control)
{
 styledtext1.SaveToFile (P_filename);
}

void
CPWindow1::menu1_File_Exit_EvMenuActive (CControl * control)
{
 WDestroy ();
}

void
CPWindow1::menu1_Build_Compile_EvMenuActive (CControl * control)
{

 if (P_filename.size () == 0)
  {
   Message (wxT ("First save the file!"));
   return;
  }

 wxStyledTextCtrl * text = (wxStyledTextCtrl*) styledtext1.GetWidget ();

 text->AnnotationClearAll ();

 styledtext1.SaveToFile (P_filename);

 String oldpath = lxGetCwd ();

 wxSetWorkingDirectory (dirname (P_filename));
 wxArrayString result;
 String cmd = dirname (lxGetExecutablePath ()) + P_scc8080 + wxT (" -t ") + basename (P_filename);
 lxExecute (cmd, result);


 String fname = basename (P_filename).BeforeLast ('.') + wxT (".s");

 if ((result.Count () == 1) && lxFileExists (fname))
  {


   String cmd = dirname (lxGetExecutablePath ()) + P_sc2deeds + wxT (" ") + fname;

   lxExecute (cmd);

   fname = dirname (P_filename) + basename (P_filename).BeforeLast ('.') + wxT (".asm");

   cmd = dirname (lxGetExecutablePath ()) + P_8085asm + wxT (" ") + fname;

   lxExecute (cmd, result);
   if (result.Count () == 6)
    {
     printf ("success!\n");
     Message ("Success!");
    }
   else
    {
     printf ("Assembler error\n");
     for (unsigned int i = 0; i < result.Count (); i++)
      {
       text->AnnotationSetText (1, text->AnnotationGetText (1) + result.Item (i) + wxT ("\n"));
       text->AnnotationSetStyle (1, ANNOTATION_STYLE);
       printf ("%s\n", (const char *) result.Item (i));
      }
     Message ("Assembler error!");
    }
  }
 else
  {
   printf ("Compile error\n");

   for (unsigned int i = 0; i < result.Count (); i++)
    {
     if (result.Item (i).Contains (basename (P_filename)))
      {
       String error = result.Item (i);
       String resto;

       String fname = error.BeforeFirst (':', &resto);
       error = resto;
       String line = error.BeforeFirst (':', &resto);
       error = resto;
       String pos = error.BeforeFirst (':', &resto);

       int lineno = atoi (line) - 1;

       text->AnnotationSetText (lineno, text->AnnotationGetText (lineno) + resto + wxT ("\n"));
       text->AnnotationSetStyle (lineno, ANNOTATION_STYLE);
       printf ("%s\n", (const char *) result.Item (i));
      }
     else
      {
       text->AnnotationSetText (1, text->AnnotationGetText (1) + result.Item (i) + wxT ("\n"));
       text->AnnotationSetStyle (1, ANNOTATION_STYLE);
       printf ("%s\n", (const char *) result.Item (i));
      }
    }
   Message ("Compile error!");
  }

 wxSetWorkingDirectory (oldpath);
}

void
CPWindow1::menu1_Build_RuninDeeds_EvMenuActive (CControl * control)
{

 if (P_filename.size () == 0)
  {
   Message (wxT ("First save the file!"));
   return;
  }

 String fname = basename (P_filename).BeforeLast ('.') + wxT (".mc8");

 if (lxFileExists (fname))
  {
   String cmd = P_DeedsMCE + wxT (" ") + fname;

   printf ("cmd=[%s]\n", (const char *) cmd.c_str ());
   lxExecute (cmd);
  }
 else
  {
   Message (wxT ("First compile the file!"));
  }
}

void
CPWindow1::filedialog1_EvOnClose (const int retId)
{
 if (retId && (filedialog1.GetType () == (lxFD_SAVE | lxFD_CHANGE_DIR)))
  {
   if (lxFileExists (filedialog1.GetFileName ()))
    {

     if (!Dialog (String ("Overwriting file: ") + basename (filedialog1.GetFileName ()) + "?"))
      return;
    }
   P_filename = filedialog1.GetFileName ();
   styledtext1.SaveToFile (P_filename);
   menu1_File_Save.SetEnable (1);
  }

 if (retId && (filedialog1.GetType () == (lxFD_OPEN | lxFD_CHANGE_DIR)))
  {
   wxStyledTextCtrl * text = (wxStyledTextCtrl*) styledtext1.GetWidget ();
   text->ClearAll ();
   P_filename = filedialog1.GetFileName ();
   styledtext1.LoadFromFile (P_filename);
   menu1_File_Save.SetEnable (1);
  }
}

void
CPWindow1::menu1_File_SaveAs_EvMenuActive (CControl * control)
{
 filedialog1.SetType (lxFD_SAVE | lxFD_CHANGE_DIR);
 filedialog1.Run ();
}

void
CPWindow1::menu1_Help_Examples_EvMenuActive (CControl * control)
{
 //code here:)
 mprint (wxT ("menu1_Help_Examples_EvMenuActive\n"));
}

void
CPWindow1::menu1_Help_About_EvMenuActive (CControl * control)
{
 //code here:)
 mprint (wxT ("menu1_Help_About_EvMenuActive\n"));
}

void
CPWindow1::menu1_File_New_EvMenuActive (CControl * control)
{
 wxStyledTextCtrl * text = (wxStyledTextCtrl*) styledtext1.GetWidget ();
 if (text->GetLineCount () > 1)
  {
   if (Dialog (wxT ("Discard all?")))
    {
     text->ClearAll ();
     P_filename = wxT ("");
     menu1_File_Save.SetEnable (0);
    }
  }
}

void
CPWindow1::menu1_Help_Contents_EvMenuActive (CControl * control)
{
 //code here:)
 mprint (wxT ("menu1_Help_Contents_EvMenuActive\n"));
}
