
//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


extern int xpdf_main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
 return xpdf_main(argc, argv);
}


#ifdef HIDE
#ifdef _WIN32
int CALLBACK WinMain(HINSTANCE hIstance, HINSTANCE hPrevInstance,
       LPSTR lpCmdLine, int nCmdShow) {
  wchar_t **args;
  int argc, i, n, ret;

  if (!(args = CommandLineToArgvW(GetCommandLineW(), &argc)) ||
      argc < 0) {
    return -1;
  }
  char **argv = (char  **)gmallocn(argc + 1, sizeof(char *));
  for (i = 0; i < argc; ++i) {
    n = WideCharToMultiByte(CP_ACP, 0, args[i], -1, NULL, 0, NULL, NULL);
    argv[i] = (char *)gmalloc(n);
    WideCharToMultiByte(CP_ACP, 0, args[i], -1, argv[i], n, NULL, NULL);
  }
  argv[argc] = NULL;
  LocalFree(args);
  ret = xpdf_main(argc, argv);
  for (i = 0; i < argc; ++i) {
    gfree(argv[i]);
  }
  gfree(argv);
  return ret;
}
#endif
#endif // HIDE

