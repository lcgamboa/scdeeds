
#include<wx/wx.h>
#include<wx/stc/stc.h>
#include"scdeeds1.h"
#include"scdeeds1_d.cc"



CPWindow1 Window1;

//Implementation
const int ANNOTATION_STYLE = wxSTC_STYLE_LASTPREDEFINED + 1;

void
CPWindow1::_EvOnCreate(CControl * control)
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
 text->SetKeyWords (0, lxT ("break case continue default do else extern for goto if new null return sizeof switch this typeof while"));
 text->SetKeyWords (1, lxT ("char const double enum float int long short static struct unsigned void"));

 // annotations style
 text->StyleSetBackground (ANNOTATION_STYLE, wxColour (244, 220, 220));
 text->StyleSetForeground (ANNOTATION_STYLE, *wxBLACK);
 text->StyleSetSizeFractional (ANNOTATION_STYLE, (text->StyleGetSizeFractional (wxSTC_STYLE_DEFAULT)*4) / 5);
 text->AnnotationSetVisible (wxSTC_ANNOTATION_BOXED);

 P_filename = lxT ("");
 menu1_File_Save.SetEnable (0);
 //TODO ler preferências
#ifdef _WIN_
 P_scc8080 = lxT ("scc8080.exe");
 P_sc2deeds = lxT ("sc2deeds.exe");
 P_8085asm = lxT ("8085asm.exe");
 P_DeedsMCE = lxT ("/home/win/Arquivos\\ de\\ programas/DeedsSuite/DeedsMCE.exe");
#else 
 P_scc8080 = lxT ("../SmallC-85/smallC/scc8080");
 P_sc2deeds = lxT ("sc2deeds/sc2deeds");
 P_8085asm = lxT ("../8085asm/8085asm");
 P_DeedsMCE = lxT ("/home/win/Arquivos\\ de\\ programas/DeedsSuite/DeedsMCE.exe");
#endif

 char home[1024];
 strncpy (home, (char*) lxGetUserDataDir (lxT ("scdeeds")).char_str (), 1023);
 Configure (control, home);

}

void
CPWindow1::Configure(CControl * control, const char * home)
{

 char line[1024];
 char fname[1024];

 char *name;
 char *value;
 int lc;

 // lxString status;

 snprintf (fname, 1023, "%s/scdeeds.ini", home);


 prefs.Clear ();
 if (lxFileExists (fname))
  {
   if (prefs.LoadFromFile (fname))
    {
     for (lc = 0; lc < (int) prefs.GetLinesCount (); lc++)
      {
       strncpy (line, prefs.GetLine (lc).c_str (), 1023);

       name = strtok (line, "\t= ");
       strtok (NULL, " ");
       value = strtok (NULL, "\"");
       if ((name == NULL) || (value == NULL))continue;

       if (!strcmp (name, "deedsmce"))
        {
         P_DeedsMCE = lxString (value, lxConvUTF8);
        }


      }
    }
  }
 else
  {
   printf ("Error open config file \"%s\"!\n", fname);
  }
}

void
CPWindow1::_EvOnDestroy(CControl * control)
{
 char home[1010];
 char fname[1110];

 //write options
 strncpy (home, (char*) lxGetUserDataDir (lxT ("scdeeds")).char_str (), 1000);

 lxCreateDir (home);

 snprintf (fname, 1200, "%s/scdeeds.ini", home);

 saveprefs (lxT ("deedsmce"), P_DeedsMCE);

 prefs.SaveToFile (fname);

}

void
CPWindow1::saveprefs(lxString name, lxString value)
{
 char line[1024];
 char *pname;
 char *pvalue;

 for (int lc = 0; lc < (int) prefs.GetLinesCount (); lc++)
  {
   strncpy (line, prefs.GetLine (lc).c_str (), 1023);

   pname = strtok (line, "\t= ");
   strtok (NULL, " ");
   pvalue = strtok (NULL, "\"");

   if ((pname == NULL) || (pvalue == NULL))continue;

   if (lxString (pname) == name)
    {
     prefs.SetLine (name + lxT ("\t= \"") + value + lxT ("\""), lc);

     return;
    }
  }
 prefs.AddLine (name + lxT ("\t= \"") + value + lxT ("\""));
}

void
CPWindow1::_EvOnShow(CControl * control)
{
 styledtext1.SetWidth (GetWidth () - 20);
 styledtext1.SetHeight (GetHeight () - 70);
}

void
CPWindow1::menu1_File_Open_EvMenuActive(CControl * control)
{
 filedialog1.SetType (lxFD_OPEN | lxFD_CHANGE_DIR);
 filedialog1.Run ();
}

void
CPWindow1::menu1_File_Save_EvMenuActive(CControl * control)
{
 styledtext1.SaveToFile (P_filename);
}

void
CPWindow1::menu1_File_Exit_EvMenuActive(CControl * control)
{
 WDestroy ();
}

void
CPWindow1::menu1_Build_Compile_EvMenuActive(CControl * control)
{

 if (P_filename.size () == 0)
  {
   Message (lxT ("First save the file!"));
   return;
  }

 wxStyledTextCtrl * text = (wxStyledTextCtrl*) styledtext1.GetWidget ();

 text->AnnotationClearAll ();

 styledtext1.SaveToFile (P_filename);

 lxString oldpath = lxGetCwd ();

 lxSetWorkingDirectory (dirname (P_filename));
 lxString cmd = dirname (lxGetExecutablePath ()) + P_scc8080 + lxT (" -t ") + basename (P_filename);
 wxArrayString result;
 wxExecute (cmd, result);


 lxString fname = basename (P_filename).BeforeLast ('.') + lxT (".s");

 if ((result.Count () == 1) && lxFileExists (fname))
  {


   lxString cmd = dirname (lxGetExecutablePath ()) + P_sc2deeds + lxT (" ") + fname;

   lxExecute (cmd);

   fname = dirname (P_filename) + basename (P_filename).BeforeLast ('.') + lxT (".asm");

   cmd = dirname (lxGetExecutablePath ()) + P_8085asm + lxT (" ") + fname;

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
       text->AnnotationSetText (1, text->AnnotationGetText (1) + result.Item (i) + lxT ("\n"));
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
       lxString error = result.Item (i);
       lxString resto;

       lxString fname = error.BeforeFirst (':', &resto);
       error = resto;
       lxString line = error.BeforeFirst (':', &resto);
       error = resto;
       lxString pos = error.BeforeFirst (':', &resto);

       int lineno = atoi (line) - 1;

       text->AnnotationSetText (lineno, text->AnnotationGetText (lineno) + resto + lxT ("\n"));
       text->AnnotationSetText (lineno, text->AnnotationGetText (lineno) + result.Item (++i) + lxT ("\n"));
       text->AnnotationSetText (lineno, text->AnnotationGetText (lineno) + result.Item (++i) + lxT ("\n"));

       text->AnnotationSetStyle (lineno, ANNOTATION_STYLE);
       printf ("%s\n", (const char *) result.Item (i));
      }
     else
      {
       text->AnnotationSetText (1, text->AnnotationGetText (1) + result.Item (i) + lxT ("\n"));
       text->AnnotationSetStyle (1, ANNOTATION_STYLE);
       printf ("%s\n", (const char *) result.Item (i));
      }
    }
   Message ("Compile error!");
  }

 lxSetWorkingDirectory (oldpath);
}

void
CPWindow1::menu1_Build_RuninDeeds_EvMenuActive(CControl * control)
{

 if (P_filename.size () == 0)
  {
   Message (lxT ("First save the file!"));
   return;
  }

 lxString fname = basename (P_filename).BeforeLast ('.') + lxT (".mc8");

 if (lxFileExists (fname))
  {
#ifdef _WIN_
   lxString cmd = P_DeedsMCE + lxT (" ") + fname;
#else
   lxString cmd = lxT ("wine \"")+P_DeedsMCE + lxT ("\" ") + fname;
#endif
   
   printf ("cmd=[%s]\n", (const char *) cmd.c_str ());
   lxExecute (cmd);
  }
 else
  {
   Message (lxT ("First compile the file!"));
  }
}

void
CPWindow1::filedialog1_EvOnClose(const int retId)
{
 if (retId && (filedialog1.GetType () == (lxFD_SAVE | lxFD_CHANGE_DIR)))
  {
   if (lxFileExists (filedialog1.GetFileName ()))
    {

     if (!Dialog (lxString ("Overwriting file: ") + basename (filedialog1.GetFileName ()) + "?"))
      return;
    }
   P_filename = filedialog1.GetFileName ();
   styledtext1.SaveToFile (P_filename);
   menu1_File_Save.SetEnable (1);
  }

 if (filedialog1.GetType () == (lxFD_OPEN | lxFD_CHANGE_DIR))
  {
   if (OFilter.size () > 0)
    {
     if (retId)
      {
       P_DeedsMCE = filedialog1.GetFileName ();
      }
     filedialog1.SetFilter (OFilter);
     filedialog1.SetFileName (OFilename);
     OFilter = lxT ("");
     OFilename = lxT ("");
    }
   else if (retId)
    {
     wxStyledTextCtrl * text = (wxStyledTextCtrl*) styledtext1.GetWidget ();
     text->ClearAll ();
     P_filename = filedialog1.GetFileName ();
     styledtext1.LoadFromFile (P_filename);
     menu1_File_Save.SetEnable (1);
    }
  }
}

void
CPWindow1::menu1_File_SaveAs_EvMenuActive(CControl * control)
{
 filedialog1.SetType (lxFD_SAVE | lxFD_CHANGE_DIR);
 filedialog1.Run ();
}

void
CPWindow1::menu1_Help_Examples_EvMenuActive(CControl * control)
{
 filedialog1.SetType (lxFD_OPEN | lxFD_CHANGE_DIR);
 filedialog1.SetFileName (dirname (lxGetExecutablePath ())+lxT("examples/blink.c"));
 filedialog1.Run ();
}

void
CPWindow1::menu1_Help_About_EvMenuActive(CControl * control)
{
 Message (lxT ("Developed by L.C. Gamboa\n <lcgamboa@yahoo.com>\n Version: ") + lxString (lxT (_VERSION_)));

}

void
CPWindow1::menu1_File_New_EvMenuActive(CControl * control)
{
 wxStyledTextCtrl * text = (wxStyledTextCtrl*) styledtext1.GetWidget ();
 if (text->GetLineCount () > 1)
  {
   if (Dialog (lxT ("Discard all?")))
    {
     text->ClearAll ();
     P_filename = lxT ("");
     menu1_File_Save.SetEnable (0);
    }
  }
}

void
CPWindow1::menu1_Help_Contents_EvMenuActive(CControl * control)
{
 //code here:)
 mprint (lxT ("menu1_Help_Contents_EvMenuActive\n"));
}

void
CPWindow1::menu1_Options_McEPath_EvMenuActive(CControl * control)
{
 filedialog1.SetType (lxFD_OPEN | lxFD_CHANGE_DIR);

 OFilter = filedialog1.GetFilter ();
 OFilename = filedialog1.GetFileName ();
 filedialog1.SetFilter (lxT ("DeedsMcE (*.exe)|*.exe;*.EXE;"));
 filedialog1.SetFileName (P_DeedsMCE);

 filedialog1.Run ();
}


